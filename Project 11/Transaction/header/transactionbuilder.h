#ifndef TRANSACTIONBUILDER_H_INCLUDED
#define TRANSACTIONBUILDER_H_INCLUDED

/**
    @file transactionbuilder.h
    @brief Le transaction builder sert à construire les transactions
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucune
*/

#include "../header/transaction.h"

/**
    @class TransactionBuilder "transactionmanager.h"
    @brief Le transaction builder permet de construire les transactions. Il utilise le pattern builder et singleton
*/
class TransactionBuilder
{
    friend TransactionManager;
    private:
        //methodes=========================
        /**
            @fn TransactionBuilder::TransactionBuilder()
            @brief Constructeur, en tant que singleton ce dernier est privé
        */
        TransactionBuilder();
        /**
            @fn TransactionBuilder::~TransactionBuilder()
            @brief Destructeur
        */
        ~TransactionBuilder();
        /**
            @var static void TransactionBuilder::detruireTransaction(Transaction* const _transaction) noexcept
            @brief detruit la liste de transaction passée en paramètre.
            @param _transaction : Transaction*, transaction à détruire
        */
        static void detruireTransaction(Transaction* const _transaction) noexcept;
        /**
            @fn static Transaction* TransactionBuilder::creerTransaction(time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _listOperations)
            @brief Méthode qui permet d'ajouter une nouvelle transaction.
            @param _date : time_t, la date de la transaction à  créer
            @param _ref : string, la référence de la transaction à créer
            @param _memo : string, le mémo de la transaction à  créer
            @param _listOperations : list<Operation*>, ensemble des opérations formant la transaction à  créer
            @exception MEMO_EXC_T exception d'allocation mémoire
            @exception RULE_EXC_T non-équilibre des opérations
            @exception RULE_EXC_T liste vide d'opérations
            @return retourne un pointeur sur la transaction nouvellement créée
        */
        static Transaction* creerTransaction(time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _listOperations);
        /**
            @fn static list<Transaction*> TransactionBuilder::creerTransactionAvecFichier(string const& _path)
            @brief Méthode qui permet de convertir la sauvegarde en une liste de transactions.
            @param _path : string const, le chemin vers le fichier de sauvegarde contenant les transactions
            @exception UNFD_EXC_F exception d'accés au fichier
            @exception SNTX_EXC_F exception de syntaxe du fichier
            @exception RULE_EXC_T exception d'opération : le débit et le crédit sont tous les deux nuls
            @exception RULE_EXC_T exception d'opération : non-équilibre des opérations
            @exception NULL_EXC_T exception d'opération : passage d'un compte nul
            @exception MEMO_EXC_T exception d'allocation mémoire
            @return retourne une liste de pointeurs sur les transactions
        */
        static list<Transaction*> creerTransactionAvecFichier(string const& _path);
        /**
            @fn static Operation* TransactionBuilder::creerOperation(CompteHierarchie* const& _compte,double const& _debit, double const& _credit)
            @brief Méthode qui permet d'ajouter une nouvelle opération
            @param _compte : CompteHierarchie*, pointeur sur le compte correspondant qui doit être réel
            @param _debit : double, correspond au montant à débiter
            @param _credit : double, correspondant au montant à  créditer
            @exception NULL_EXC_C exception d'opération : passage d'un compte nul
            @exception RULE_EXC_T exception d'opération : crédit et débit sont tous les deux nuls
            @exception RULE_EXC_T passage d'un compte non réel
            @return retourne un pointeur sur l'opération nouvellement créée
        */
        static Operation* creerOperation(CompteHierarchie* const _compte,double const& _debit, double const& _credit);
};

#endif // TRANSACTIONBUILDER_H_INCLUDED
