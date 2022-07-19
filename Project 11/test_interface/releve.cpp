/**
    @file releve.cpp
    @brief définition des fonctions membres de la classe releve.
    @author Ophélie Delattre, Jérémy Godde
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "releve.h"
#include "ui_releve.h"
#include "mainwindow.h"

double const unite_par_mm = 47.39; //constante

releve::releve(MainWindow* parent) :
    QDialog(parent),
    debut(new QDateEdit(QDate::currentDate())),
    fin((new QDateEdit(QDate::currentDate()))),
    design(new Ui::releve)
{
    design->setupUi(this);
    design->tableRecettes->horizontalHeader()->setStretchLastSection(true);
    design->tableDepenses->horizontalHeader()->setStretchLastSection(true);

    devise = parent->getDevise();

    fin->setMinimumDate(QDate(01,01,1970));
    QLabel* finLabel = new QLabel(tr("Date Fin"));
    design->formLayout->insertRow(0,finLabel,fin);

    debut->setMinimumDate(QDate(01,01,1970));
    QLabel* debutLabel = new QLabel(tr("Date Debut"));
    design->formLayout->insertRow(0,debutLabel,debut);

    //on cache tous les attributs non nécessaires :
    this->setFixedSize(650,200);
    design->labelDepenses->setVisible(false);
    design->labelRecettes->setVisible(false);
    design->tableRecettes->setVisible(false);
    design->tableDepenses->setVisible(false);
    design->pushButtonExport->setVisible(false);

    //connection
    connect(design->pushButtonReleve,SIGNAL(clicked()),this,SLOT(fairereleve()));

    //mise à jour de la monnaie
    QStringList lt;
    lt.push_back(QString("Compte"));
    lt.push_back(QString("Montant ")+devise);
    design->tableDepenses->setHorizontalHeaderLabels(lt);
    design->tableRecettes->setHorizontalHeaderLabels(lt);
}

releve::~releve()
{
    delete design;
}

void releve::fairereleve(){
    this->setFixedSize(650,600);
    design->labelDepenses->setVisible(true);
    design->labelRecettes->setVisible(true);
    design->tableRecettes->setVisible(true);
    design->tableDepenses->setVisible(true);
    design->pushButtonExport->setVisible(true);

    connect(design->pushButtonExport,SIGNAL(clicked()),this,SLOT(exporterPDF()));

    //on recupere la date debut et de fin
    // Le relevé des recettes et des dépenses liste l'ensemble des recettes et des dépenses effectuées sur une période donnée.
    QDateTime qdebut= debut->dateTime();
    QDateTime qfin= fin->dateTime();

     //On fait les vérifs sur les dates
    if (qdebut.date()>qfin.date()){
        QMessageBox::warning(this,"Erreur",
        "La date debut doit être inféireur à la date de fin");
        return;
    }

     if (qdebut.date()>QDate::currentDate() || qfin.date()>QDate::currentDate()){
         QMessageBox::information(this,"Information",
         "Vous ne pouvez pas faire de releve dans le futur");
         return;
     }

     if (qdebut.date().year()<1970 || qfin.date().year()<1970){
         QMessageBox::information(this,"Information",
         "Aucun compte et aucunes transaction n'existaient à cette période");
         return;
     }

     list<CompteHierarchie*> liste_comptes;
     // Pour les recettes

     liste_comptes = CompteManager::getInstance().getListeComptePoste(RECETTE);
     affichertableau(design->tableRecettes, liste_comptes);

     //pour les dépense
     liste_comptes = CompteManager::getInstance().getListeComptePoste(DEPENSE);
     affichertableau(design->tableDepenses, liste_comptes);

     est_genere = true;
}

void releve::affichertableau(QTableWidget* const _tableau, std::list<CompteHierarchie*> const _liste_comptes){
    _tableau->clearContents();
    _tableau->setRowCount(0);

    //on transforme en time_t et on met la date par défaut à 23h59
     time_t const debut_t = time_t(QDateTime(debut->dateTime().date(),QTime(00,00,00)).toTime_t());
     time_t const fin_t = time_t(QDateTime(fin->dateTime().date(),QTime(23,59,59)).toTime_t());

    TransactionManager& tm = TransactionManager::getInstance();
    double delta = 0.;

    int row = 0;

    if(!_liste_comptes.empty()){

        QTableWidgetItem TWI_vide("\"");
        TWI_vide.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        QTableWidgetItem TWI_nul("-");
        TWI_nul.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        for(auto c : _liste_comptes)
        {
            // Cette fois on ne cherche pas à  connaître le solde absolu : On s'intéresse à  un Delta Solde sur la période.
            // On essaye de récupérer la liste de ses transactions
            list<Transaction*> liste_t;
            delta =0.;
            try
            {
                liste_t = tm.getListeTransactionsParCompte(c->getId());
            }
            catch (ExceptionTransaction& e)
            {
                if(e.getCode() != ExceptionTransaction::CodeExcepTransaction::SRCH_EXC_T){
                    QMessageBox::information(this,"Erreur", QString::fromStdString(e.getMessage()));
                }
                liste_t.clear();
            }


            for(auto t : liste_t)
            {
                // Si la transaction a été réalisée avant, on l'ignore
                if(difftime(t->getDate(), debut_t)<0)
                {
                    continue;
                }
                // Si elle a été réalisée après le début et avant la fin de la période
                else if (difftime(t->getDate(), debut_t)>=0 && difftime(t->getDate(),fin_t)<=0)
                {
                    // Pour chacune des opérations ("o" est un Operation*)
                    for(auto o : t->getListeOperations())
                    {
                        // Si l'opération porte sur le compte actuel
                        if(o->isCompte(c->getId()))
                        {
                            // Si c'est un débit
                            if(o->getDebit() != 0.)
                            {
                                c->getPosteCompte().debiter(&delta, o->getDebit());
                            }
                            // Sinon c'est un crédit
                            else
                            {
                                c->getPosteCompte().crediter(&delta, o->getCredit());
                            }
                        }
                    }
                }// Si on est après la date de fin, on sort de la boucle
                else if (difftime(t->getDate(), fin_t)>0)
                {
                    break;
                }
            }


             _tableau->setRowCount(row+1);
            // Afficher le nom du compte, et le solde
             _tableau->setItem(row,0,new QTableWidgetItem(QString::fromStdString(c->getNom())));
             _tableau->setItem(row,1,new QTableWidgetItem(QString::number(delta)));
             row++;

       }
  }
}

void releve::exporterPDF()
{
    if(!est_genere) return; //cette fonction nécessite que releve::fairereleve() ait été exécutée.

    //création du fichier-------------------------------------------
    QString chemin = QFileDialog::getSaveFileName(this,"Exporter le relevé :","../Exports/","PDF (.pdf)");

    if(chemin.size()==0) return;

    chemin += ".pdf";

    time_t now = time(nullptr);
    setlocale(LC_ALL, "french");
    struct tm* now_tm = gmtime(&now);
    char now_c[30];
    strftime(now_c,30,"%A %d %b %Y",now_tm);
    QString date = QString::fromLatin1(now_c);
    QPdfWriter* pdf = new QPdfWriter(chemin);

    if(pdf == nullptr){
        QMessageBox::warning(this,"Erreur","Nous n'avons pas pu exporter de pdf (avez-vous un dossier \"Exports\" ?)");
        return;
    }

    //paramétrage du pdf---------------------------------------------
    pdf->setPageSize(QPageSize(QPageSize::A4));
    pdf->setTitle("Relevé");
    pdf->setPageMargins(QMarginsF(30,30,30,30)); //en pixel, contrairement à l'unité de QPainter


    //dessin de l'entête---------------------------------------------
    QPainter painter(pdf);
    QFont f;

        QImage logo(":/ressources/logo.png");
        logo = logo.scaled(int(25*unite_par_mm),int(25*unite_par_mm),Qt::KeepAspectRatio);

        painter.drawImage(0,0,logo);

        f.setFamily("times");        f.setPointSize(22);        f.setBold(true);
        painter.setFont(f);
        painter.drawText(int(27*unite_par_mm),0,int(35*unite_par_mm),int(10*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Relevé");
        f.setPointSize(8);        f.setBold(false);
        painter.setFont(f);

        painter.drawLine(int(27*unite_par_mm),int(12*unite_par_mm),int(65*unite_par_mm),int(12*unite_par_mm));

        painter.drawText(int(27*unite_par_mm),int(15*unite_par_mm),int(35*unite_par_mm),int(3*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         date);

        painter.drawText(int(27*unite_par_mm),int(21*unite_par_mm),int(35*unite_par_mm),int(3*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Powered by Business App");

        QLocale francais(QLocale::French,QLocale::France);
        QString date_1 = francais.toString(debut->dateTime(),"dddd d MMMM yyyy");
        QString date_2 = francais.toString(fin->dateTime(),"dddd d MMMM yyyy");

        painter.drawText(int(90*unite_par_mm),int(9*unite_par_mm),int(75*unite_par_mm),int(15*unite_par_mm),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         "Relevé des comptes de recette et de dépense entre\nle "+date_1+"\net le "+date_2);

        painter.drawLine(0,int(27*unite_par_mm),int(190*unite_par_mm),int(27*unite_par_mm));

    //dessin du corps de page-----------------------------------------

        f.setPointSize(18);        f.setBold(true);
        painter.setFont(f);
        painter.drawText(int(0*unite_par_mm),int(40*unite_par_mm),int(190*unite_par_mm),int(7*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Recette");
        f.setPointSize(8);        f.setBold(false);
        painter.setFont(f);

        int y = makeTableForPDF(design->tableRecettes,55,&painter,&f);

        f.setPointSize(18);        f.setBold(true);
        painter.setFont(f);
        painter.drawText(int(0*unite_par_mm),int((y+15)*unite_par_mm),int(190*unite_par_mm),int(7*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Dépense");
        f.setPointSize(8);        f.setBold(false);
        painter.setFont(f);

        (void)makeTableForPDF(design->tableDepenses,y+30,&painter,&f);

        painter.end();

    QMessageBox::information(this,"Information","Votre document a été exporté avec succès.");
}

int releve::makeTableForPDF(QTableWidget* const _tableau,int const _y_origin, QPainter* _painter, QFont* _f)
{
    int const height = 5;
    int y = _y_origin;
    double solde_total = 0.;

    for (int i = 0;
         i < _tableau->rowCount();
         i++
    )
    {
        y = _y_origin+height*i;
        _painter->drawText(int(10*unite_par_mm),int(y*unite_par_mm),int(140*unite_par_mm),int(height*unite_par_mm),
                         Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
                         _tableau->model()->index(i,0).data().toString());

        double solde = _tableau->model()->index(i,1).data().toDouble();
        solde_total += solde;
        _painter->drawText(int(150*unite_par_mm),int(y*unite_par_mm),int(30*unite_par_mm),int(height*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         QString::number(solde,'f',2));
    }
    y = _y_origin+height*_tableau->rowCount();

    //----

    _f->setBold(true);
    _painter->setFont(*_f);
    _painter->drawText(int(10*unite_par_mm),int(y*unite_par_mm),int(140*unite_par_mm),int(height*unite_par_mm),
                     Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine,
                     "TOTAL");

    _painter->drawText(int(150*unite_par_mm),int(y*unite_par_mm),int(30*unite_par_mm),int(height*unite_par_mm),
                     Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                     QString::number(solde_total,'f',2)+" "+devise);
    _f->setBold(false);
    _painter->setFont(*_f);

    return y;
}

