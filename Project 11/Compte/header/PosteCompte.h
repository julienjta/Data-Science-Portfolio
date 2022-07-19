#ifndef POSTECOMPTE_H_INCLUDED
#define POSTECOMPTE_H_INCLUDED

/**
    @file PosteCompte.h
    @brief PosteCompte est la classe mère des différentes postes de compte : Actif et Depense, Passif et Recette, et la Racine.
        Elle permet de manipuler tous les postes via la même interface
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/Originator.h"

/**
    @enum Poste, représente le nom du poste d'un Compte : Passif, Actif, Depense, Recette et la Racine.
*/
enum Poste {
    //! @var PASSIF marque un compte passif
    PASSIF = 0,
    //! @var ACTIF marque un compte actif
    ACTIF = 1,
    //! @var DEPENSE marque un compte depense
    DEPENSE = 2,
    //! @var RECETTE marque un compte recette
    RECETTE = 3,
    //! @var RACINE marque un compte racine
    RACINE = 4
};

/**
    @class PosteCompte "PosteCompte.h"
    @brief PosteCompte est la classe mère des différents postes de compte : Actif et Depense, Passif et Recette, et  la Racine.
*/
class PosteCompte{
public:
    /**
        @fn  virtual string PosteCompte::getLetter() const noexcept;
        @brief Méthode virtuelle qui permettra de renvoyer la première lettre de le nom du poste d'un compte.
        @return D si c'est un poste Depense, R si c'est poste Recette ou Racine, P si c'est un poste Passif, A si c'est un poste Actif.
    */
    virtual string getLetter() const noexcept = 0;

    /**
     @fn virtual Poste PosteCompte::getPoste() const noexcept;
     @brief Méthode qui permet de retourner le nom du poste d'un PosteCompte.
     @return ACTIF si c'est un Actif, PASSIF si c'est un Passif, RECETTE si c'est un Recette, DEPENSE si c'est un Depense ou RACINE si c'est la racine.
    */
    virtual Poste getPoste() const noexcept = 0;

    /**
        @fn virtual void PosteCompte::debiter const (double* _solde, double _montant);
        @brief Méthode qui permet de débiter de l'argent d'un un compte. Cette méthode sera redéfinie dans les sous-classes.
        @param _solde : double*, pointeur sur le solde du compte que l'on veut créditer.
        @param _montant : double, montant que l'on veut débiter du compte.
        @exception ROOT_EXC_C Lancement d'ExceptionComptabilité : Impossible de débiter le compte racine.
    */
    virtual void debiter(double* _solde, double _montant)const = 0;

    /**
        @fn virtual void PosteCompte::crediter const(double* _solde, double _montant);
        @brief Méthode qui permet de créditer de l'argent sur un un compte. Cette méthode sera redéfinie dans les sous-classes.
        @param _solde : double*, pointeur sur le solde du compte que l'on veut créditer.
        @param _montant : double, montant que l'on veut créditer sur compte.
        @exception ROOT_EXC_C Lancement d'ExceptionComptabilité : Impossible de crediter le compte racine.
    */
    virtual void crediter(double* _solde, double _montant) const = 0;
};


#endif // POSTECOMPTE_H_INCLUDED
