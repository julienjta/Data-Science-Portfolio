/**
    @file transactionmanager.cpp
    @brief définition des fonctions de la classe TransactionManager
    @author Jérémy Godde / Mathilde Rineau
    @version v2
    @date 2 mai 2020
    @bug aucun dtect
    @warning NON COMPIL
    @note aucune
*/

#include "../../Compte/header/CompteManager.h"

TransactionManager TransactionManager::instance;
list<Transaction*> TransactionManager::transactions;

TransactionManager::TransactionManager()
{

}

TransactionManager::~TransactionManager()
{
    //On effectue une sauvegarde
    //sauver(path);

    //on parcours la liste et on supprime chaque transaction
    for(list<Transaction*>::iterator iterator_transaction = transactions.begin();
        !transactions.empty() && iterator_transaction != transactions.end();
        iterator_transaction++)
    {
        TransactionBuilder::detruireTransaction(*iterator_transaction);
    }
}

TransactionManager& TransactionManager::getInstance() noexcept
{
    return instance;
}

list<Transaction*> TransactionManager::getListeTransactions() const noexcept
{
    return transactions;
}

Transaction* TransactionManager::getTransaction(string const& _ref) noexcept
{
    //parcours de la liste
    for(list<Transaction*>::iterator iterator_transaction = transactions.begin();
        !transactions.empty() && iterator_transaction != transactions.end();
        iterator_transaction++)
    {
        //si la référence est trouvée on retourne la transaction
        if((*iterator_transaction)->getReference() == _ref)
        {
            return *iterator_transaction;
        }
    }

    //dans le cas infructeux on retourne nullptr
    return nullptr;

}

list<Transaction*> TransactionManager::getListeTransactionsParValide(int const& _id_compte, bool const& _valide)
{
    list<Transaction*> transactions_compte;
    bool existe = false;
    //parcours de la liste
    for(list<Transaction*>::iterator iterator_transaction = transactions.begin();
        !transactions.empty() && iterator_transaction != transactions.end();
        iterator_transaction++)
    {
        if((*iterator_transaction)->getValide() == _valide)
        {
            list<Operation*> listOperations = (*iterator_transaction)->getListeOperations();

            bool verification = false;

            for(list<Operation*>::iterator iterator_operation = listOperations.begin();
            !verification && !listOperations.empty() && iterator_operation != listOperations.end();
            iterator_operation++)
            {
                if( (verification = (*iterator_operation)->isCompte(_id_compte))) //il s'agit bien d'un = d'assignation
                {
                    existe = true;
                    transactions_compte.push_back(*iterator_transaction);
                }
            }
        }
    }

    if(!existe)
        throw ExceptionTransaction("[!]Aucune operation de cette validite ne porte sur ce compte ",ExceptionTransaction::SRCH_EXC_T);

    return transactions_compte;
}

list<Transaction*> TransactionManager::getListeTransactionsParCompte(int const& _id_compte)
{
    list<Transaction*> transactions_compte;
    bool existe = false;
    //parcours de la liste
    for(list<Transaction*>::iterator iterator_transaction = transactions.begin();
        !transactions.empty() && iterator_transaction != transactions.end();
        iterator_transaction++)
    {
        list<Operation*> listOperations = (*iterator_transaction)->getListeOperations();

        bool verification = false;

        for(list<Operation*>::iterator iterator_operation = listOperations.begin();
        !verification && !listOperations.empty() && iterator_operation != listOperations.end();
        iterator_operation++)
        {
            if( (verification = (*iterator_operation)->isCompte(_id_compte))) //il s'agit bien d'un = d'assignation
            {
                existe = true;
                transactions_compte.push_back(*iterator_transaction);
            }
        }
    }

    if(!existe)
        throw ExceptionTransaction("[!]Aucune operation n'a porte sur ce compte",ExceptionTransaction::SRCH_EXC_T);

    return transactions_compte;
}

Transaction* TransactionManager::getTransactionParReference(string const& _ref)
{
    Transaction* transaction = nullptr;
    for(list<Transaction*>::iterator iterator_transaction = transactions.begin();
        transaction == nullptr && !transactions.empty() && iterator_transaction != transactions.end();
        iterator_transaction++)
    {
        if((*iterator_transaction)->getReference() == _ref)
            transaction = *iterator_transaction;
    }

    if(transaction == nullptr)
        throw ExceptionTransaction("[!]Aucune transaction correspondant a cette reference",ExceptionTransaction::SRCH_EXC_T);

    return transaction;
}

bool TransactionManager::emptyTransactionsParCompte(int const& _id_compte) const noexcept
{
    list<Transaction*> transactions_compte;
    bool empty = true;
    //parcours de la liste
    for(list<Transaction*>::iterator iterator_transaction = transactions.begin();
        empty && !transactions.empty() && iterator_transaction != transactions.end();
        iterator_transaction++)
    {
        list<Operation*> listOperations = (*iterator_transaction)->getListeOperations();

        for(list<Operation*>::iterator iterator_operation = listOperations.begin();
        empty && !listOperations.empty() && iterator_operation != listOperations.end();
        iterator_operation++)
        {
            if( ((*iterator_operation)->isCompte(_id_compte))) //il s'agit bien d'un = d'assignation
            {
                empty = false;
            }
        }
    }

    return empty;
}

void TransactionManager::ajouterOperation(list<Operation*>* _liste,CompteHierarchie* const _compte,double const& _debit, double const& _credit)
{
    *_liste = *_liste << TransactionBuilder::creerOperation(_compte,_debit,_credit);
}

void TransactionManager::ajouterTransaction(time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _listOperations)
{
   if (difftime(time(nullptr),_date)<0){
         throw ExceptionTransaction("[!]Tentative de transaction dans le futur ",ExceptionTransaction::RULE_EXC_T);
    }
    //on vérifie que la transaction n'est pas antérieure au rapprochement de chaque compte impacté
    for(
        list<Operation*>::const_iterator iterator_operation = _listOperations.begin();
        iterator_operation != _listOperations.end();
        ++iterator_operation
        )
    {
        CompteHierarchie* compte = CompteManager::getInstance().getCompte((*iterator_operation)->getIdCompte()); //peut retourner une exception
        Memento* memento_rapprochement = *(++compte->getMementos().rbegin());
        if(difftime(_date, memento_rapprochement->getDate())<0)
            throw ExceptionTransaction("[!]Tentative de transaction anterieure au dernier rapprochement ou avant 1970",ExceptionTransaction::RULE_EXC_T);
    }

    //on vérifie que l'unicité est concervée
    if(getTransaction(_ref) != nullptr)
        throw ExceptionTransaction("[!]Non respect de l'unicite de la reference des transactions ",ExceptionTransaction::RULE_EXC_T);

    //on ajoute la nouvelle transaction
    transactions.push_back(TransactionBuilder::creerTransaction(_date,_ref,_memo,_listOperations));
    transactions.sort(compare);
}

void TransactionManager::editerTransaction(string const& _ancienne_ref, time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _listOperations)
{
    //si l'ancienne transaction n'existe pas ou a été rapprochée, on émet une exception
    Transaction* ancienne = getTransaction(_ancienne_ref);
    if(ancienne == nullptr)
        throw ExceptionTransaction("[!]La reference a editer ne correspond a aucune transaction",ExceptionTransaction::SRCH_EXC_T);

    if(ancienne->getValide())
        throw ExceptionTransaction("[!]La transaction que vous souhaitez modifier est rapprochee",ExceptionTransaction::RULE_EXC_T);

    //si la référence est changée, on vérifie que l'unicité est concervée
    if(_ancienne_ref != _ref)
    {
        if(getTransaction(_ref) != nullptr)
            throw ExceptionTransaction("[!]Non respect de l'unicite de la reference des transactions",ExceptionTransaction::RULE_EXC_T);
    }

    //on recalcule le solde des comptes, on supprime l'ancienne et on ajoute la nouvelle
    list<Operation*> liste_operation = ancienne->getListeOperations();
    for(
        list<Operation*>::iterator iterator_operation = liste_operation.begin();
        iterator_operation != liste_operation.end();
        ++iterator_operation
        )
    {
        if(!tool::double_equal((*iterator_operation)->getCredit(), 0.))
        {
            CompteManager::getInstance().debiterCompte((*iterator_operation)->getIdCompte(),(*iterator_operation)->getCredit());
        }
        else if(!tool::double_equal((*iterator_operation)->getDebit(), 0.))
        {
            CompteManager::getInstance().crediterCompte((*iterator_operation)->getIdCompte(),(*iterator_operation)->getDebit());
        }
    }
    transactions.remove(ancienne);
    try{
    ajouterTransaction(_date,_ref,_memo,_listOperations);
    } catch (ExceptionTransaction & e){
        transactions.push_back(ancienne);
        transactions.sort(compare);
        throw (ExceptionTransaction(e.getMessage(),ExceptionTransaction::CodeExcepTransaction::RULE_EXC_T));
    }

    transactions.sort(compare);
    TransactionBuilder::detruireTransaction(ancienne);

}

void TransactionManager::supprimerTransaction(string const& _ref)
{
    //recherche de la transaction à supprimer
    Transaction* transaction_supp = getTransaction(_ref);
    if(transaction_supp == nullptr)
        throw ExceptionTransaction("[!]La reference ne correspond a aucune transaction",ExceptionTransaction::SRCH_EXC_T);

    if(transaction_supp->getValide())
        throw ExceptionTransaction("[!]La transaction que vous souhaitez supprimer est rapprochee",ExceptionTransaction::RULE_EXC_T);

    //calcul du solde des comptes puis suppression de la liste puis destruction
    list<Operation*> liste_operation = transaction_supp->getListeOperations();
    for(
        list<Operation*>::iterator iterator_operation = liste_operation.begin();
        iterator_operation != liste_operation.end();
        ++iterator_operation
        )
    {
        if(!tool::double_equal((*iterator_operation)->getCredit(), 0.))
        {
            CompteManager::getInstance().debiterCompte((*iterator_operation)->getIdCompte(),(*iterator_operation)->getCredit());
        }
        else if(!tool::double_equal((*iterator_operation)->getDebit(), 0.))
        {
            CompteManager::getInstance().crediterCompte((*iterator_operation)->getIdCompte(),(*iterator_operation)->getDebit());
        }
    }
    transactions.remove(transaction_supp);
    TransactionBuilder::detruireTransaction(transaction_supp);
}

void TransactionManager::charger(string const& _path)
{
    transactions = TransactionBuilder::creerTransactionAvecFichier(_path);
}

void TransactionManager::sauver(QXmlStreamWriter* const _xml)
{
    //Si on a aucune transaction, ca ne sert a rien d'ecraser la sauvegarde
    if(transactions.empty())
        return;

    _xml->writeStartElement("TransactionManager");

    time_t temp_time_t;

    list<Transaction*>::const_iterator iterator_transactions = transactions.begin();
    for(
        ;
        iterator_transactions != transactions.end();
        iterator_transactions++
    )
    {
        _xml->writeStartElement("Transaction");

        temp_time_t = (*iterator_transactions)->getDate();
        _xml->writeAttribute(QString("date"), QString::number(temp_time_t));
        _xml->writeAttribute(QString("valide"), QString::number((*iterator_transactions)->getValide()));
        _xml->writeAttribute(QString("reference"), QString::fromStdString((*iterator_transactions)->getReference()));
        _xml->writeAttribute(QString("memo"), QString::fromStdString((*iterator_transactions)->getMemo()));

        list<Operation*> operations = (*iterator_transactions)->getListeOperations();
        list<Operation*>::const_iterator iterator_operations = operations.begin();
        for(
            ;
            iterator_operations != operations.end();
            iterator_operations++
        )
        {
            _xml->writeStartElement("Operation");
            _xml->writeAttribute(QString("id_compte"), QString::number((*iterator_operations)->getIdCompte()));
            _xml->writeAttribute(QString("credit"), QString::number((*iterator_operations)->getCredit()));
            _xml->writeAttribute(QString("debit"), QString::number((*iterator_operations)->getDebit()));
            _xml->writeEndElement();
        }

        _xml->writeEndElement();
    }
    _xml->writeEndElement();
}

void TransactionManager::affiche(QTableWidget* const _tableau, QString const& _devise, QString const& _format) noexcept
{
    _tableau->clearContents();
    _tableau->setRowCount(0);

    if(!transactions.empty())
    {
        int row = 0;

        QTableWidgetItem TWI_vide("\"");
        TWI_vide.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        QTableWidgetItem TWI_nul("-");
        TWI_nul.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        list<Transaction*>::const_reverse_iterator it_transaction = transactions.rbegin();
        for(;
            it_transaction != transactions.rend();
            it_transaction++
        )
        {
            _tableau->setRowCount(row+1);

            _tableau->setItem(row,0,new QTableWidgetItem(QString::fromLatin1((*it_transaction)->getStringDate(_format.toStdString()).c_str())));
            _tableau->setItem(row,1,new QTableWidgetItem(QString::fromStdString((*it_transaction)->getReference())));
            _tableau->setItem(row,2,new QTableWidgetItem(QString::fromStdString((*it_transaction)->getMemo())));

            list<Operation*> liste_operations = (*it_transaction)->getListeOperations();
            list<Operation*>::const_iterator it_operation = liste_operations.begin();

            bool found = false;
            for (;
                 it_operation != liste_operations.end();
                 it_operation++
            )
            {
                if(found)
                {
                    _tableau->setRowCount(row+1);
                    _tableau->setItem(row,0,new QTableWidgetItem(TWI_vide));
                }
                else found = true;

                int const id = (*it_operation)->getIdCompte();
                CompteHierarchie* c = CompteManager::getInstance().getCompte(id);

                _tableau->setItem(row,3,new QTableWidgetItem(QString::fromStdString(c->toString())));

                double const cr = (*it_operation)->getCredit();
                double const db = (*it_operation)->getDebit();

                if(cr > db) // l'un devant valoir zero on determine ainsi lequel a une valeur non nul
                {
                    QTableWidgetItem * TWI_cr = new QTableWidgetItem(QString::number(cr,'f',2)+" "+_devise);
                    TWI_cr->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

                    _tableau->setItem(row,5,TWI_cr);

                    _tableau->setItem(row,4,new QTableWidgetItem(TWI_nul));
                }
                else
                {
                    _tableau->setItem(row,5,new QTableWidgetItem(TWI_nul));

                    QTableWidgetItem * TWI_db = new QTableWidgetItem(QString::number(db,'f',2)+" "+_devise);
                    TWI_db->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

                    _tableau->setItem(row,4,TWI_db);
                }
                row++;
            }
        }
    }
}

void TransactionManager::affiche(QTableWidget* const _tableau,CompteHierarchie* _compte, QString const& _devise, QString const& _format)
{
    if(_compte->getType() != REEL)
        return;

    _tableau->clearContents();
    _tableau->setRowCount(0);

    int const id = _compte->getId();

    if(!emptyTransactionsParCompte(id))
    {
        list<Transaction*> const _transactions = getListeTransactionsParCompte(id);

        QTableWidgetItem TWI_vide("\"");
        TWI_vide.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        QTableWidgetItem TWI_nul("-");
        TWI_nul.setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        int row = 0;
        double solde = 0.;

        list<Transaction*>::const_reverse_iterator it_transaction = _transactions.rbegin();
        for(;
            it_transaction != _transactions.rend();
            it_transaction++
        )
        {
            _tableau->setRowCount(row+1);

            _tableau->setItem(row,0,new QTableWidgetItem(QString::fromLatin1((*it_transaction)->getStringDate(_format.toStdString()).c_str())));
            _tableau->setItem(row,1,new QTableWidgetItem(QString::fromStdString((*it_transaction)->getReference())));
            _tableau->setItem(row,2,new QTableWidgetItem(QString::fromStdString((*it_transaction)->getMemo())));

            list<Operation*> liste_operations = (*it_transaction)->getListeOperations();
            list<Operation*>::const_iterator it_operation = liste_operations.begin();

            int row_tr = row;
            bool found = false;
            for (;
                 it_operation != liste_operations.end();
                 it_operation++
            )
            {
                if((*it_operation)->getIdCompte() == id)
                {
                    if(found)
                    {
                        _tableau->setRowCount(row+1);
                        _tableau->setItem(row,0,new QTableWidgetItem(TWI_vide));
                        _tableau->setItem(row,5,new QTableWidgetItem(TWI_nul));
                    }
                    else found = true;

                    double const cr = (*it_operation)->getCredit();
                    double const db = (*it_operation)->getDebit();

                    if(cr > db) // l'un devant valoir zero on determine ainsi lequel a une valeur non nul
                    {
                        if(_compte->getPoste() == PASSIF || _compte->getPoste() == RECETTE)
                            solde += cr;
                        else
                            solde -= cr;

                        QTableWidgetItem * TWI_cr = new QTableWidgetItem(QString::number(cr,'f',2)+" "+_devise);
                        TWI_cr->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

                        _tableau->setItem(row,4,TWI_cr);

                        _tableau->setItem(row,3,new QTableWidgetItem(TWI_nul));
                    }
                    else
                    {
                        if(_compte->getPoste() == PASSIF || _compte->getPoste() == RECETTE)
                            solde -= db;
                        else
                            solde += db;

                        _tableau->setItem(row,4,new QTableWidgetItem(TWI_nul));

                        QTableWidgetItem * TWI_db = new QTableWidgetItem(QString::number(db,'f',2)+" "+_devise);
                        TWI_db->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);

                        _tableau->setItem(row,3,TWI_db);
                    }

                    row++;
                }

                QTableWidgetItem * TWI_solde = new QTableWidgetItem(QString::number(solde,'f',2)+" "+_devise);
                TWI_solde->setTextAlignment(Qt::AlignHCenter | Qt::AlignCenter);
                _tableau->setItem(row_tr,5,TWI_solde);
            }
        }
    }
}
