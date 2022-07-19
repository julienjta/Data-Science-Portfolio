#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

/**
    @file operation.h
    @brief Objet représentant une opération comptable, utilisé par les comptes et les
        transactions
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucune
*/

#include "../../Compte/header/CompteReel.h"

/**
    @class Operation "operation.h"
    @brief Objet représentant une opération comptable
*/
class Operation{
    friend TransactionBuilder;
    friend list<Operation*> operator<<(list<Operation*>& _listOperations, Operation* const _operation) noexcept;

    public:
        /**
            @fn Operation::~Operation()
            @brief Destructeur
        */
        ~Operation();
        /**
            @fn bool Operation::isCompte(int const _id_compte) const noexcept
            @brief vérifie si l'opération appartient au compte correspondant.
            @param _id_compte : int const&, identifiant d'un compte
            @return true si le compte correspond, false sinon
        */
        bool isCompte(int const& _id_compte) const noexcept;
        /**
            @fn int Operation::getIdCompte() const noexcept
            @brief Méthode pour btenir l'id du compte de l'opération.
            @return l'id du compte de l'opération
        */
        int getIdCompte() const noexcept;
        /**
            @fn double Operation::getDebit() const noexcept
            @brief Méthode pour obtenir la valeur du débit de l'opération.
            @return la valeur du débit de l'opération
        */
        double getDebit() const noexcept;
        /**
            @fn double Operation::getCredit() const noexcept
            @brief Méthode pour obtenir la valeur du crédit de l'opération.
            @return la valeur du crédit de l'opération
        */
        double getCredit() const noexcept;
        /**
            @fn bool Operation::operator<(Operation const& _operation) const noexcept
            @brief définition de l'opérateur <, test sur crédit et débit.
        */
        bool operator<(Operation const& _operation) const noexcept;
        /**
            @fn bool Operation::operator<=(Operation const& _operation) const noexcept
            @brief définition de l'opérateur <=, test sur crédit et débit.
        */
        bool operator<=(Operation const& _operation) const noexcept;
        /**
            @fn bool Operation::operator>(Operation const& _operation) const noexcept
            @brief définition de l'opérateur >, test sur crédit et débit.
        */
        bool operator>(Operation const& _operation) const noexcept;
        /**
            @fn bool Operation::operator>=(Operation const& _operation) const noexcept
            @brief définition de l'opérateur >=, test sur crédit et débit.
        */
        bool operator>=(Operation const& _operation) const noexcept;
    private:
        //methodes=========================
        /**
            @fn Operation::Operation(CompteHierarchie* const _compte,double _debit, double _credit) explicit
            @brief Constructeur, si ni le débit, ni le crédit n'est nul, une soustraction du plus faible montant sur le plus élevé a lieu.
            @param _compte : CompteHierarchie*, compte sur lequel porte l'opération
            @param _debit : double, valeur du débit
            @param _credit : double, valeur du crédit
            @exception RULE_EXC_T le débit et le crédit sont tous les deux nuls
            @exception RULE_EXC_T passage d'un compte non reel
            @exception NULL_EXC_T passage d'un compte nul
        */
        explicit Operation(CompteHierarchie* const _compte,double _debit, double _credit);
        //attributs========================
        /**
            @var Transaction* Operation::transaction
            @brief la transaction dont l'opération fait partie
        */
        Transaction* transaction;
        /**
            @var CompteHierarchie* Operation::compte
            @brief le compte sur lequel l'opération porte
        */
        CompteHierarchie* compte;
        /**
            @var double Operation::debit
            @brief la valeur de débit
        */
        double debit;
        /**
            @var double Operation::crédit
            @brief la valeur de crédit
        */
        double credit;
};


#endif // OPERATION_H_INCLUDED
