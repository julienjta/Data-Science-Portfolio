/**
    @file transaction.cpp
    @brief définition des fonctions membre de la classe transaction
    @author Mathilde Rineau / Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning NON COMPILÉ
    @note aucune
*/

#include "../../Compte/header/CompteManager.h"

time_t Transaction::getDate() const noexcept
{
    return date;
}

string Transaction::getStringDate(string const& format) const noexcept
{
    char c_date[30];
    string s_date;
    setlocale(LC_ALL, "french");
    struct tm* t_date = gmtime(&date);
    if (format == "dd/mm/yy") {
        strftime(c_date,30,"%d/%m/%y",t_date);
        s_date = string(c_date);
    } else if (format == "dd/mm/yyyy") {
        strftime(c_date,30,"%d/%m/%Y",t_date);
        s_date = string(c_date);
    } else {
        strftime(c_date,30,"%A %d %b %Y",t_date);
        s_date = string(c_date);
    }

    return s_date;
}

string Transaction::getReference() const noexcept
{
    return reference_transaction;
}

string Transaction::getMemo() const noexcept
{
    return memo;
}

bool Transaction::getValide() const noexcept
{
    return valide;
}

void Transaction::setValide(bool _valide) noexcept
{
    valide = _valide;
}

list<Operation*> const Transaction::getListeOperations() const noexcept
{
    return operations;
}

Transaction::Transaction(const time_t &_date, const string &_ref, const string &_memo, const bool &_valide, const list<Operation *> &_listOperations)
{
    date=_date;
    reference_transaction=_ref;
    memo=_memo;
    valide=_valide;
    operations=_listOperations;
}

Transaction::~Transaction()
{
    for(
        list<Operation*>::iterator iterator_operation = operations.begin();
        !operations.empty() && iterator_operation != operations.end();
        iterator_operation++
    )
    {
        delete *iterator_operation;
    }

}


bool compare(Transaction* const _transaction_1, Transaction* const _transaction_2) noexcept
{
    return _transaction_1->getDate() < _transaction_2->getDate();
}
