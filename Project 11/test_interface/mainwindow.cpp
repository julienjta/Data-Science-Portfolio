#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
    @file mainwindow.cpp
    @brief définition des fonctions membres des classes QTreeWidgetPerso et mainwindow.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/


QTreeWidgetPerso::QTreeWidgetPerso(QWidget* _parent) : QTreeWidget(_parent)
{
    setAcceptDrops(true);
}

void QTreeWidgetPerso::dropEvent(QDropEvent* event)
{
    QTreeWidget::dropEvent(event);

    //le code ci-dessous est inspir de https://forum.qt.io/topic/27951/solved-qtreewidget-drag-and-drop-signals/5

    const QMimeData* qMimeData = event->mimeData();

    QByteArray encoded = qMimeData->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    int ligne, colonne;
    QMap<int,  QVariant> Donnees;

    int i = 0;
    while(!stream.atEnd() && i < 2)
    {
        i++;
        stream >> ligne >> colonne >> Donnees; // recupre colonne par colonne, nous on veut la 2me pour l'id
    }

    int const id_bouge = Donnees[0].toString().toInt();
    int const id_recoit = this->itemAt(event->pos())->text(1).toInt(); // text(1) car l'id est dans la 2me colonne (soit la numro 1)

    emit dragAndDrop(id_bouge,id_recoit);
}





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    design(new Ui::fenetrePrincipale)
{
    //Liaison du design de la fenetre a l'objet fenetre
        design->setupUi(this);
        design->tableauCompte->horizontalHeader()->setVisible(true);  //affiche l'en-tete du tableWidget des compte
        design->tableauTransaction->horizontalHeader()->setVisible(true);//affiche l'en-tete du tableWidget des transactions

    setMinimumSize(this->width(),this->height()); // on règle la taille du .ui comme la taille minimale
    setSizeObjects(); //on fait les calculs de dimensions pour harmoniser la vue
    
    //désactivation des boutons et actions nécessitant une sélection
        design->actionSupprimerCompte->setDisabled(true);
        design->supprComptePushButton->setDisabled(true);
        design->actionModifierTransaction->setDisabled(true);
        design->modifTransacPushButton->setDisabled(true);
        design->actionSupprimerTransaction->setDisabled(true);
        design->supprTransacPushButton->setDisabled(true);

    //=====================  QACTION  ==================//
        connect(design->actionAjouterCompte, SIGNAL(triggered()), this, SLOT(afficherFormulaireCompte()));
        connect(design->actionDeplacerCompte2, SIGNAL(triggered()),this, SLOT(afficherFormulaireDeplacerCompte()));
        connect(design->actionModifierTransaction, SIGNAL(triggered()), this, SLOT(afficherFormulaireModificationTransaction()));
        connect(design->actionAjouterTransaction, SIGNAL(triggered()), this, SLOT(afficherFormulaireTransaction()));
        connect(design->actionSupprimerTransaction,SIGNAL(triggered()),this,SLOT(supprimerTransaction()));
        connect(design->actionOuvrirFichier,SIGNAL(triggered()),this,SLOT(afficherFormulaireOuvrir_1()));
        connect(design->actionEnregistrerFichier,SIGNAL(triggered()),this, SLOT(afficherFormulaireEnregistrement()));
        connect(design->actionEnregistrer_sousFichier,SIGNAL(triggered()),this, SLOT(afficherFormulaireEnregistrementSous()));
        connect(design->actionFaireReleve,SIGNAL(triggered()),this, SLOT(afficherReleve()));
        connect(design->actionFaireBilan,SIGNAL(triggered()),this, SLOT(afficherBilan()));
        connect(design->actionFaireResultat,SIGNAL(triggered()),this,SLOT(afficherResultat()));
        connect(design->actionFaireRapprochement,SIGNAL(triggered()),this, SLOT(afficherRapprochement()));
        connect(design->actionFaireCloture,SIGNAL(triggered()),this, SLOT(afficherCloture()));
        connect(design->actionParametresFichier,SIGNAL(triggered()),this,SLOT(afficherParametre()));
        connect(design->actionSupprimerCompte,SIGNAL(triggered()), this, SLOT(supprimerCompte()));

    //=================  QTreeWidget  ========================//
        connect(design->arborescenceCompte,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(selectionnerCompte(QTreeWidgetItem*)));
        connect(design->arborescenceCompte,SIGNAL(dragAndDrop(int,int)),this,SLOT(deplacerCompte(int,int)));

    //=================  QTableWidget  =======================//
        connect(design->tableauTransaction,SIGNAL(cellClicked(int,int)),this,SLOT(selectionnerTransaction(int,int)));

    //=================  QPushButton  ========================//
        connect(design->creerComptePushButton,SIGNAL(clicked()),this,SLOT(afficherFormulaireCompte()));
        connect(design->supprComptePushButton,SIGNAL(clicked()),this,SLOT(supprimerCompte()));
        connect(design->creerTransacPushButton,SIGNAL(clicked()), this, SLOT(afficherFormulaireTransaction()));
        connect(design->supprTransacPushButton,SIGNAL(clicked()),this,SLOT(supprimerTransaction()));
        connect(design->modifTransacPushButton,SIGNAL(clicked()),this,SLOT(afficherFormulaireModificationTransaction()));

    // dialog de chargement
        chargementwindow* chargement = new chargementwindow(this);
        connect(chargement,SIGNAL(chargerFichier(QString)),this,SLOT(charger(QString)));
        connect(chargement,SIGNAL(initialiser()),this,SLOT(initialiser()));
        chargement->show();
}


// Fonctions de rafraichissiment -----------------------------------------------------------------------------


void MainWindow::afficherHierarchie(){
    compte_selectionne=nullptr;
    design->actionSupprimerCompte->setDisabled(true);
    design->supprComptePushButton->setDisabled(true);
    compte_manager.affiche(design->arborescenceCompte,devise);

     QStringList comptes_reels;
     QStringList comptes_virtuels;
     std::list<int> id_comptes_virtuels;
     std::list<int> id_comptes_reels;

     compte_manager.getListeComptes(&comptes_reels,&id_comptes_reels,1);
     compte_manager.getListeComptes(&comptes_virtuels,&id_comptes_virtuels,0);

     if(!comptes_reels.empty())
        {

            design->actionFaireBilan->setEnabled(true);
            design->actionFaireReleve->setEnabled(true);
            design->actionFaireCloture->setEnabled(true);
            design->actionFaireResultat->setEnabled(true);
            design->actionFaireRapprochement->setEnabled(true);
            design->actionDeplacerCompte2->setEnabled(true);
        }
     else
     {
         design->actionFaireBilan->setEnabled(false);
         design->actionFaireReleve->setEnabled(false);
         design->actionFaireCloture->setEnabled(false);
         design->actionFaireResultat->setEnabled(false);
         design->actionFaireRapprochement->setEnabled(false);
         design->actionDeplacerCompte2->setEnabled(false);
         if (comptes_virtuels.size()>1){
             design->actionDeplacerCompte2->setEnabled(true);
         }else{
             design->actionDeplacerCompte2->setEnabled(false);
         }

     }
}

void MainWindow::afficherTransaction(){

    transac_selectionne = nullptr;
    design->actionModifierTransaction->setDisabled(true);
    design->modifTransacPushButton->setDisabled(true);
    design->actionSupprimerTransaction->setDisabled(true);
    design->supprTransacPushButton->setDisabled(true);
    transaction_manager.affiche(design->tableauTransaction,devise,formatDate);
    design->groupeOnglets->setCurrentIndex(1);

    afficherHierarchie();
}

void MainWindow::refreshContexte(QStringList params) {
    devise = params[0];
    formatDate = params[1];
    afficherTransaction();
    afficherHierarchie();
    afficherCompte();
}

void MainWindow::afficherCompte(){
    if(compte_selectionne != nullptr)
    {
        int const id = compte_selectionne->text(1).toInt();
        CompteHierarchie* compte = nullptr;

        try
        {
            compte = compte_manager.getCompte(id);
        }
        catch(Exception & except) {
            QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
            return;
        }

        if(compte->getType() == REEL)
        {
            transaction_manager.affiche(design->tableauCompte,compte,devise,formatDate);
            design->groupeOnglets->setCurrentIndex(0);
        }
    }
}


// Fonctions d'ouverture de dialog --------------------------------------------------------------------------------


void MainWindow::afficherFormulaireCompte()
{
    // creer la dialog et on l'affiche
    QStringList liste_compte;
    list<int> liste_id;
    compte_manager.getListeComptes(&liste_compte,&liste_id,2);
    ajouterwindow* nouveauCompte = new ajouterwindow(liste_id,compte_selectionne, this);
    connect(nouveauCompte,SIGNAL(ajout()),this, SLOT(afficherTransaction()));
    nouveauCompte->show();
}

void MainWindow::afficherFormulaireDeplacerCompte(){
    QStringList liste_compte;
    list<int> liste_id;
    compte_manager.getListeComptes(&liste_compte,&liste_id,2);
    deplacercompte* fdeplacement = new deplacercompte(liste_id, this);
    connect(fdeplacement, SIGNAL(deplacement()), this, SLOT(afficherHierarchie()));
    fdeplacement->show();

}


void MainWindow::afficherFormulaireTransaction()
{
    QStringList liste_compte;
    list<int> liste_id;
    compte_manager.getListeComptes(&liste_compte,&liste_id,1); // 1 = que compte reel

    if(liste_compte.size() < 2) // Si aucun compte reel n'existe
    {
        QMessageBox::information(this,QString("Information"),QString("Vous devez posséder au moins 2 comptes pour effectuer une transaction."));
        return;
    }

    ajoutertransactionwindows* nouvelleTransaction = new ajoutertransactionwindows(liste_compte,liste_id,this);
    connect(nouvelleTransaction,SIGNAL(signalDone()),this, SLOT(afficherTransaction()));
    nouvelleTransaction->show();
}

void MainWindow::afficherFormulaireEnregistrement()
{
    if(compte_manager.isDefaultPath())
    {
        afficherFormulaireEnregistrementSous();
    }
    else
    {
        sauvegarder("");
    }
}

void MainWindow::afficherFormulaireEnregistrementSous()
{
    // creer la dialog et on l'affiche
    savewindow* enregistrement = new savewindow(this);
    connect(enregistrement,SIGNAL(sauvegarderFichier(QString)),this,SLOT(sauvegarder(QString)));
    enregistrement->show();
}

void MainWindow::afficherFormulaireOuvrir_1()
{
    if(QMessageBox::StandardButton::No != QMessageBox::question(this,"","Voulez-vous sauvegarder votre travail actuel ?"))
    {
        if(compte_manager.isDefaultPath())
        {
            savewindow* enregistrement = new savewindow(this);
            connect(enregistrement,SIGNAL(sauvegarderFichier(QString)),this,SLOT(sauvegarder(QString)));
            connect(enregistrement,SIGNAL(sauvegarderFichier(QString)),this,SLOT(afficherFormulaireOuvrir_2()));
            enregistrement->show();
        }
        else
        {
            sauvegarder("");
            afficherFormulaireOuvrir_2();
        }
    }
    else
    {
        afficherFormulaireOuvrir_2();
    }
}

void MainWindow::afficherFormulaireOuvrir_2()
{
    QString nouv_path = QFileDialog::getOpenFileName(this,"Sélectionner le fichier à charger : ",
           "../Backups/","business (*.business);;XML (*.xml);;Tous les fichiers (*.*)");
    if(nouv_path.size()>0)
        charger(nouv_path);
}

void MainWindow::afficherFormulaireModificationTransaction(){
    if(transac_selectionne == nullptr)
        return;

    QStringList liste_compte;
    list<int> liste_id;
    //on recupère les comptes reels
    compte_manager.getListeComptes(&liste_compte,&liste_id,1);
    modifiertransaction *mt = new modifiertransaction(transac_selectionne->text(),liste_compte,liste_id,this);
    connect(mt,SIGNAL(modifiant()),this,SLOT(afficherTransaction()));
    mt->show();
}

void MainWindow::afficherCloture(){
    QStringList liste_compte;
    list<int> liste_id;
    //on recupère tous les comptes car on aura besoin des réels et virtuels
    compte_manager.getListeComptes(&liste_compte,&liste_id,2);
    cloture *cl = new cloture(liste_id, this);
    connect(cl, SIGNAL(ajout()), this, SLOT(afficherHierarchie()));
    connect(cl, SIGNAL(ajouttransaction()),this, SLOT(afficherTransaction()));
    cl->show();
}


void MainWindow::afficherRapprochement(){
    QStringList liste_compte;
    list<int> liste_id;
    //on recupère les comptes reels
    compte_manager.getListeComptes(&liste_compte,&liste_id,1);
    rapprochement *ra = new rapprochement(liste_compte,liste_id,this);
    connect(ra,SIGNAL(modifiant()),this,SLOT(afficherTransaction()));
    ra->show();
}

void MainWindow::afficherBilan()
{
    bilan* b = new bilan(this);
    b->show();
}

void MainWindow::afficherReleve()
{
    releve* r=new releve(this);
    r->show();
}


void MainWindow::afficherResultat()
{
    QStringList liste_compte;
    list<int> liste_id;
    compte_manager.getListeComptes(&liste_compte,&liste_id,1);
    Resultat * res=new Resultat(liste_id,this);
    res->show();
}

void MainWindow::afficherParametre()
{
    parametrewindow *pw = new parametrewindow(this);
    connect(pw,SIGNAL(modifParams(QStringList)),this,SLOT(refreshContexte(QStringList)));
    pw->show();
}


// Fonctions de selection --------------------------------------------------------------------------------------------


void MainWindow::selectionnerCompte(QTreeWidgetItem* _item_compte)
{
    compte_selectionne = _item_compte;

    compte_selectionne->setSelected(true);

    int const id = compte_selectionne->text(1).toInt();
    CompteHierarchie* compte = nullptr;

    try
    {
        compte = compte_manager.getCompte(id);
    }
    catch(Exception & except) {
        QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
        return;
    }

    if(compte->getType() == REEL)
    {
        try
        {
            transaction_manager.affiche(design->tableauCompte,compte,devise,formatDate);
        }
        catch(Exception & except) {
            QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
            return;
        }
        design->nomCompte->setText(QString::fromStdString(compte->getNom()));

        QString poste;

        switch(compte->getPoste())
        {
            case ACTIF: poste = "Actif"; break;
            case PASSIF: poste = "Passif"; break;
            case RECETTE: poste = "Recette"; break;
            case DEPENSE: poste = "Depense"; break;
            default: poste = ""; break;
        }

        design->posteCompte->setText(poste);

        std::list<Memento*>::const_reverse_iterator it_memento = compte->getMementos().rbegin();
        it_memento++;
        time_t date_t = (*it_memento)->getDate();
        if(date_t>0)
        {
            struct tm* tm_date = localtime(&date_t);
            QDate qdate(tm_date->tm_year+1900,tm_date->tm_mon+1,tm_date->tm_mday);
            string temp = formatDate.toStdString();
            replace(temp.begin(),temp.end(),'m','M');
            QString format = QString::fromStdString(temp);
            design->dateRapprochementCompte->setText("Dernier rapprochement : " + qdate.toString(format));
        }
        else
        {
            design->dateRapprochementCompte->setText("Jamais rapproché");
        }
        afficherCompte();
    }
    else{
        compte_selectionne->setExpanded(!compte_selectionne->isExpanded());
    }
    
    design->actionSupprimerCompte->setDisabled(false);
    design->supprComptePushButton->setDisabled(false);
}

void MainWindow::selectionnerTransaction(int row,int column)
{
    column++;

    int const max_column = design->tableauTransaction->columnCount();
    int i = 0;
    if(transac_selectionne != nullptr)
    {
        int const old_row = transac_selectionne->row();
        for(; i<max_column;i++)
            design->tableauTransaction->item(old_row,i)->setBackgroundColor(QColor(255,255,255));
    }

    QTableWidgetItem* cellID = design->tableauTransaction->item(row,1);
    while(cellID == nullptr) {
        row--;
        cellID = design->tableauTransaction->item(row,1);
    }
    transac_selectionne = cellID;
    design->actionModifierTransaction->setDisabled(false);
    design->modifTransacPushButton->setDisabled(false);
    design->actionSupprimerTransaction->setDisabled(false);
    design->supprTransacPushButton->setDisabled(false);


    for(i = 0; i<max_column;i++)
        design->tableauTransaction->item(row,i)->setBackgroundColor(QColor(215,215,215));
}



// Fonctions de comportement des comptes --------------------------------------------------------------------------


void MainWindow::deplacerCompte(int const _id_bouge, int const _id_recoit)
{
    try
    {
        compte_manager.deplacerFils(_id_bouge,_id_recoit);
    }
    catch(Exception except){
        QMessageBox::warning(this,QString("Erreur"),QString("Vous ne pouvez pas effectuer ce deplacement :\n")+QString::fromStdString(except.getMessage()));
    }
    afficherHierarchie();
}

void MainWindow::supprimerCompte()
{
    try {
        if(compte_selectionne != nullptr
        && QMessageBox::StandardButton::No != QMessageBox::question(this,"Validation","Voulez-vous vraiment supprimer ce compte ?"))
        {
            int const id = compte_selectionne->text(1).toInt();
            compte_manager.supprimerCompte(id);
            afficherHierarchie();
        }
    }
    catch (Exception except) {
        QMessageBox::warning(this,QString("Erreur"),QString("Destruction du compte impossible :\n")+QString::fromStdString(except.getMessage()));
    }
}


// Fonctions de comportement des transactions ---------------------------------------------------------------------


void MainWindow::supprimerTransaction()
{
    try {
            if(transac_selectionne != nullptr
            && QMessageBox::StandardButton::No != QMessageBox::question(this,"Validation","Voulez-vous vraiment supprimer cette transaction ?"))
            {
                transaction_manager.supprimerTransaction(transac_selectionne->text().toStdString());
                afficherTransaction();
            }
    } catch(Exception e) {
        QMessageBox::warning(this,QString("Erreur"),QString("Suppression de la transaction impossible :\n")+QString::fromStdString(e.getMessage()));
    }
}


//Fonctions de comportement de la fenetre --------------------------------------------------------------------------


void MainWindow::setSizeObjects()
{
    int const espace = 6;
    int const btn_height = 23;
    int const cmpt_width = this->width()/5;

    //arborescence
        QSize btn_cmpt_size((cmpt_width-espace)/2,btn_height);
        design->arborescenceCompte->setFixedSize(cmpt_width,
               this->height()-design->barMenu->height()-design->barStatut->height()-btn_cmpt_size.height()-3*espace);
        design->arborescenceCompte->move(espace,espace);
        design->creerComptePushButton->setFixedSize(btn_cmpt_size);
        design->creerComptePushButton->move(espace,design->arborescenceCompte->height()+2*espace);
        design->supprComptePushButton->setFixedSize(btn_cmpt_size);
        design->supprComptePushButton->move(btn_cmpt_size.width()+2*espace,design->arborescenceCompte->height()+2*espace);
        design->arborescenceCompte->setColumnWidth(0,cmpt_width+espace); // on cache la colonne ID

    //onglets
        design->groupeOnglets->setFixedSize(this->width()-cmpt_width-3*espace,
              this->height()-design->barMenu->height()-design->barStatut->height()-2*espace);
        design->groupeOnglets->move(cmpt_width+2*espace,espace);

    //onglet transaction
    int const demi_onglet_width = design->groupeOnglets->width()/2;
    int const btn_trns_width = (demi_onglet_width-2*espace)/3-espace;
        design->tableauTransaction->setFixedSize(design->groupeOnglets->width()-3*espace,
               design->groupeOnglets->height()-2*btn_height-3*espace);
        design->tableauTransaction->move(espace,espace);
        design->creerTransacPushButton->setFixedSize(btn_trns_width,btn_height);
        design->creerTransacPushButton->move(demi_onglet_width,design->tableauTransaction->height()+2*espace);
        design->supprTransacPushButton->setFixedSize(btn_trns_width,btn_height);
        design->supprTransacPushButton->move(demi_onglet_width+btn_trns_width+espace,
               design->tableauTransaction->height()+2*espace);
        design->modifTransacPushButton->setFixedSize(btn_trns_width,btn_height);
        design->modifTransacPushButton->move(demi_onglet_width+2*btn_trns_width+2*espace,
               design->tableauTransaction->height()+2*espace);
    int const column_trs_width_unity = design->tableauTransaction->width()/10; //         = 10x
        design->tableauTransaction->setColumnWidth(0,column_trs_width_unity); //Date          x
        design->tableauTransaction->setColumnWidth(1,column_trs_width_unity*2); //Reference  2x
        design->tableauTransaction->setColumnWidth(2,column_trs_width_unity*3); //Intitule   3x
        design->tableauTransaction->setColumnWidth(3,column_trs_width_unity*2); //Compte     2x
        design->tableauTransaction->setColumnWidth(4,column_trs_width_unity); //Debit         x
        design->tableauTransaction->setColumnWidth(5,column_trs_width_unity); //Credit        x

    //onglet compte
        design->tableauCompte->setFixedSize(design->groupeOnglets->width()-3*espace,
               design->groupeOnglets->height()-3*btn_height-4*espace);
        design->tableauCompte->move(espace,2*(btn_height+espace));
        design->nomCompte->setFixedSize(demi_onglet_width-(3*espace)/2,2*btn_height);
        design->nomCompte->move(espace,espace);
        design->posteCompte->setFixedSize(demi_onglet_width-(3*espace)/2,btn_height);
        design->posteCompte->move(design->nomCompte->width()+(3*espace)/2,espace);
        design->dateRapprochementCompte->setFixedSize(demi_onglet_width-(3*espace)/2,btn_height);
        design->dateRapprochementCompte->move(design->nomCompte->width()+(3*espace)/2,btn_height+2*espace);        
    int const column_cmpt_width_unity = design->tableauCompte->width()/9; //          = 9x
        design->tableauCompte->setColumnWidth(0,column_cmpt_width_unity); //Date         x
        design->tableauCompte->setColumnWidth(1,column_cmpt_width_unity*2); //Reference 2x
        design->tableauCompte->setColumnWidth(2,column_cmpt_width_unity*3); //Intitule  3x
        design->tableauCompte->setColumnWidth(3,column_cmpt_width_unity); //Debit        x
        design->tableauCompte->setColumnWidth(4,column_cmpt_width_unity); //Credit       x
        design->tableauCompte->setColumnWidth(5,column_cmpt_width_unity); //Solde        x
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    setSizeObjects();
}


// Fonctions liées au chargement --------------------------------------------------------------------------

void MainWindow::chargerContexte(string const& _path)
{
    // Ouverture du fichier
      QFile qfile(QString::fromStdString(_path));
      if (!qfile.open(QIODevice::ReadOnly))
      {
          throw ExceptionFichier("[!]Impossible d'ouvrir le fichier suivant en lecture : " + _path,
                                              ExceptionFichier::CodeExcepFichier::UFND_EXC_F);

      }

      QDomDocument xml;
      xml.setContent(&qfile);
      qfile.close();

      // save > CompteManager > TransactionManager > contexte
      QDomNode actual = xml.documentElement().firstChild().nextSibling().nextSibling();

      QDomElement contexte = actual.toElement();
      devise = contexte.attribute(QString("devise"));
      formatDate = contexte.attribute(QString("formatDate"));
}

void MainWindow::charger(QString fichier)
{
    try
    {
        compte_manager.charger(fichier.toStdString());
        chargerContexte(fichier.toStdString());
    }
    catch (Exception except)
    {
        QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
        this->show();
    }

    afficherTransaction();
    this->show();
}

void MainWindow::initialiser()
{
    afficherHierarchie();
    afficherFormulaireCompte();
    this->show();
}

void MainWindow::ajouterContexte (string const& _path)
{
    // Ouverture du fichier
     QFile qfile(QString::fromStdString(_path));
     if (!qfile.open(QIODevice::ReadOnly))
     {
         throw ExceptionFichier("[!]Impossible d'ouvrir le fichier suivant en lecture : " + _path,
                                           ExceptionFichier::CodeExcepFichier::UFND_EXC_F);

     }
     QDomDocument xml;
     xml.setContent(&qfile);

     qfile.close();
     // on crée un élément dans le document
     QDomElement contexte = xml.createElement("contexte");
     contexte.setAttribute(QString("devise"),devise);
     contexte.setAttribute(QString("formatDate"),formatDate);

     //on ajoute le nouvel élément au bon endroit
     xml.documentElement().appendChild(contexte);

     //réouverture en écriture du document (sinon on se retrouve à append le document au lieu de le réécrire car le curseur est placé à la fin du doc)
     if (!qfile.open(QIODevice::WriteOnly))
     {
         throw ExceptionFichier("[!]\tExceptionFichier\tImpossible d'ouvrir le fichier suivant en écriture : " + _path,
                                           ExceptionFichier::CodeExcepFichier::UFND_EXC_F);

     }
     qfile.write(xml.toString().toStdString().c_str());// on transforme le doc en c_str qui peut ensuite être écrite dans le doc
     qfile.flush();

     qfile.close();
}

void MainWindow::sauvegarder(QString fichier)
{
    try {
        compte_manager.sauver(fichier.toStdString());
        ajouterContexte(compte_manager.getPath());
        this->show();
    } catch (Exception & except) {
        QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
        this->show();
    }
}


// Destructeur --------------------------------------------------------------------------------------------


MainWindow::~MainWindow()
{
    // Sauvegarde
    try{
        compte_manager.sauver(compte_manager.getPath());
        ajouterContexte(compte_manager.getPath());
    } catch (ExceptionFichier& e){
        QMessageBox::warning(this, QString("Erreur"), QString::fromStdString(e.getMessage()));

    }
    delete design;
}
