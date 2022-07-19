/**
    @file modifiertransaction.cpp
    @brief définition des fonctions membres de la classe modifiertransaction.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "modifiertransaction.h"
#include "ui_modifiertransaction.h"
#include "mainwindow.h"

modifiertransaction::modifiertransaction(QString const _reference, QStringList const _comptes, std::list<int> const _liste_id, MainWindow *parent) :
    QDialog(parent),
    design(new Ui::modifiertransaction),
    comptes(_comptes),
    liste_id(_liste_id),
    reference(_reference)
{
    design->setupUi(this);
    devise =  parent->getDevise();

    Transaction* _tr;
    try
    {
        _tr = tm.getTransactionParReference(reference.toStdString());
    }
    catch(Exception except)
    {
        return;
    }

    connect(design->ajouterOperationPushButton,SIGNAL(clicked()),this,SLOT(ajouterOperation()));
    connect(design->buttonsDialog,SIGNAL(accepted()),this,SLOT(modifierTransaction()));
    connect(design->buttonsDialog,SIGNAL(rejected()),this,SLOT(reject()));

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

void modifiertransaction::modifierTransaction()
{
    if(design->memoLineEdit->text().isEmpty() || design->referenceLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"Information","Veuillez remplir tous les champs");
        return;
    }

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
        tm.editerTransaction(reference.toStdString(),date_t,ref.toStdString(),memo.toStdString(),operations);
    } catch (Exception e) {
        QMessageBox::warning(this,"Erreur",QString::fromStdString(e.getMessage()));
        return;
    }

    emit modifiant();
    accept();
}

void modifiertransaction::ajouterOperation()
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

void modifiertransaction::suppressionDernier()
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

modifiertransaction::~modifiertransaction()
{
    delete design;
}
