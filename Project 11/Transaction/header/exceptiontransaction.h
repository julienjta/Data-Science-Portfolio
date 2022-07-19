#ifndef EXCEPTIONTRANSACTION_H_INCLUDED
#define EXCEPTIONTRANSACTION_H_INCLUDED

/**
    @file exceptiontransaction.h
    @brief Objet représentant les exceptions intervenant lors de manipulations de
        transactions
    @author Jérémy Godde
    @version v3
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note hérite de la classe exception "exception.h"
*/

#include "../../Compte/header/ExceptionCompte.h"

/**
    @class ExceptionTransaction "exceptiontransaction.h"
    @brief traite les exceptions de la partie transaction
*/
class ExceptionTransaction : public Exception
{
    public:
        /**
            @enum ExceptionTransaction::CodeExcepTransaction
            @brief énumération des codes d'erreur possible pour les ExceptionTransaction, prenant des valeurs entre 40 et 59 incluses
        */
        enum CodeExcepTransaction
        {
            /**
                @brief 40 : une exception inconnue
            */
            UKWN_EXC_T = 40,
            /**
                @brief 41 : exception levée pour un problème d'allocation mémoire
            */
            MEMO_EXC_T = 41,
            /**
                @brief 42 : exception levée lorsqu'un résultat ne correspond pas aux régles imposées par la logique de l'application
            */
            RULE_EXC_T = 42,
            /**
                @brief 43 : exception levée lorsqu'un pointeur NULLPTR est non-attendu
            */
            NULL_EXC_T = 43,
            /**
                @brief 44 : exception levée lorsqu'une boucle de recherche ne trouve aucun l'élément
            */
            SRCH_EXC_T = 44
        };
        /**
            @fn ExceptionTransaction::ExceptionTransaction(string const& _message, CodeExcepTransaction const& _code_erreur = CodeExcepTransaction::UKWN_EXC_T) noexcept;
            @brief Constructeur, hérite de Exception.
            @param _message : string, message d'erreur expliquant l'exception
            @param _code_erreur : CodeExcepTransaction, code d'erreur permettant le traitement de l'exception
        */
        explicit ExceptionTransaction(string const& _message, CodeExcepTransaction const& _code_erreur = CodeExcepTransaction::UKWN_EXC_T) noexcept : Exception(_message,_code_erreur){}

    private:
};

/**
    @class ExceptionFichier "exceptiontransaction.h"
    @brief traite les exceptions de la partie fichier.
*/
class ExceptionFichier : public Exception
{
    public:
        /**
            @enum ExceptionFichier::CodeExcepFichier
            @brief énumération des codes d'erreur possible pour les ExceptionFichier, prenant des valeurs entre 60 et 79 incluses.
        */
        enum CodeExcepFichier
        {
            /**
                @brief 60 : une exception inconnue
            */
            UKWN_EXC_F = 60,
            /**
                @brief 61 : le fichier est introuvable ou inaccessible
            */
            UFND_EXC_F = 61,
            /**
                @brief 62 : le fichier présente une syntaxe incorrecte
            */
            SNTX_EXC_F = 62
        };
        /**
            @fn ExceptionFichier::ExceptionFichier(string const& _message, CodeExcepFichier const& _code_erreur = CodeExcepFichier::UKWN_EXC_F) noexcept;
            @brief Constructeur, hérite de Exception.
            @param _message : string, message d'erreur expliquant l'exception
            @param _code_erreur : CodeExcepFichier, code d'erreur permettant le traitement de l'exception
        */
        explicit ExceptionFichier(string const& _message, CodeExcepFichier const& _code_erreur = CodeExcepFichier::UKWN_EXC_F) noexcept : Exception(_message,_code_erreur){}

    private:
};

#endif // EXCEPTIONTRANSACTION_H_INCLUDED
