/**
    @file VisiteurAffichage.cpp
    @brief Définition des fonctions membres de la classe VisiteurAffichage.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/CompteManager.h"

void VisiteurAffichage::visiter(CompteReel& _c) noexcept{
    QTreeWidgetItem* noeud = new QTreeWidgetItem(actual_widget);

    //les comptes réelles peuvent être activée, sélectionnés, déplacés et n'auront jamais d'enfant
    noeud->setFlags(
        Qt::ItemFlag::ItemIsDragEnabled |
        Qt::ItemFlag::ItemIsEnabled |
        Qt::ItemFlag::ItemIsSelectable |
        Qt::ItemFlag::ItemNeverHasChildren
    );

    fillItem(_c, noeud);
}

void VisiteurAffichage::visiter(CompteVirtuel& _c) noexcept{
    if(actual_widget == nullptr) // Si c'est le premier Item
    {
        //on crée une racine fantôme pour empêcher les drop au premier niveau
        QTreeWidgetItem* invisible_racine = arbre->invisibleRootItem();
        invisible_racine->setFlags( Qt::ItemFlag::ItemIsEnabled );
        //notre racine
        actual_widget = new QTreeWidgetItem(invisible_racine);
    }
    else
        actual_widget = new QTreeWidgetItem(actual_widget);
        
    actual_widget->setIcon(0,QIcon(":/ressources/dossier.png"));
    if(_c.getPoste() == RACINE)
    {
        //la racine peut être activée, sélectionnée et recevoir des fils
        actual_widget->setFlags(
            Qt::ItemFlag::ItemIsEnabled |
            Qt::ItemFlag::ItemIsSelectable |
            Qt::ItemFlag::ItemIsDropEnabled
        );
    }
    else{
        //les comptes virtuelles peuvent être activée, sélectionnés, déplacés et recevoir des fils
        actual_widget->setFlags(
            Qt::ItemFlag::ItemIsDragEnabled |
            Qt::ItemFlag::ItemIsEnabled |
            Qt::ItemFlag::ItemIsSelectable |
            Qt::ItemFlag::ItemIsDropEnabled
        );
    }

    fillItem(_c, actual_widget);

    for(auto it : _c.getFils()) it->accepte(*this);

    actual_widget = actual_widget->parent();
}

void VisiteurAffichage::fillItem(CompteHierarchie& _c, QTreeWidgetItem* _item) noexcept{
    double solde = CompteManager::getInstance().getSolde(_c.getId());
    QString qstr_solde = " "+QString::number(solde,'f',2)+" "+devise;

    _item->setText(0,QString::fromStdString(_c.toString())+qstr_solde);
    _item->setToolTip(0,"Solde actuel :"+qstr_solde);
    _item->setText(1,QString::number(_c.getId()));

    _item->setExpanded(true);
}
