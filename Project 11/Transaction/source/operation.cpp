/**
    @file operation.cpp
    @brief définition des fonctions membre de la classe Operation
    @author Jérémy Godde / Mathilde Rineau
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucune
*/

#include "../header/operation.h"
Operation::Operation(CompteHierarchie* const _compte,double _debit, double _credit)
{
    //Le pointeur sur compte doit exister
    if(_compte == nullptr)
    {
        throw ExceptionTransaction("[!]Tentative d'effectuer une opération sur un compte qui n'existe pas'",ExceptionTransaction::NULL_EXC_T);
    }

    if(_compte->getType() != REEL)
    {
        throw ExceptionTransaction("[!]Tentative d'effectuer une opération sur un compte virtuel",ExceptionTransaction::RULE_EXC_T);
    }

    //Correction de valeur sur débit et crédit
    if(!tool::double_equal(_debit, 0.) && !tool::double_equal(_credit, 0.))
    {
        if(_debit >= _credit)
        {
            _debit -= _credit;
            _credit = 0.;
        }
        else
        {

            _credit -= _debit;
            _debit = 0.;
        }
    }

    //Si le débit et le crédit sont nuls, génération d'exception
    if(tool::double_equal(_debit, 0.) && tool::double_equal(_credit, 0.))
    {
        throw ExceptionTransaction("[!]Operation sans impact veuillez saisir un crédit ou un débit différent de 0",ExceptionTransaction::RULE_EXC_T);
    }

    //Ici : seule une des deux variables crédit et débit est non nulle

    //Si cette variable a une valeur négative, on procède à  une inversion
    if(_credit < 0.)
    {
        _debit -= _credit;
        _credit = 0.;
    }
    else if(_debit < 0.)
    {
         _credit -= _debit;
        _debit = 0.;
    }

    //assignation des variables aux attributs
    debit = _debit;
    credit = _credit;
    compte = _compte;
}

Operation::~Operation()
{
    compte=nullptr;
    debit = 0;
    credit =0;
    //on ne détruit pas le compte
}


bool Operation::isCompte(int const& _id_compte) const noexcept
{
    return compte->getId() == _id_compte;

}

int Operation::getIdCompte() const noexcept
{
     return compte->getId();

}

double Operation::getCredit() const noexcept
{
    return credit;
}

double Operation::getDebit() const noexcept
{
    return debit;
}

bool Operation::operator<(Operation const& _operation) const noexcept
{
    if(this->credit > 0. && _operation.credit > 0.) //si les deux sont en credit
    {
        return (this->credit < _operation.credit);
    }
    else if(this->debit > 0. && _operation.debit > 0.) //si les deux sont en debit
    {
        return (this->debit > _operation.debit);
    }

    //sinon  on recherche le credit
    return (this->credit > 0.);
}

bool Operation::operator<=(Operation const& _operation) const noexcept
{
    if(this->credit > 0. && _operation.credit > 0.) //si les deux sont en credit
    {
        return (this->credit <= _operation.credit);
    }
    else if(this->debit > 0. && _operation.debit > 0.) //si les deux sont en debit
    {
        return (this->debit >= _operation.debit);
    }

    //sinon on recherche le credit
    return (this->credit > 0.);
}

bool Operation::operator>(Operation const& _operation) const noexcept
{
    if(this->credit > 0. && _operation.credit > 0.) //si les deux sont en credit
    {
        return (this->credit > _operation.credit);
    }
    else if(this->debit > 0. && _operation.debit > 0.) //si les deux sont en debit
    {
        return (this->debit < _operation.debit);
    }

    //sinon on recherche le debit
    return (this->debit > 0.);
}

bool Operation::operator>=(Operation const& _operation) const noexcept
{
    if(this->credit > 0. && _operation.credit > 0.) //si les deux sont en credit
    {
        return (this->credit >= _operation.credit);
    }
    else if(this->debit > 0. && _operation.debit > 0.) //si les deux sont en debit
    {
        return (this->debit <= _operation.debit);
    }

    //sinon on recherche le debit
    return (this->debit > 0.);
}

list<Operation*> operator<<(list<Operation*>& _listOperations, Operation* const _operation) noexcept
{
    _listOperations.push_back(_operation);
    _listOperations.sort();
    return _listOperations;
}
