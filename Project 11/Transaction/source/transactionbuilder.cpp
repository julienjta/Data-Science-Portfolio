/**
    @file transactionbuilder.cpp
    @brief définition de des fonctions membres de la classe TransactionBuilder
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug nécessité d'avoir une définition de CompteManager pour compiler
    @warning COMPILE
    @note aucune
*/

#include "../../Compte/header/CompteManager.h"

TransactionBuilder::TransactionBuilder()
{

}

TransactionBuilder::~TransactionBuilder()
{

}

Transaction* TransactionBuilder::creerTransaction(time_t const& _date, string const& _ref, string const& _memo, list<Operation*> const& _liste_operations)
{
    /*===================================================================
     * Hypothèses :
     *   - L'unicité de _ref a été vérifié avant
     *   - On suppose que la vérification sur les opérations d'avoir soit
     *      le crédit, soit le débit de nul est faite avant
     * Informations :
     *   TransactionBuilder est friend sur Transaction et sur Operation
     *===================================================================*/

    //On vérifie que la liste d'opération n'est pas vide
    if(_liste_operations.empty())
        throw ExceptionTransaction("[!]Tentative de creation de transaction avec une liste vide d'operations ",ExceptionTransaction::RULE_EXC_T);

    // Nouvelle transaction
    Transaction* transaction = new Transaction();
    if(transaction == nullptr)
        throw ExceptionTransaction("[!]Probleme d'allocation memoire pour la Transaction",ExceptionTransaction::MEMO_EXC_T);


    // Vérification de l'égalité débit crédit des opérations
    double total_credit = 0.,
           total_debit = 0.;

    for(list<Operation*>::const_iterator iterator_operation = _liste_operations.begin();
        iterator_operation != _liste_operations.end();
        iterator_operation++)
    {
        total_credit += (*iterator_operation)->credit;
        total_debit += (*iterator_operation)->debit;
    }
    if(!tool::double_equal(total_credit, total_debit)){
        throw ExceptionTransaction("[!]Les totaux du debit et du credit sont differents dans la transaction",ExceptionTransaction::RULE_EXC_T);
    }

    // Assignation des attributs
    transaction->date = _date;
    transaction->reference_transaction = _ref;
    transaction->memo = _memo;
    transaction->operations = _liste_operations;

    // Lier les opérations à leur transaction
    for(
        list<Operation*>::iterator iterator_operation = transaction->operations.begin();
        iterator_operation != transaction->operations.end();
        iterator_operation++
    )
    {
        (*iterator_operation)->transaction = transaction;

        if((*iterator_operation)->getCredit()>0.)
            CompteManager::getInstance().crediterCompte((*iterator_operation)->getIdCompte(),(*iterator_operation)->getCredit());
        if((*iterator_operation)->getDebit()>0.)
            CompteManager::getInstance().debiterCompte((*iterator_operation)->getIdCompte(),(*iterator_operation)->getDebit());
    }

    return transaction;
}

list<Transaction*> TransactionBuilder::creerTransactionAvecFichier(string const& _path)
{
    // Ouverture du fichier
    QFile qfile(QString::fromStdString(_path));
    if (!qfile.open(QIODevice::ReadOnly))
    {
        ExceptionFichier("[!]Impossible d'ouvrir le fichier suivant en lecture : " + _path,
                                  ExceptionFichier::CodeExcepFichier::UFND_EXC_F);
    }

    QDomDocument xml;
    xml.setContent(&qfile);
    qfile.close();

    list<Transaction*> liste_transactions;
    // save > CompteManager
    QDomNode actual = xml.documentElement().firstChild();

    if(actual.nextSibling().isNull())
        return liste_transactions;

    CompteManager& cm = CompteManager::getInstance();

    // CompteManager > TransactionManager > Transaction
    actual = actual.nextSibling().firstChild();
    while(!actual.isNull())
    {
        QDomElement transaction = actual.toElement();

        Transaction* nouv_transaction = new Transaction();

        nouv_transaction->date = transaction.attribute(QString("date")).toLong();
        nouv_transaction->valide = transaction.attribute(QString("valide")).toInt();
        nouv_transaction->reference_transaction = transaction.attribute(QString("reference")).toStdString();
        nouv_transaction->memo = transaction.attribute(QString("memo")).toStdString();

        list<Operation*> liste_operations;
        QDomNode actual_operation = actual.firstChild();

        while(!actual_operation.isNull())
        {
            QDomElement operation = actual_operation.toElement();
            int id = operation.attribute(QString("id_compte")).toInt();
            CompteHierarchie* compte = cm.getCompte(id);
            double credit = operation.attribute(QString("credit")).toDouble();
            double debit = operation.attribute(QString("debit")).toDouble();

            Operation* nouv_operation = new Operation(compte,debit,credit);
            nouv_operation->transaction = nouv_transaction;
            liste_operations = liste_operations << nouv_operation;

            actual_operation = actual_operation.nextSibling();
        }

        nouv_transaction->operations = liste_operations;
        liste_transactions.push_back(nouv_transaction);

        actual = actual.nextSibling();
    }
    return liste_transactions;
}

void TransactionBuilder::detruireTransaction(Transaction* const _transaction) noexcept
{
    delete _transaction;
}

Operation* TransactionBuilder::creerOperation(CompteHierarchie* const _compte,double const& _debit, double const& _credit)
{
    return new Operation(_compte,_debit,_credit);
}
