#ifndef POSTEPR_H_INCLUDED
#define POSTEPR_H_INCLUDED

/**
    @file PostePR.h
    @brief PostePR est la classe mère des postes de compte : Recette et Passif.
        Nous avons choisi de regrouper ces deux postes car ils ont un comportement semblable pour les méthodes crediter et debiter.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/PosteAD.h"

/**
    @class PostePR "PostePR.h"
    @brief PostePR est la classe mère des postes de compte : Recette et Passif. Elle a pour but de définir les méthodes créditer et débiter qui sont communes à ces deux classes.
*/
class PostePR : public PosteCompte{
public:
    /**
        @fn virtual void PostePR::debiter(double* _solde, double _montant)const noexcept override;
        @brief Redéfinition de la méthode debiter de PosteCompte. Cette méthode permet de débiter de l'argent d'un compte passif ou de recette, c'est-à-dire qu'elle diminue le solde d'un de ces comptes.
        @param _solde : double*, pointeur sur le solde du compte que l'on veut débiter.
        @param _montant : double, montant que l'on veut débiter du compte.
    */
    void debiter(double* _solde, double _montant) const noexcept override {*_solde -= _montant;}
    /**
        @fn virtual void PostePR::crediter(double* _solde, double _montant)const noexcept override;
        @brief Redéfinition de la méthode crediter de PosteCompte. Cette méthode permet de créditer de l'argent sur compte passif ou de recette, c'est-à-dire qu'elle augmente le solde d'un de ces comptes.
        @param _solde : double*, pointeur sur le solde du compte que l'on veut créditer.
        @param _montant : double, montant que l'on veut créditer sur compte.
    */
    void crediter(double* _solde, double _montant) const noexcept override {*_solde += _montant;}
};
#endif // POSTEPR_H_INCLUDED
