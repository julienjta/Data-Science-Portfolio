#ifndef TRANSACTIONMANAGER_H_INCLUDED
#define TRANSACTIONMANAGER_H_INCLUDED

/**
    @file transactionmanager.h
    @brief Le transaction managager sert de porte d'entrée à toutes les opérations
        concernant les transactions
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucune
*/

#include "../../Compte/header/HierarchieBuilder.h"

/**
    @class TransactionManager "transactionmanager.h"
    @brief Le transaction managager permet de gérer les transactions. Elle est basée sur les pattern Manager et Singleton
*/
class TransactionManager
{
    public:
        /**
            @fn static TransactionManager& TransactionManager::getInstance() noexcept
            @brief Méthode qui permet d'accéder à l'instance du singleton.
            @return une référence sur l'instance du singleton
        */
        static TransactionManager& getInstance() noexcept;
        /**
            @fn list<Transaction*> TransactionManager::getListeTransactions() const noexcept
            @brief Méthode qui permet d'obtenir la liste de toute les transactions.
            @return la liste de toute les transactions
        */
        list<Transaction*> getListeTransactions() const noexcept;
        /**
            @fn Transaction* TransactionManager::getTransaction(string const& _ref) noexcept
            @brief Méthode qui permet d'accéder à une transaction depuis sa référence.
            @param _ref : string const, représente la référence de la transaction que l'on souhaite obtenir
            @return un pointeur sur la transaction si elle existe, nullptr sinon
        */
        Transaction* getTransaction(string const& _ref) noexcept;
        /**
            @fn void TransactionManager::affiche(QTableWidget* const _tableau, QString _devise, QString const& _format) noexcept
            @brief Méthode qui permet d'afficher toutes les transactions dans le tableau des transactions.
            @param _tableau : QTableWidget* const, représente le tableau dans lequel on souhaite afficher les transactions
            @param _devise : QString const&, devise utilisé pour les valeurs de monnaie
            @param _format : QString const&, format d'affichage de la date
        */
        void affiche(QTableWidget* const _tableau, QString const& _devise, QString const& _format) noexcept;
        /**
            @fn void TransactionManager::affiche(QTableWidget* const _tableau, QString _devise, QString const& _format) noexcept
            @brief Méthode permet d'afficher toutes opération d'un compte dans un tableau.
            @param _tableau : QTableWidget* const, représente le tableau dans lequel on souhaite afficher les opérations
            @param _compte : CompteHiearchie*, compte pour lequel on souhaite afficher les opérations
            @param _devise : QString const&, devise utilisé pour les valeurs de monnaie
            @param _format : QString const&, format d'affichage de la date
        */
        void affiche(QTableWidget* const _tableau,CompteHierarchie* _compte, QString const& _devise, QString const& _format); //exception de getListeTransactionsParCompte

        /**
            @fn  list<Transaction*> TransactionManager::getListeTransactionsParCompte(int const& _id_compte)
            @brief Méthode qui permet d'obtenir une liste des transactions correspondantes à un même compte.
            @param _id_compte : int const&, représente le compte dont on souhaite obtenir les transactions
            @exception SRCH_EXC_T aucune transaction ne porte sur le compte demandé
            @return une liste de pointeur sur les transactions
        */
        list<Transaction*> getListeTransactionsParCompte(int const& _id_compte);
        /**
            @fn Transaction* TransactionManager::getTransactionParReference(string const& _ref)
            @brief Méthode qui permet de trouver une transaction grâce à sa référence.
            @param _ref : int const&, représente la référence que l'on cherche
            @exception SRCH_EXC_T aucune transaction ne correspond
            @return une référence sur la transaction
        */
        Transaction* getTransactionParReference(string const& _ref);
        /**
            @fn bool TransactionManager::emptyTransactionsParCompte(int const& _id_compte) const noexcept
            @brief Méthode qui permet de verifier si un compte n'a plus de transaction
            @param _id_compte : string const, représente le compte dont on souhaite obtenir les transactions
            @return true si le compte n'a plus de transaction, false sinon
        */
        bool emptyTransactionsParCompte(int const& _id_compte) const noexcept;
        /**
            @fn list<Transaction*> TransactionManager::getListeTransactionsParValide(int const& _id_compte, bool const& _valide)
            @brief Méthode qui permet d'obtenir une liste des transactions valide ou non correspondantes à un même compte?
            @param _id_compte : string const, représente le compte dont on souhaite obtenir les transactions
            @param _valide : bool const, la validité des transactions à afficher
            @exception SRCH_EXC_T aucune transaction de cette validité ne porte sur le compte demandé
            @return une liste de pointeur sur les transactions
        */
        list<Transaction*> getListeTransactionsParValide(int const& _id_compte, bool const& _valide);
        /**
            @fn void ajouterOperation(list<Operation*>* _liste,CompteHierarchie* const _compte,double const& _debit, double const& _credit)
            @brief Méthode qui permet d'ajouter une nouvelle opération à une liste d'opération
            @param _liste : list<Operation*>*, pointeur sur la liste d'opération à compléter
            @param _compte : CompteHiearchie*, pointeur sur le compte subissant l'opération
            @param _debit : double, correspond au montant à débiter
            @param _credit : double, correspondant au montant à créditer
            @exception NULL_EXC_T exception d'opération : passage d'un compte nul
            @exception RULE_EXC_T exception d'opération : crédit et débit sont tous les deux nuls
            @exception RULE_EXC_T passage d'un compte non reel
        */
        void ajouterOperation(list<Operation*>* _liste,CompteHierarchie* const _compte,double const& _debit, double const& _credit);
        /**
            @fn void TransactionManager::ajouterTransaction(time_t const& _date, string const& _ref, double const& _montant, list<Operation*> const& _listOperations)
            @brief Méthode qui permet d'ajouter une nouvelle transaction.
            @param _date : time_t, la date de la nouvelle transaction
            @param _ref : string, la référence de la nouvelle transaction
            @param _memo : string, le mémo de la nouvelle transaction
            @param _listOperations : list<Operation*>, ensemble des opérations formant la nouvelle transaction
            @exception RULE_EXC_T non-unicité de la référence _ref
            @exception RULE_EXC_T non-équilibre des opérations
            @exception RULE_EXC_T tentative d'ajout d'une transaction antérieure au dernier rapprochement
            @exception IDNF_EXC_H l'identifiant du compte lié à une opération ne correspond à aucun compte réel
            @exception MEMO_EXC_T exception d'allocation mémoire
        */
        void ajouterTransaction(time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _listOperations);
        /**
            @fn void TransactionManager::editerTransaction(string const& _ancienne_ref,time_t const& _date, string const& _ref, double const& _montant, list<Operation*> const& _listOperations)
            @brief Méthode qui permet d'editer une transaction existante.
            @param _ancienne_ref : string const, la référence de la transaction à modifier
            @param _date : time_t, la nouvelle date de la transaction
            @param _ref : string, la nouvelle référence de la transaction
            @param _memo : string, le nouveau mémo de la transaction
            @param _listOperations : list<Operation*>, le nouvel ensemble des opérations formant la transaction
            @exception RULE_EXC_T non-équilibre des opérations
            @exception RULE_EXC_T non-unicité de la référence _ref
            @exception RULE_EXC_T tentative de modification sur une référence rapprochée
            @exception MEMO_EXC_T exception d'allocation mémoire
            @exception SRCH_EXC_T référence _ancienne_ref inconnue
        */
        void editerTransaction(string const& _ancienne_ref, time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _listOperations);
        /**
            @fn void TransactionManager::supprimerTransaction(string const& _ref)
            @brief Méthode qui permet de supprimer une transaction.
            @param _ref : string const, la référence de la transaction à supprimer
            @exception RULE_EXC_T tentative de suppression sur une référence rapprochée
            @exception SRCH_EXC_T référence _ref inconnue
        */
        void supprimerTransaction(string const& _ref);
        /**
            @fn void TransactionManager::charger(string const& _path)
            @brief Méthode qui permet de charger un fichier
            @param _path : string const, le chemin du fichier de sauvegarde
            @exception RULE_EXC_T exception d'opération : le débit et le crédit sont tous les deux nuls
            @exception RULE_EXC_T exception d'opération : non-équilibre des opérations
            @exception NULL_EXC_T exception d'opération : passage d'un compte nul
            @exception MEMO_EXC_T exception d'allocation mémoire
        */
        void charger(string const& _path);
        /**
            @fn void TransactionManager::sauver(QXmlStreamWriter* const _xml)
            @brief Méthode qui permet de sauvegarder un fichier
            @param _xml : QXmlStreamWriter* const, le flux de sauvegarde xml
        */
        void sauver(QXmlStreamWriter* const _xml);

    private:
        //methodes=========================
        /**
            @fn TransactionManager::TransactionManager()
            @brief Constructeur, en tant que singleton ce dernier est privé
        */
        TransactionManager();
        /**
            @fn TransactionManager::~TransactionManager()
            @brief Destructeur
        */
        ~TransactionManager();

        //attributs========================
        /**
            @var TransactionManager TransactionManager::instance
            @brief l'instance du manager
        */
        static TransactionManager instance;
        /**
            @var list<Transaction*> TransactionManager::transactions
            @brief ensemble des transactions existantes
        */
        static list<Transaction*> transactions;
};

#endif // TRANSACTIONMANAGER_H_INCLUDED
