#ifndef POSTEAD_H_INCLUDED
#define POSTEAD_H_INCLUDED

/**
    @file PosteAD.h
    @brief PosteAD est la classe mère des postes de compte : Actif et Depense.
        Nous avons choisi de regrouper ces deux postes car ils ont un comportement semblable pour les méthodes créditer et débiter.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/Racine.h"

/**
    @class PosteAD "PosteAD.h"
    @brief PosteAD est la classe mère des postes de compte : Actif et Depense. Elle a pour but de définir les méthodes créditer et débiter qui sont communes à ces deux classes.
*/

class PosteAD : public PosteCompte{
public :
    /**
        @fn virtual void PosteAD::debiter(double* _solde, double _montant)const noexcept override;
        @brief Redéfinition de la méthode debiter de PosteCompte. Cette méthode permet de débiter de l'argent d'un compte actif ou de dépenses, c'est-à-dire qu'elle augmente le solde d'un de ces comptes.
        @param _solde : double*, pointeur sur le solde du compte que l'on veut débiter.
        @param _montant : double, montant que l'on veut débiter du compte.
    */
    void debiter(double* _solde, double _montant) const noexcept override {*_solde += _montant;}
 /**
        @fn virtual void PosteAD::crediter(double* _solde, double _montant)const noexcept override;
        @brief Redéfinition de la méthode crediter de PosteCompte. Cette méthode permet de créditer de l'argent sur compte actif ou de dépenses, c'est-à-dire qu'elle diminue le solde d'un de ces comptes.
        @param _solde : double*, pointeur sur le solde du compte que l'on veut créditer.
        @param _montant : double, montant que l'on veut créditer sur compte.
    */
    void crediter(double* _solde, double _montant) const noexcept override {*_solde -= _montant;}
};

#endif // POSTEAD_H_INCLUDED
