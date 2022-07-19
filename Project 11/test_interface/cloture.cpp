/**
    @file cloture.cpp
    @brief définition des fonctions membres de la classe cloture.
    @author Ophélie Delattre
    @version v3
    @date 11 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "cloture.h"
#include "ui_cloture.h"
#include "mainwindow.h"

cloture::cloture(std::list<int> const _liste_id, MainWindow *parent) :
    QDialog(parent),
    cm(CompteManager::getInstance()),
    design(new Ui::cloture)
{
    design->setupUi(this);
    //initialise les liste déroulante
    CompteHierarchie *c;

    design->compteClotureDeroulant->addItem("Nouveau");
    for(auto it_id = _liste_id.begin();it_id != _liste_id.end();it_id++){
        c = cm.getCompte(*(it_id));
        if ((*it_id)==0){ //racine
            design->nouveauPereDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
        }else if (c->getPoste()==PASSIF){// si c'est un passif
                if (c->getType()==REEL) {// si il est réel
                    design->compteClotureDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
                 }else{//alors il est virtuel
                        design->nouveauPereDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
                }
      }
    }

    //connexion des signaux
    //selection compte capitaux propre
    connect(design->compteClotureDeroulant, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(nvcomptecloture(const QString&)));
    //realisation cloture
    connect(design->DialogbuttonBox,SIGNAL(accepted()),this,SLOT(fairecloture())); //bouton OK -> fonction verifierChamps()
    connect(design->DialogbuttonBox,SIGNAL(rejected()),this,SLOT(close())); //bouton close -> fonction fermer()

}

void cloture::nvcomptecloture(const QString &text){
    if (text=="Nouveau"){
        design->NvComptelabel->setVisible(true);
        design->line1->setVisible(true);
        design->line2->setVisible(true);
        design->perelabel->setVisible(true);
        design->nouveauPereDeroulant->setVisible(true);
        design->nomlabel->setVisible(true);
        design->nomLineEdit->setVisible(true);
        design->typelabel->setVisible(true);
        design->reellabel->setVisible(true);
        design->postelabel->setVisible(true);
        design->passiflabel->setVisible(true);
    }else{
         design->NvComptelabel->setVisible(false);
        design->line1->setVisible(false);
        design->line2->setVisible(false);
        design->perelabel->setVisible(false);
        design->nouveauPereDeroulant->setVisible(false);
        design->nomlabel->setVisible(false);
        design->nomLineEdit->setVisible(false);
        design->typelabel->setVisible(false);
        design->reellabel->setVisible(false);
        design->postelabel->setVisible(false);
        design->passiflabel->setVisible(false);
    }
}
cloture::~cloture()
{
    delete design;
}


void cloture::fairecloture(){
    //si l'utilisateur a choisi de créer un nouveau compte
    CompteHierarchie * resultat;
    try{
       if (design->compteClotureDeroulant->currentText()=="Nouveau"){
                 QString nomnv = design->nomLineEdit->text();
                 int idpere =design->nouveauPereDeroulant->currentData().toInt();
                 resultat = cm.gestionCompteResultat(true,idpere, nomnv);
       }else{
                int id =design->compteClotureDeroulant->currentData().toInt();
                resultat = cm.gestionCompteResultat(false,id);
       }
    } catch (Exception &e) {
        QMessageBox::warning(this,"Erreur",QString::fromStdString(e.getMessage()));
        return;
    }

   try{
        cm.cloturer(resultat);
    }catch(Exception &except){
        QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
        return;
    }
    //on met à jour hiérarchie des comptes et transaction
     emit ajout();
     emit ajouttransaction();
     accept();

}
