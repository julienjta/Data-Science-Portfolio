/**
    @file ajouterwindow.cpp
    @brief définition des fonctions membres de la classe ajouterwindow.
    @author Ophélie Delattre
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "ajouterwindow.h"
#include "ui_ajouterwindow.h"
#include "mainwindow.h"

ajouterwindow::ajouterwindow(std::list<int> const _liste_id,QTreeWidgetItem * _compte_selectionne, MainWindow *parent) :
    QDialog(parent),
    cm(CompteManager::getInstance()),
    liste_id(_liste_id),
    design(new Ui::fenetreAjouterCompte)
{
    QString devise = QString("€");
    if (dynamic_cast<MainWindow*>(parent) != nullptr)
    {
        devise = dynamic_cast<MainWindow*>(parent)->getDevise();
    }
    //on cache les attributs
    design->setupUi(this);
    design->titreCompteLabel->setVisible(false);
    design->soldeLabel->setVisible(false);
    design->soldeCompteur->setVisible(false);
    design->compteInitalisateurLabel->setVisible(false);
    design->compteInitialisateurDeroulant->setVisible(false);
    design->nomLabel2->setVisible(false);
    design->nouveaulabel->setVisible(false);
    design->CPLineEdit->setVisible(false);
    design->Dossierlabel2->setVisible(false);
    design->nvPereCPDeroulant->setVisible(false);

    //mise à jour de la monnaie
    design->soldeCompteur->setSuffix(devise);

    //rempli QComboBox Nom
    int id = -1;
     CompteHierarchie *c;

     selecteurs = new QComboBox(this);
     QLabel* nameLabel = new QLabel(tr("Dossier"));
     std::list<int>::const_iterator it_id = liste_id.begin();

     design->formulaireLayout->insertRow(0,nameLabel,selecteurs);

     //On récupère le compte sélectionner dans l'arbre : si c'est un compte virtuel on le met par défaut comme choix de père
    if (_compte_selectionne != nullptr){
        id = _compte_selectionne->text(1).toInt();
        try {
             c = cm.getCompte(id);
             if (c->getType()==VIRTUEL){
                 selecteurs->addItem(QString::fromStdString(c->toString()),QVariant(id));
             }else{
                id =-1;
             }
        } catch (Exception &e) {
            id = -1;
     }
    }

    //rempli QComboBox Capitaux Propre + nouveau + Nom
    for(it_id = liste_id.begin();it_id != liste_id.end();it_id++){
        c = cm.getCompte(*(it_id));
        if ((*it_id)==0){
            if ((*it_id)!=id) {//si ce n'était pas le compte sélectionné
                selecteurs->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
            }
            design->nvPereCPDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
        }else if (c->getType()==VIRTUEL){// si ce n'était pas le compte sélectionné
                if ((*it_id)!=id) {
                    selecteurs->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
                 }
                   if (c->getPoste()==PASSIF){
                        design->nvPereCPDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
                     }
              }else if (c->getType()==REEL && c->getPoste()==PASSIF){
                        design->compteInitialisateurDeroulant->addItem( QString::fromStdString(c->toString()),QVariant(*it_id));
        }
    }
    design->compteInitialisateurDeroulant->addItem("Nouveau",QVariant(-1));

    //solde
    design->soldeCompteur->setDecimals(2);
    design->soldeCompteur->setSingleStep(0.01);
    design->soldeCompteur->setMinimum(0.00);
    design->soldeCompteur->setMaximum(10000.00);

    //connexion des signaux
    //selection capitaux propre
    connect(design->posteDeroulant, SIGNAL(currentIndexChanged(int)), this, SLOT(capitauxpropre()));
    connect(design->typeDeroulant, SIGNAL(currentIndexChanged(int)), this, SLOT(capitauxpropre()));
    //creation capitaux propre
    connect(design->compteInitialisateurDeroulant, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(nvcapitauxpropre(const QString&)));
    connect(design->boutonsDialog,SIGNAL(accepted()),this,SLOT(ajouterCompte())); //bouton OK
    connect(design->boutonsDialog,SIGNAL(rejected()),this,SLOT(close())); //bouton close
}

void ajouterwindow::capitauxpropre(){
    //si compte actif ou passif et reel
  if ((design->posteDeroulant->currentIndex()==0 ||  design->posteDeroulant->currentIndex()==1)&&(design->typeDeroulant->currentIndex()==1)){
          design->titreCompteLabel->setVisible(true);
          design->soldeLabel->setVisible(true);
          design->soldeCompteur->setVisible(true);
          design->compteInitalisateurLabel->setVisible(true);
          design->compteInitialisateurDeroulant->setVisible(true);
       if (design->compteInitialisateurDeroulant->currentText()=="Nouveau"){
           design->nomLabel2->setVisible(true);
           design->nouveaulabel->setVisible(true);
           design->CPLineEdit->setVisible(true);
           design->Dossierlabel2->setVisible(true);
           design->nvPereCPDeroulant->setVisible(true);
       }
  }else{
      design->titreCompteLabel->setVisible(false);
      design->soldeLabel->setVisible(false);
      design->soldeCompteur->setVisible(false);
      design->compteInitalisateurLabel->setVisible(false);
      design->compteInitialisateurDeroulant->setVisible(false);
      design->nomLabel2->setVisible(false);
      design->nouveaulabel->setVisible(false);
      design->CPLineEdit->setVisible(false);
      design->Dossierlabel2->setVisible(false);
      design->nvPereCPDeroulant->setVisible(false);

  }
}

void ajouterwindow::nvcapitauxpropre(const QString &text){
    //si on créer un nouveau compte de capitaux propre on affiche le formulaire de création sinon on le cache
    if (text=="Nouveau"){
        design->nomLabel2->setVisible(true);
        design->nouveaulabel->setVisible(true);
        design->CPLineEdit->setVisible(true);
        design->Dossierlabel2->setVisible(true);
        design->nvPereCPDeroulant->setVisible(true);
    }else{
        design->nomLabel2->setVisible(false);
        design->nouveaulabel->setVisible(false);
        design->CPLineEdit->setVisible(false);
        design->Dossierlabel2->setVisible(false);
        design->nvPereCPDeroulant->setVisible(false);
    }
}

ajouterwindow::~ajouterwindow()
{
    delete design;
}

void ajouterwindow::ajouterCompte(){
    //id nv fils
    int idnv;
    //id pere
    int pere;
    //poste
    Poste p;

    //on recupere le nom
    QString nom = design->nomLineEdit->text();

      if(nom.isEmpty()) //pas de nom
    {
        QMessageBox::warning(this,"Warning",
        "Veuillez renseigner un nom de compte");
        return;
    }

    std::string nomstring = nom.toStdString();

    //on vérifie que le père et le fils sont du même poste
    try {
        //recupere le pere
        pere = selecteurs->currentData().toInt();

        //recupere le poste
        int poste = design->posteDeroulant->currentIndex();
        p = Poste(poste);

        Poste p_pere = cm.getCompte(pere)->getPoste();


        if(p_pere != p && p_pere != RACINE)
        {
            QMessageBox::warning(this,QString("Erreur"),QString("Vous ne pouvez ajouter ce compte dans ce dossier, leur poste ne correspondent pas"));
            return;
        }
    } catch (Exception &except) {
        QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
        return;
    }

     //recuperer le type
     Type t;
     int type = design->typeDeroulant->currentIndex();
      t= Type(type);

     //gestion du compte actif passif avec initialisation des capitaux propres :
     double solde = 0.;
     QString np;
     CompteHierarchie* CapitauxPropre = nullptr;
     if ((design->posteDeroulant->currentIndex()==0 ||  design->posteDeroulant->currentIndex()==1)&&(design->typeDeroulant->currentIndex()==1)){
            solde = design->soldeCompteur->value();
             np= design->CPLineEdit->text();
            if (design->compteInitialisateurDeroulant->currentText()=="Nouveau"){ //on créer un nouveau compte de Capitaux propre
                CapitauxPropre=cm.gestionCapitauxPropre(true, design->nvPereCPDeroulant->currentData().toInt(), np);
                if (CapitauxPropre == nullptr){
                    QMessageBox::warning(this,"Erreur",
                             "Erreur lors de la création du compte de capitaux propre, veuillez compléter tous les champs et vérifier les informations saisies");
                    return;
                 }
                emit ajout();
            }else{//compte déjà existant
                CapitauxPropre=cm.gestionCapitauxPropre(false, design->compteInitialisateurDeroulant->currentData().toInt());
                //n'arrive jamais car la liste propose des compte passifs reel existants
                if (CapitauxPropre == nullptr){
                    QMessageBox::warning(this,"Erreur",
                             "Erreur le compte choisi est incorrect");
                    return;
                 }
            }

      }

     //tentative de création du compte
      try {
           //recupere id fils creer
           idnv = HierarchieBuilder::idcompte;
           cm.ajouterFils(pere, nomstring, t, p);
           emit ajout();
        } catch (Exception &except) {
            QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
            return;
        }

        // on gère les transaction d'initialisation si compte passif, actif et solde !=0
        if ((design->posteDeroulant->currentIndex()==0 ||  design->posteDeroulant->currentIndex()==1)&&(design->typeDeroulant->currentIndex()==1)){
            if (tool::double_equal(solde,0.)){
                QMessageBox::information(this,"Information",
                    "Aucune transaction n'a été creer car le solde est renseigné à 0");
                 accept();
                return;
            }

            std::list<Operation*> nouv_operations;
            TransactionManager& tm = TransactionManager::getInstance();

            //si passif on crédit pour avoir un solde le solde indiqué
            if (design->posteDeroulant->currentIndex()==0){
                tm.ajouterOperation(&nouv_operations,cm.getCompte(idnv),0.,solde);
                tm.ajouterOperation(&nouv_operations,CapitauxPropre,solde,0.);
             }else{//actif on débit pour avoir le solde indiqué
                tm.ajouterOperation(&nouv_operations,cm.getCompte(idnv),solde,0.);
                tm.ajouterOperation(&nouv_operations,CapitauxPropre,0.,solde);
             }

             try {
                 //cree transaction
                 tm.ajouterTransaction(std::time(nullptr),"INIT "+std::to_string(CompteManager::init),"Initialisation "+cm.getCompte(idnv)->getNom(),nouv_operations);
                 CompteManager::init++;
                 emit ajout();
            } catch (Exception &except) {
                        QMessageBox::warning(this,QString("Erreur le compte n'a pas pu être initialisé : le solde sera donc mis à 0"),QString::fromStdString(except.getMessage()));
                        return;
             }
         }


    accept();

}






