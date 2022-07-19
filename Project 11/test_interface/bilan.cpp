/**
    @file bilan.cpp
    @brief définition des fonctions membres de la classe bilan.
    @author Ophélie Delattre, Jérémy Godde
    @version v3
    @date 08 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "../Transaction/header/transactionmanager.h"
#include "bilan.h"
#include "ui_bilan.h"
#include "mainwindow.h"

double const unite_par_mm = 47.39; //constante

bilan::bilan(MainWindow *parent) :
    QDialog(parent),
    date(new QDateEdit(QDate::currentDate())),
    design(new Ui::bilan)
{
    devise = parent->getDevise();
    design->setupUi(this);
    design->tableActif->horizontalHeader()->setStretchLastSection(true);
    design->tablePassif->horizontalHeader()->setStretchLastSection(true);
    design->totalDetteLineEdit->setReadOnly(true);
    design->totalCreanceLineEdit->setReadOnly(true);

    date->setMinimumDate(QDate(01,01,1970));
    QLabel* dateLabel = new QLabel(tr("Date"));
    design->formLayout->insertRow(0,dateLabel,date);


    //on cache tous les attributs non nécessaires :
    this->setFixedSize(650,150);
    design->labelDette->setVisible(false);
    design->labelCreance->setVisible(false);
    design->labelMonnaie1->setVisible(false);
    design->labelMonnaie2->setVisible(false);
    design->tableActif->setVisible(false);
    design->tablePassif->setVisible(false);
    design->totalDetteLabel->setVisible(false);
    design->totalCreanceLabel->setVisible(false);
    design->totalCreanceLineEdit->setVisible(false);
    design->totalDetteLineEdit->setVisible(false);
    design->totalCreanceLineEdit->setVisible(false);
    design->pushButtonExport->setVisible(false);

    //on met à jour la devise dans la fenêtre

    //mise à jour dans les labels en bas de la page
    design->labelMonnaie1->setText(devise);
    design->labelMonnaie2->setText(devise);
    //mise à jour dans les tableaux
    QStringList lt;
    lt.push_back(QString("Compte"));
    lt.push_back(QString("Montant ")+devise);
    design->tableActif->setHorizontalHeaderLabels(lt);
    design->tablePassif->setHorizontalHeaderLabels(lt);

    //connection
    connect(design->bilenPushButton,SIGNAL(clicked()),this,SLOT(fairebilan()));
}

bilan::~bilan()
{
    delete design;
}


void bilan::fairebilan(){

    //on recupere la date actuelle
    // Le bilan (actif/passif) donne, à  une date donnée, le total des créances et dettes et leur répartition dans les sous-comptes.
     QDateTime qdate = date->dateTime();

     //On compare les dates
     if (qdate.date()>QDate::currentDate()){
         QMessageBox::information(this,"Information",
         "Vous ne pouvez pas faire de bilan à une date future");
         return;
     }

     if (qdate.date().year()<1970){
         QMessageBox::information(this,"Information",
         "Aucun compte et aucune transaction n'existait à cette période");
         return;
     }

     this->setFixedSize(650,540);
     design->labelDette->setVisible(true);
     design->labelCreance->setVisible(true);
     design->tableActif->setVisible(true);
     design->tablePassif->setVisible(true);
     design->totalDetteLabel->setVisible(true);
     design->totalCreanceLabel->setVisible(true);
     design->totalDetteLineEdit->setVisible(true);
     design->totalCreanceLineEdit->setVisible(true);
     design->labelMonnaie1->setVisible(true);
     design->labelMonnaie2->setVisible(true);
     design->pushButtonExport->setVisible(true);

     connect(design->pushButtonExport,SIGNAL(clicked()),this,SLOT(exporterPDF()));

     list<CompteHierarchie*> liste_comptes;
     // Pour les passifs

     liste_comptes = CompteManager::getInstance().getListeComptePoste(PASSIF);
     double total = affichertableau(design->tablePassif, liste_comptes);
     design->totalDetteLineEdit->setText(QString::number(total));

     //pour les actifs
     liste_comptes = CompteManager::getInstance().getListeComptePoste(ACTIF);
     total = affichertableau(design->tableActif, liste_comptes);
     design->totalCreanceLineEdit->setText(QString::number(total));

     est_genere = true;

}

double bilan::affichertableau(QTableWidget* const _tableau, std::list<CompteHierarchie*> _liste_comptes)
{
    _tableau->clearContents();
    _tableau->setRowCount(0);

    //on transforme en time_t et on met la date par défaut à 23h59
     time_t const date_t = time_t(QDateTime(date->dateTime().date(),QTime(23,59,59)).toTime_t());

    TransactionManager& tm = TransactionManager::getInstance();
    const Memento* m = nullptr;
    list<Transaction*> liste_t;

      int row = 0;
     double temp = 0.,total=  0.;

    if(!_liste_comptes.empty()){

        QTableWidgetItem TWI_vide("\"");
        TWI_vide.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        QTableWidgetItem TWI_nul("-");
        TWI_nul.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        for(auto c : _liste_comptes)
        {
            // Récupérer les mementos
            const list<Memento*>liste_m = c->getMementos();
            m = liste_m.front();
            // on parcourt les Mementos, ("elt" est un Memento*)
           for(auto elt : liste_m)
            {
               // Si on trouve un memento plus récent sans dépasser la date on le stocke
                if(difftime( date_t,elt->getDate())>=0 && difftime(elt->getDate(), m->getDate())>=0)
                 {
                     m = elt;
                    // Si on a dépassé la date inutile d'aller plus loin
                 }
                    else if (difftime(date_t, elt->getDate())<0)
                    {
                        break;
                    }
            }

            // Initialiser le solde temporaire avec son solde
            // On va essayer de reproduire le solde du compte à   partir des transactions réalisées après le Memento.
            temp = m->getSolde();

            // Parcourir les opérations réalisées après la date du memento et avant la date du bilan, et mettre à  jour le solde temporaire

            // On essaye de récupérer la liste
            // Si on a une erreur différente de "liste vide" on la renvoie
            // Si on a une erreur "liste vide" on vide juste la liste.
            try
            {
                liste_t = tm.getListeTransactionsParCompte(c->getId());
            }
            catch (ExceptionTransaction& e)
            {
                if(e.getCode() != ExceptionTransaction::CodeExcepTransaction::SRCH_EXC_T) {
                    QMessageBox::information(this,"Erreur", QString::fromStdString(e.getMessage()));
                 }
                liste_t.clear();
            }

            // ("t" est un Transaction*)
            for(auto t : liste_t)
            {
                // Si la transaction a été réalisée avant, on l'ignore
                if(difftime(t->getDate(), m->getDate())<=0)
                {
                    continue;
                }
                // Si elle a été réalisée après le memento et avant la date limite on la traite
                else if (difftime(t->getDate(), m->getDate())>0 && (difftime(t->getDate(), date_t)<=0))
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
                                c->getPosteCompte().debiter(&temp, o->getDebit());
                            }
                            // Sinon c'est un crédit
                            else
                            {
                                c->getPosteCompte().crediter(&temp, o->getCredit());
                            }
                        }
                    }
                }
                // Si on est après la date, on sort de la boucle
                else if (difftime(t->getDate(), date_t)>0)
                {
                    break;
                }
            }

             _tableau->setRowCount(row+1);
            // Afficher le nom du compte, et le solde
             _tableau->setItem(row,0,new QTableWidgetItem(QString::fromStdString(c->getNom())));
             _tableau->setItem(row,1,new QTableWidgetItem(QString::number(temp)));
             row++;
            total += temp;
       }
  }
    return total;
}

void bilan::exporterPDF()
{
    if(!est_genere) return; //cette fonction nécessite que bilan::fairebilan() ait été exécutée.

    //création du fichier-------------------------------------------
    QString chemin = QFileDialog::getSaveFileName(this,"Exporter le bilan :","../Exports/","PDF (.pdf)");

    if(chemin.size()==0) return;

    chemin += ".pdf";

    time_t now = time(nullptr);
    setlocale(LC_ALL, "french");
    struct tm* now_tm = gmtime(&now);
    char now_c[30];
    strftime(now_c,30,"%A %d %b %Y",now_tm);
    QString date_s = QString::fromLatin1(now_c);
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
                         "Bilan");
        f.setPointSize(8);        f.setBold(false);
        painter.setFont(f);

        painter.drawLine(int(27*unite_par_mm),int(12*unite_par_mm),int(65*unite_par_mm),int(12*unite_par_mm));

        painter.drawText(int(27*unite_par_mm),int(15*unite_par_mm),int(35*unite_par_mm),int(3*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         date_s);

        painter.drawText(int(27*unite_par_mm),int(21*unite_par_mm),int(35*unite_par_mm),int(3*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Powered by Business App");

        QLocale francais(QLocale::French,QLocale::France);
        QString date_local = francais.toString(date->dateTime(),"dddd d MMMM yyyy");

        painter.drawText(int(90*unite_par_mm),int(9*unite_par_mm),int(75*unite_par_mm),int(9*unite_par_mm),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         "Bilan des comptes d'actif et de passif à la date\ndu "+date_local);

        painter.drawLine(0,int(27*unite_par_mm),int(190*unite_par_mm),int(27*unite_par_mm));

    //dessin du corps de page-----------------------------------------

        f.setPointSize(18);        f.setBold(true);
        painter.setFont(f);
        painter.drawText(int(0*unite_par_mm),int(40*unite_par_mm),int(190*unite_par_mm),int(7*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Actif");
        f.setPointSize(8);        f.setBold(false);
        painter.setFont(f);

        int y = makeTableForPDF(design->tableActif,55,&painter,&f);

        f.setPointSize(18);        f.setBold(true);
        painter.setFont(f);
        painter.drawText(int(0*unite_par_mm),int((y+15)*unite_par_mm),int(190*unite_par_mm),int(7*unite_par_mm),
                         Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine,
                         "Passif");
        f.setPointSize(8);        f.setBold(false);
        painter.setFont(f);

        (void)makeTableForPDF(design->tablePassif,y+30,&painter,&f);

        painter.end();

    QMessageBox::information(this,"Information","Votre document a été exporté avec succès.");
}

int bilan::makeTableForPDF(QTableWidget* const _tableau,int const _y_origin, QPainter* _painter, QFont* _f)
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
