#ifndef VISITEURAFFICHAGE_H_INCLUDED
#define VISITEURAFFICHAGE_H_INCLUDED

/**
    @file VisiteurAffichage.h
    @brief VisiteurAffichage est un visiteur qui permet d'afficher la hiérarchie des comptes.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/visiteurlistecompte.h"

/**
    @class VisiteurAffichage "VisiteurAffichage.h"
    @brief VisiteurAffichage est un visiteur qui permet d'afficher la hiérarchie des comptes.
*/

class VisiteurAffichage : public Visiteur{
    friend CompteManager;
public:
    /**
        @fn void VisiteurAffichage::visiter(CompteReel& _c) noexcept;
        @brief Méthode qui permet de parcourir un CompteReel
        @param _c : CompteReel&, CompteReel auquel le visiteur veut avoir accés pour afficher ces informations.
    */
    void visiter(CompteReel& _c) noexcept;
    /**
        @fn void VisiteurAffichage::visiter(CompteVirtuel& _c) noexcept;
        @brief Méthode qui permet de parcourir un CompteVirtuel
        @param _c : CompteVirtuel&, CompteVirtuel auquel le visiteur veut avoir accés pour afficher ces informations.
    */
    void visiter(CompteVirtuel& _c) noexcept;

private:
    /**
        @fn void VisiteurAffichage::fillItem(CompteHierarchie& _c, QTreeWidgetItem* _item) noexcept{
        @brief Méthode qui permet de remplir un QTreeWidgetItem* avec les informations d'un compte.
        @param _c : CompteHierarchie* ,compte dont on veut récuprer les informations.
        @param _item : QTreeWidgetItem*, noeud à remplir
    */
    void fillItem(CompteHierarchie& _c, QTreeWidgetItem* _item) noexcept;
/**
        @fn VisiteurAffichage::VisiteurAffichage();
        @brief Constructeur privé
        @param _arbre : QTreeWidget* const, l'arbre dans lequel ajouter les comptes
        @param _devise : QString const&, la devise dans laquelle afficher les soldes
    */
    VisiteurAffichage(QTreeWidget* const _arbre,QString const& _devise) : arbre(_arbre), devise(_devise), actual_widget(nullptr) {}

    /**
        @fn  VisiteurAffichage::VisiteurAffichage(const VisiteurAffichage& _v);
        @brief Constructeur par recopie privé.
        @param _v : const VisiteurAffichage&, référence constante sur le VisiteurAffichage à recopier.
    */
    VisiteurAffichage (const VisiteurAffichage& _v) = default;

    /**
        @fn  VisiteurAffichage& VisiteurAffichage::operator=(const VisiteurAffichage& _v);
        @brief Suppression de surcharge de l'opérateur d'affectation privé.
        @param _v : const VisiteurAffichage&, réfrence constante sur le VisiteurAffichage affecter.
    */
    VisiteurAffichage& operator=(const VisiteurAffichage& _v) = delete;

    /**
       @fn VisiteurAffichage::~VisiteurAffichage();
       @brief Destructeur privé
   */
    ~VisiteurAffichage() = default;

    //attributs
    /**
        @var QTreeWidget* const VisiteurAffichage::arbre
        @brief Arbre dans lequel ajouter les comptes
    */
    QTreeWidget* const arbre;

    /**
        @var QString const VisiteurAffichage::devise
        @brief Devise dans laquelle les soldes sont affichés
    */
    QString devise;

    /**
        @var QTreeWidgetItem* VisiteurAffichage::actual_widget
        @brief Item sur lequel le visiteur travaille actuellement
    */
    QTreeWidgetItem* actual_widget;
};

#endif // VISITEURAFFICHAGE_H_INCLUDED
