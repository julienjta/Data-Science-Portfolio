#ifndef VISITEURGETSOLDE_H_INCLUDED
#define VISITEURGETSOLDE_H_INCLUDED

/**
    @file VisiteurGetSolde.h
    @brief VisiteurGetSolde est un visiteur d'afficher le solde des comptes en parcourant la hiérarchie des comptes.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/VisiteurFree.h"

/**
    @class VisiteurGetSolde "VisiteurGetSolde.h"
    @brief VisiteurGetSolde est un visiteur qui permet de libérer la mémoire dans des comptes.
*/


class VisiteurGetSolde : public Visiteur{
    friend CompteManager;
    public:
    /**
        @fn void VisiteurGetSolde::visiter(CompteReel& _c)noexcept override;
        @brief Méthode qui permet de calculer le solde d'un compte réel.
        @param _c : CompteReel& _c,CompteReel auquel le visiteur veut avoir accés pour calculer son solde.
    */
     void visiter (CompteReel& _c) noexcept override;

    /**
        @fn void VisiteurGetSolde::visiter(CompteVirtuel &_c)noexcept override;
        @brief Méthode qui permet de calculer le solde d'un compte virtuel en faisant la somme des soldes de ses comptes fils.
        @param _c : CompteVirtuel& _c,CompteVirtuel auquel le visiteur veut avoir accés pour calculer son solde.
    */
    void visiter(CompteVirtuel& _c) noexcept override;

    /**
        @fn int VisiteurGetSolde::getSolde() const noexcept;
        @brief Méthode qui permet d'obtenir le solde du compte demandé s'il existe.
        @return Le solde du compte si le nom correspond à un compte existant déclenche une exception sinon.
    */
    double getSolde() const noexcept {return solde;}

private:
    /**
        @var int VisiteurGetSolde::solde
        @brief Solde du compte.
    */
    double solde = 0.;

    /**
        @fn VisiteurGetSolde::VisiteurGetSolde();
        @brief Constructeur privé.
    */
    VisiteurGetSolde() : Visiteur() {};
    /**
        @fn  VisiteurGetSolde::VisiteurGetSolde(const VisiteurGetSolde& _v);
        @brief Constructeur par recopie privé
        @param _v : const VisiteurGetSolde&, référence constante sur le VisiteurGetSolde à recopier.
    */
    VisiteurGetSolde (const VisiteurGetSolde& _v) = default;

    /**
        @fn  VisiteurGetSolde& VisiteurGetSolde::operator=(const VisiteurGetSolde& _v);
        @brief Suppresion de surcharge de l'opérateur d'affectation privé.
        @param _v : const VisiteurGetSolde&, référence constante sur le VisiteurGetSolde à affecter.
    */
    VisiteurGetSolde& operator=(const VisiteurGetSolde& _v) = delete;


};



#endif // VISITEURGETSOLDE_H_INCLUDED
