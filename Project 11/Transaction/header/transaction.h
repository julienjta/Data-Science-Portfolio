#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED

/**
    @file transaction.h
    @brief La transaction représente un ensemble d'opérations équilibrées effectuées
        à une même date entre plusieurs comptes
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning NON COMPILE
    @note aucune
*/

#include "../header/operation.h"

/**
    @class Transaction "transaction.h"
    @brief La transaction représente un ensemble d'opérations équilibrées effectuées
        à une même date entre plusieurs comptes
*/
class Transaction
{
    friend TransactionBuilder;
    friend CompteManager;

    public:
    /**
        @fn  bool Transaction::operator<(Transaction* _transaction_2) const noexcept
        @brief surchage de l'opérateur <, pour comprarer deux transactions : test sur la date.
    */
        bool operator<(Transaction* _transaction_2) const noexcept;
        /**
            @fn time_t Transaction::getDate()
            @brief Méthode pour obtenir la date de la transaction.
            @return la date de la transaction
        */
        time_t getDate() const noexcept;
        /**
            @fn string Transaction::getStringDate(string const& format) const noexcept
            @brief Méthode pour obtenir la date de la transaction au format string?
            @param format : string const&, format de souhaité pour la date
            @return la date de la transaction au format indiqué
        */
        string getStringDate(string const& format) const noexcept;
        /**
            @fn string Transaction::getReference() const noexcept
            @brief Méthode pour obtenir la référence de la transaction
            @return la référence de la transaction
        */
        string getReference() const noexcept;
        /**
            @fn string Transaction::getMemo() const noexcept
            @brief Méthode pour obtenir le memo de la transaction.
            @return le memo de la transaction
        */
        string getMemo() const noexcept;
        /**
            @fn bool Transaction::getValide() const noexcept
            @brief vérifie si la transaction est rapprochée.
            @return true si la transaction est rapprochée, sinon false
        */
        bool getValide() const noexcept;
        /**
            @fn list<Operation*> const Transaction::getListeOperations() const noexcept
            @brief Méthode pour obtenir la liste des opérations de la transaction.
            @return la liste des opérations de la transaction
        */
         list<Operation*> const getListeOperations() const noexcept;

    private:
        //methodes=========================
        /**
            @fn Transaction::Transaction()
            @brief Constructeur par défaut
        */
        Transaction() = default;
        /**
            @fn Transaction::Transaction(time_t const& _date, string const& _ref, string const& _memo, bool const& _valide, list<Operation*> const& _listOperations) explicit
            @brief Constructeur
            @param _date : time_t, la nouvelle date de la transaction
            @param _ref : string, la nouvelle référence de la transaction
            @param _memo : string, le nouveau mémo de la transaction
            @param _valide : bool, marqueur de rapprochement de la transaction
            @param _listOperations : list<Operation*>, le nouvel ensemble des opérations formant la transaction
            @exception RULE_EXC_T non-équilibre des opérations
        */
        explicit Transaction(time_t const& _date, string const& _ref, string const& _memo, bool const& _valide, list<Operation*> const& _listOperations);
        /**
            @fn Transaction::Transaction()
            @brief Destructeur
        */
        ~Transaction();

        /**
            @fn void Transaction::setValide(bool _valide) noexcept
            @brief modifieur de l'attribut valide.
            @param _valide : bool, nouvelle valeur de l'attribut valide
        */
        void setValide(bool _valide) noexcept;

        //attributs========================
        /**
            @var time_t Transaction::date
            @brief la date de la transaction.
        */
        time_t date = 0;
        /**
            @var string Transaction::reference_transaction
            @brief la reference unique de la transaction.
        */
        string reference_transaction = ""; // les mots ref et reference sont des mots-clés c++
        /**
            @var string Transaction::memo
            @brief le memo de la transaction.
        */
        string memo = "";
        /**
            @var bool Transaction::valide
            @brief le marqueur de rapprochement de la transaction. Vaut true si rapprochée, sinon false.
        */
        bool valide = false;
        /**
            @var list<Operation*> Transaction::operations
            @brief la liste des operations composant la transaction.
        */
        list<Operation*> operations;
};

/**
    @var bool compare(Transaction* const _transaction_1, Transaction* const _transaction_2) noexcept
    @brief compare deux pointeurs sur des transactions par rapport à leur date
*/
bool compare(Transaction* const _transaction_1, Transaction* const _transaction_2) noexcept;

#endif // TRANSACTION_H_INCLUDED
