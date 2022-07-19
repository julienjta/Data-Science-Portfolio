#ifndef EXCEPTIONCOMPTE_H_INCLUDED
#define EXCEPTIONCOMPTE_H_INCLUDED

/**
    @file ExceptionCompte.h
    @brief Regroupe les différentes exceptions de la partie comptes.
    @author Ophélie Delattre / Simon Lepage / Jérémy Godde
    @version v4
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
*/

#include "Exception.h"

/**
    @class ExceptionHierarchie "ExceptionCompte.h"
    @brief ExceptionHierarchie est créée lors d'une opération illégale sur la hiérarchie de comptes.
*/
class ExceptionHierarchie : public Exception{
public:
    /**
        @enum ExceptionHierarchie::CodeExcepHierarchie
        @brief énumération des codes d'erreur possible pour les ExceptionHiérarchie, prenant des valeurs entre 0 et 19 incluses
    */
    enum CodeExcepHierarchie
    {
        /**
            @brief 0 : une exception inconnue
        */
        UKWN_EXC_H = 0,

        /**
            @brief 1 : Un type de Compte inconnue
        */
        TYPE_EXC_H = 1,

        /**
            @brief 2 : Un compte de Poste inconnu
        */
        POSTE_EXC_H = 2,

        /**
            @brief 3 : Ne respecte par les régles de création d'un compte : un père virtuel et doit être de même poste que le père
        */
        RULE_EXC_H = 3,

        /**
            @brief 4 : Tentative d'accés à un compte non présent dans la hiérarchie.
        */
        IDNF_EXC_H = 4,

        /**
            @brief 5 : Tentative d'accéder ou manipuler les fils d'un compte réel
        */
        FLSR_EXC_H = 5,
        /**
          @brief 6 : Compte n'existe pas
         */
        COMPT_EXC_H = 6,
        /**
          @brief 7 : Compte ne respecte pas les caractéristiques d'un compte de Capitaux Propre
         */
        CAPP_EXC_H = 7,

        /**
          @brief 8 : Compte ne respecte pas les caractéristiques d'un compte de Cloture
         */
        CLOT_EXC_H = 8,

        /**
          @brief 9 : Compte ne respecte pas caractéristiques d'un compte Excedent
         */
        EXCE_EXC_H = 9,

        /**
          @brief 10 : Compte ne respecte pas caractéristiques d'un compte Deficit
         */
        DEFI_EXC_H = 10,
        /**
          @brief 11 : Tentative de déplacer un compte sous un de ses fils.
        */
        DSON_EXC_H = 11,
        /**
          @brief 12 : Tentative de déplacer un compte sous lui-même.
        */
        DSELF_EXC_H = 12,

    };
    /**
        @fn ExceptionHierarchie::ExceptionHierarchie(string _s, CodeExcepHierarchie _code_erreur = CodeExcepHierarchie::UKWN_EXC_H);
        @brief Constructeur à partir d'un message d'erreur.
    */
    ExceptionHierarchie(string _s, CodeExcepHierarchie _code_erreur = CodeExcepHierarchie::UKWN_EXC_H) noexcept : Exception(_s, _code_erreur){}
};

/**
    @class ExceptionComptabilite "ExceptionCompte.h"
    @brief ExceptionComptabilite est créée lors d'une opération de comptabilité illégale.
*/
class ExceptionComptabilite  : public Exception{
public:
    /**
        @enum ExceptionComptabilite::CodeExcepComptabilite
        @brief énumération des codes d'erreur possible pour les ExceptionComptabilite, prenant des valeurs entre 20 et 39 incluses
    */
    enum CodeExcepComptabilite
    {
        /**
            @brief 20 : une exception inconnue
        */
        UKWN_EXC_C = 20,

        /**
            @brief 21 : Tentative de manipuler les mementos d'un CompteVirtuel.
        */
        MEMV_EXC_C = 21,

        /**
            @brief 22 : Tentative de manipulation du solde sur la racine
        */
        ROOT_EXC_C = 22,

        /**
            @brief 23 : Tentative de suppression d'un compte virtuel qui a des fils
        */
        SUPVIR_EXC_C=23,

        /**
            @brief 24 : Tentative de suppression d'un compte reel qui a des transactions
        */
        SUPREL_EXC_C=24,
        /**
          @brief 25 : Relevé date saisie incorrects
        */
        RELEV_EXC_C = 25
    };
    /**
        @fn ExceptionComptabilite::ExceptionComptabilite(string _s, CodeExcepComptabilite _code_erreur = CodeExcepComptabilite::UKWN_EXC_C);
        @brief Constructeur à partir d'un message d'erreur.
    */
    ExceptionComptabilite(string _s, CodeExcepComptabilite _code_erreur = CodeExcepComptabilite::UKWN_EXC_C) noexcept : Exception(_s, _code_erreur){}
};


#endif // EXCEPTIONCOMPTE_H_INCLUDED
