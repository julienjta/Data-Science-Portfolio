/**
    @file rapprochement.cpp
    @brief définition des fonctions membres de la classe rapprochement.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "rapprochement.h"
#include "ui_rapprochement.h"
#include "mainwindow.h"

#include <iostream>

rapprochement::rapprochement(QStringList const _comptes, std::list<int> const _liste_id, MainWindow *parent) :
    QDialog(parent),
    design(new Ui::rapprochement),
    comptes(_comptes),
    liste_id(_liste_id)
{
    design->setupUi(this);
    this->move(600,120);
    devise = parent->getDevise();

    design->listeCompte->addItems(_comptes);

    connect(design->ajouterOperationPushButton,SIGNAL(clicked()),this,SLOT(ajouterOperation()));
    connect(design->ModifierPushButton,SIGNAL(clicked()),this,SLOT(modifierTransaction()));
    connect(design->ValiderButton, SIGNAL(clicked()),this, SLOT(validerChoixCompte()));
    connect(design->ChangementPushButton, SIGNAL(clicked()),this, SLOT(changementCompte()));
    connect(design->QuitterButton1, SIGNAL(clicked()),this, SLOT(close()));
    connect(design->ValiderPushButton,SIGNAL(clicked()),this,SLOT(validerCompte()));
    connect(design->TerminerPushButton,SIGNAL(clicked()),this,SLOT(close()));

    std::list<int>::const_iterator it_id = liste_id.begin();
    int index = 0;
    for(;
       it_id != liste_id.end();
       it_id++
      )
    {

        design->listeCompte->setItemData(index,QVariant(*it_id));
        index++;
    }
    //mise à jour des monnaies
    design->labelSoldeActuelValeur->setText(devise);
    design->labelSoldeRapprochementValeur->setText(devise);

    choixCompte();
}


void rapprochement::choixCompte(){
    this->setFixedSize(600,150);
    //on laisse que le choix visible
    design->ValiderButton->show();
    design->QuitterButton1->show();
    design->listeCompte->setEnabled(true);
    design->ChangementPushButton->hide();
    design->labelSoldeRapprochement->hide();
    design->labelSoldeRapprochementValeur->hide();
    design->labelSoldeActuel->hide();
    design->labelSoldeActuelValeur->hide();
    design->labelTransaction->hide();
    design->listeTransaction->hide();
    design->TerminerPushButton->hide();
    design->ValiderPushButton->hide();

    design->ModifierPushButton->hide();
    design->ValiderPushButton->hide();
    design->ajouterOperationPushButton->hide();
    design->dateDateEdit->hide();
    design->dateLabel->hide();
    design->heureLabel->hide();
    design->heureTimeEdit->hide();
    design->labelTitreCompte->hide();
    design->labelTitreCredit->hide();
    design->labelTitreDebit->hide();
    design->labelTransaction->hide();
    design->listeTransaction->hide();
    design->referenceLabel->hide();
    design->referenceLineEdit->hide();
    design->memoLabel->hide();
    design->memoLineEdit->hide();
    design->operationLabel->hide();
    clear();
}

void rapprochement::changementCompte(){
    choixCompte();
}

void rapprochement::validerChoixCompte(){
    //on montre les élements cachés précedemment
    design->ChangementPushButton->show();
    design->labelSoldeRapprochement->show();
    design->labelSoldeRapprochementValeur->show();
    design->labelSoldeActuel->show();
    design->labelSoldeActuelValeur->show();
    design->labelTransaction->show();
    design->listeTransaction->show();
    design->TerminerPushButton->show();
    design->ValiderPushButton->show();

    //on cache les deux boutons et la liste
    design->ValiderButton->hide();
    design->QuitterButton1->hide();
    design->listeCompte->setEnabled(false);
    this->setFixedSize(600,660);
    modifierListeTransactions();
}




void rapprochement::modifierListeTransactions()
{
    int const _id = design->listeCompte->currentData().toInt();

    CompteHierarchie* compte;
    try
    {
        compte = cm.getCompte(_id);
    }
    catch(Exception except)
    {
        QMessageBox::warning(this,"Erreur","Selection d'un compte inexistant : "+QString::fromStdString(except.getMessage()));
        return;
    }
    if(compte->getType() != REEL)
    {
        QMessageBox::warning(this,"Erreur","Selection d'un dossier au lieu d'un compte (id = "+QString::number(_id)+")");
        return;
    }

    std::list<Memento*>::const_reverse_iterator it_memento = compte->getMementos().rbegin();
    double solde_actu = (*it_memento)->getSolde();
    design->labelSoldeActuelValeur->setText(QString::number(solde_actu,'f',2)+" "+devise);
    it_memento++;
    double solde_rapprochement = (*it_memento)->getSolde();
    design->labelSoldeRapprochementValeur->setText(QString::number(solde_rapprochement,'f',2)+" "+devise);

    std::list<Transaction*> transactions;
    try
    {
        transactions = tm.getListeTransactionsParValide(_id,false); //seulement les transactions sont rapprochées
    } catch (Exception except)
    {
        if(except.getCode() != ExceptionTransaction::CodeExcepTransaction::SRCH_EXC_T)
            QMessageBox::warning(this,"Erreur",QString::fromStdString(except.getMessage()));
    }
    if(transactions.empty())
    {
        QMessageBox::information(this,"Information","Aucune transaction associée à ce compte ne peut être modifiée, mais vous pouvez valider le rapprochement");
        design->ModifierPushButton->hide();
        design->ajouterOperationPushButton->hide();
        design->dateDateEdit->hide();
        design->dateLabel->hide();
        design->heureLabel->hide();
        design->heureTimeEdit->hide();
        design->labelTitreCompte->hide();
        design->labelTitreCredit->hide();
        design->labelTitreDebit->hide();
        design->labelTransaction->hide();
        design->listeTransaction->hide();
        design->referenceLabel->hide();
        design->referenceLineEdit->hide();
        design->memoLabel->hide();
        design->memoLineEdit->hide();
        design->operationLabel->hide();
        clear();
        return;
    }
    else if(design->ModifierPushButton->isHidden())
    {
        design->ModifierPushButton->show();
        design->ValiderPushButton->show();
        design->ajouterOperationPushButton->show();
        design->dateDateEdit->show();
        design->dateLabel->show();
        design->heureLabel->show();
        design->heureTimeEdit->show();
        design->labelTitreCompte->show();
        design->labelTitreCredit->show();
        design->labelTitreDebit->show();
        design->labelTransaction->show();
        design->listeTransaction->show();
        design->referenceLabel->show();
        design->referenceLineEdit->show();
        design->memoLabel->show();
        design->memoLineEdit->show();
        design->operationLabel->show();
    }

    if(design->listeTransaction->maxCount()>0)
    {
        disconnect(design->listeTransaction,SIGNAL(currentIndexChanged(int)),this,SLOT(modifierListeOperations()));
        design->listeTransaction->clear();
    }
    connect(design->listeTransaction,SIGNAL(currentIndexChanged(int)),this,SLOT(modifierListeOperations()));

    std::list<Transaction*>::const_iterator it_tr = transactions.begin();
    for(;
       it_tr != transactions.end();
       it_tr++
      )
    {
        design->listeTransaction->addItem(QString::fromStdString((*it_tr)->getReference()));
    }
    design->listeTransaction->setCurrentIndex(0); //emet currentIndexChanged -> active modifierListeOperations
}

void rapprochement::modifierListeOperations()
{
    Transaction* _tr;
    try
    {
        _tr = tm.getTransactionParReference(design->listeTransaction->currentText().toStdString());
    }
    catch(Exception except)
    {
        return;
    }



    clear();

    //PARTIE TRANSACTION

    design->referenceLineEdit->setText(QString::fromStdString(_tr->getReference()));
    design->memoLineEdit->setText(QString::fromStdString(_tr->getMemo()));
    time_t date_t = _tr->getDate();
    struct tm date_tm = *localtime(&date_t);
    design->dateDateEdit->setDate(QDate(date_tm.tm_year+1900,date_tm.tm_mon+1,date_tm.tm_mday));
    design->heureTimeEdit->setTime(QTime(date_tm.tm_hour,date_tm.tm_min));

    //PARTIE OPERATIONS

    std::list<Operation*> operations = _tr->getListeOperations();
    std::list<Operation*>::const_iterator it_op = operations.begin();

    for(;
            it_op != operations.end();
            it_op++
        )
    {
        if(selecteurs.size() >= 6)
        {
            design->ajouterOperationPushButton->setEnabled(false);
            return;
        }

        selecteurs.push_back(new QComboBox(this));
            selecteurs.last()->addItems(comptes);
            std::list<int>::const_iterator it_id = liste_id.begin();
            int index = 0;
            for(;
               it_id != liste_id.end();
               it_id++
              )
            {
                if(*it_id == (*it_op)->getIdCompte())
                    selecteurs.last()->setCurrentIndex(index);
                selecteurs.last()->setItemData(index,QVariant(*it_id));
                index++;
            }
            design->grilleOperationLayout->addWidget(selecteurs.last(),selecteurs.size(),0,1,1,Qt::AlignHCenter | Qt::AlignCenter);

        credits.push_back(new QDoubleSpinBox(this));
            credits.last()->setDecimals(2);
            credits.last()->setSingleStep(0.01);
            credits.last()->setSuffix(devise);
            credits.last()->setMinimum(0.00);
            credits.last()->setMaximum(10000.00);
            credits.last()->setValue((*it_op)->getCredit());
            design->grilleOperationLayout->addWidget(credits.last(),credits.size(),2,1,1,Qt::AlignHCenter | Qt::AlignCenter);

        debits.push_back(new QDoubleSpinBox(this));
            debits.last()->setDecimals(2);
            debits.last()->setSingleStep(0.01);
            debits.last()->setSuffix(devise);
            debits.last()->setMinimum(0.00);
            debits.last()->setMaximum(10000.00);
            debits.last()->setValue((*it_op)->getDebit());
            design->grilleOperationLayout->addWidget(debits.last(),debits.size(),1,1,1,Qt::AlignHCenter | Qt::AlignCenter);

        if(supprimers.size()>3)
            supprimers.last()->setEnabled(false);
        supprimers.push_back(new QPushButton("Supprimer",this));
            connect(supprimers.last(),SIGNAL(clicked()),this,SLOT(suppressionDernier()));
            design->grilleOperationLayout->addWidget(supprimers.last(),supprimers.size(),3,1,1,Qt::AlignHCenter | Qt::AlignCenter);
        if(supprimers.size()<3)
            supprimers.last()->setEnabled(false);
    }
}

void rapprochement::modifierTransaction()
{
    if(design->memoLineEdit->text().isEmpty() || design->referenceLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"Information","Veuillez remplir tous les champs");
        return;
    }

    QString a_ref = design->listeTransaction->currentText();
    QString ref = design->referenceLineEdit->text();
    QString memo = design->memoLineEdit->text();
    QDateTime date = design->dateDateEdit->dateTime();
    QDateTime heure = design->heureTimeEdit->dateTime();

    list<Operation*> operations;

    try
    {
        QList<QComboBox*>::iterator selecteur = selecteurs.begin();
        QList<QDoubleSpinBox*>::iterator credit = credits.begin();
        QList<QDoubleSpinBox*>::iterator debit = debits.begin();
        for(;
            selecteur != selecteurs.end() && credit != credits.end() && debit != debits.end();
            selecteur++, credit++, debit++
        )
        {
            int const id = (*selecteur)->currentData().toInt();
            double cr = (*credit)->value();
            double db = (*debit)->value();

            CompteHierarchie* c = cm.getCompte(id);
            tm.ajouterOperation(&operations,c,db,cr);
        }
    }
    catch(Exception except)
    {
        QMessageBox::warning(this,"Erreur",QString::fromStdString(except.getMessage()));
        return;
    }

    //on construit un objet DateTime contenant la bonne heure et la bonne date puis on le convertit
    time_t const date_t = time_t(QDateTime(date.date(),heure.time()).toTime_t());

    try
    {
        tm.editerTransaction(a_ref.toStdString(),date_t,ref.toStdString(),memo.toStdString(),operations);
    } catch (Exception e) {
        QMessageBox::warning(this,"Erreur",QString::fromStdString(e.getMessage()));
        return;
    }

    design->listeTransaction->setEditable(true);
    design->listeTransaction->setItemText(design->listeTransaction->currentIndex(),ref);
    design->listeTransaction->setEditable(false);
    emit modifiant();
    QMessageBox::warning(this,"Alerte",QString::fromStdString("Modification effectuée"));
}

void rapprochement::validerCompte()
{//on vérifie si l'utilisateur appuie sur le bouton non ou sur le bouton oui
    if(QMessageBox::StandardButton::No == QMessageBox::question(this,"Validation requise","Vous êtes sur le point de valider toutes les transactions d'un compte. Cela signifie que vous ne pourrez plus les modifier ou les supprimers. Êtes-vous sûr.e de vous ?"))
        return;
    int const _id = design->listeCompte->currentData().toInt();

    try{
        cm.rapprocherCompte(_id);
        emit modifiant();
    } catch (Exception e) {
        QMessageBox::warning(this,"Erreur",QString::fromStdString(e.getMessage()));
        return;
    }
    choixCompte();
}

void rapprochement::ajouterOperation()
{
    if(selecteurs.size() >= 6)
    {
        design->ajouterOperationPushButton->setEnabled(false);
        return;
    }

    selecteurs.push_back(new QComboBox(this));
        selecteurs.last()->addItems(comptes);
        std::list<int>::const_iterator it_id = liste_id.begin();
        int index = 0;
        for(;
           it_id != liste_id.end();
           it_id++
          )
        {
            selecteurs.last()->setItemData(index,QVariant(*it_id));
            index++;
        }
        design->grilleOperationLayout->addWidget(selecteurs.last(),selecteurs.size(),0,1,1,Qt::AlignHCenter | Qt::AlignCenter);

    credits.push_back(new QDoubleSpinBox(this));
        credits.last()->setDecimals(2);
        credits.last()->setSingleStep(0.01);
        credits.last()->setSuffix(devise);
        credits.last()->setMinimum(0.00);
        credits.last()->setMaximum(10000.00);
        design->grilleOperationLayout->addWidget(credits.last(),credits.size(),2,1,1,Qt::AlignHCenter | Qt::AlignCenter);

    debits.push_back(new QDoubleSpinBox(this));
        debits.last()->setDecimals(2);
        debits.last()->setSingleStep(0.01);
        debits.last()->setSuffix(devise);
        debits.last()->setMinimum(0.00);
        debits.last()->setMaximum(10000.00);
        design->grilleOperationLayout->addWidget(debits.last(),debits.size(),1,1,1,Qt::AlignHCenter | Qt::AlignCenter);

    supprimers.last()->setEnabled(false);
    supprimers.push_back(new QPushButton("Supprimer",this));
        connect(supprimers.last(),SIGNAL(clicked()),this,SLOT(suppressionDernier()));
        design->grilleOperationLayout->addWidget(supprimers.last(),supprimers.size(),3,1,1,Qt::AlignHCenter | Qt::AlignCenter);
}

void rapprochement::suppressionDernier()
{
    if(supprimers.size()>2)
    {
        design->ajouterOperationPushButton->setEnabled(true);
        delete supprimers.last();
        supprimers.pop_back();
        delete credits.last();
        credits.pop_back();
        delete debits.last();
        debits.pop_back();
        delete selecteurs.last();
        selecteurs.pop_back();
    }

    if(supprimers.size()>2)
    {
        supprimers.last()->setEnabled(true);
    }
}

void rapprochement::clear()
{
    while(!supprimers.empty())
    {
        delete supprimers.last();
        supprimers.pop_back();
        delete credits.last();
        credits.pop_back();
        delete debits.last();
        debits.pop_back();
        delete selecteurs.last();
        selecteurs.pop_back();
    }
}

rapprochement::~rapprochement()
{
    delete design;
}
