/**
    @file deplacercompte.cpp
    @brief définition des fonctions membres de la classe deplacercompte.
    @author Ophélie Delattre
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "deplacercompte.h"
#include "ui_deplacercompte.h"
#include "mainwindow.h"

deplacercompte::deplacercompte(std::list<int> const _liste_id,MainWindow *parent) :
    QDialog(parent),
    liste_id(_liste_id),
    design(new Ui::deplacercompte)
{
    design->setupUi(this);

    //initialiser les listes
    CompteHierarchie * c;
    for(auto it_id = liste_id.begin();it_id != liste_id.end();it_id++){
            c = CompteManager::getInstance().getCompte(*(it_id));
            if (c->getType()==VIRTUEL){
                    design->pereDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
                   if (*it_id != 0){ //si ce n'est pas la racine
                       design->compteDeroulant->addItem(QString::fromStdString(c->toString()+" [dossier]"),QVariant(*it_id));
                   }
            }else if (c->getType()==REEL){
                design->compteDeroulant->addItem(QString::fromStdString(c->toString()),QVariant(*it_id));
            }
    }

    //connexion des signaux
    connect(design->Valider, SIGNAL(clicked()), this, SLOT(deplacementcompte()));
    connect(design->Quitter, SIGNAL(clicked()), this, SLOT(reject()));
}

void deplacercompte::deplacementcompte(){
    int fils;
    int pere;
    try{
        fils = design->compteDeroulant->currentData().toInt();
        pere =design->pereDeroulant->currentData().toInt();
        CompteManager::getInstance().deplacerFils(fils,pere);
    }catch (Exception &except) {
        QMessageBox::warning(this,QString("Erreur"),QString::fromStdString(except.getMessage()));
        return;
    }
    QMessageBox::information(this,QString("Information"),"Votre compte a bien été déplacé");
    emit deplacement();
    accept();

}

deplacercompte::~deplacercompte()
{
    delete design;
}
