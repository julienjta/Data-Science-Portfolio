/**
    @file ajoutertransactionwindows.cpp
    @brief définition des fonctions membres de la classe ajoutertransactionwindows
    @author Jérémy Godde
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "ajoutertransactionwindows.h"
#include "ui_ajoutertransactionwindows.h"
#include "mainwindow.h"

#include <iostream>

ajoutertransactionwindows::ajoutertransactionwindows(QStringList const _comptes, std::list<int> const _liste_id, MainWindow *parent) :
    QDialog(parent),
    cm(CompteManager::getInstance()),
    tm(TransactionManager::getInstance()),
    comptes(_comptes),
    liste_id(_liste_id),
    qdate (new QDateEdit(QDate::currentDate())),
    qtime (new QTimeEdit(QTime::currentTime())),
    design(new Ui::fenetreAjouterTransaction)
{
    design->setupUi(this);

    devise = parent->getDevise();

    //date
    QLabel* timeLabel = new QLabel(tr("Heure"));
    design->formulaireLayout->insertRow(0,timeLabel,qtime);

    qdate->setMinimumDate(QDate(01,01,1970));
    QLabel* dateLabel = new QLabel(tr("Date"));
    design->formulaireLayout->insertRow(0,dateLabel,qdate);



    int i = 0;
    for(;i<2;i++)
    {
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
            design->grilleOperationLayout->addWidget(selecteurs.last(),i+1,0,1,1,Qt::AlignHCenter | Qt::AlignCenter);
                                                                    // i+1 -> (i+1)eme ligne
                                                                    // 0 -> 1er colonne
                                                                    // 1 -> dimension horizontal
                                                                    // 1 -> dimension vertical

        credits.push_back(new QDoubleSpinBox(this));
            credits.last()->setDecimals(2);
            credits.last()->setSingleStep(0.01);
            credits.last()->setSuffix(devise);
            credits.last()->setMinimum(0.00);
            credits.last()->setMaximum(10000.00);
            design->grilleOperationLayout->addWidget(credits.last(),i+1,2,1,1,Qt::AlignHCenter | Qt::AlignCenter);

        debits.push_back(new QDoubleSpinBox(this));
            debits.last()->setDecimals(2);
            debits.last()->setSingleStep(0.01);
            debits.last()->setSuffix(devise);
            debits.last()->setMinimum(0.00);
            debits.last()->setMaximum(10000.00);
            design->grilleOperationLayout->addWidget(debits.last(),i+1,1,1,1,Qt::AlignHCenter | Qt::AlignCenter);

        supprimers.push_back(new QPushButton("Supprimer",this));
            //pour les 2 premiers seulement
            supprimers.last()->setEnabled(false);
            design->grilleOperationLayout->addWidget(supprimers.last(),i+1,3,1,1,Qt::AlignHCenter | Qt::AlignCenter);
    }

    connect(design->ajouterOperationPushButton,SIGNAL(clicked()),this,SLOT(ajouterOperation()));
    connect(design->boutonsDialog,SIGNAL(accepted()),this,SLOT(verifier()));
    connect(design->boutonsDialog,SIGNAL(rejected()),this,SLOT(reject()));
}

void ajoutertransactionwindows::ajouterOperation()
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

void ajoutertransactionwindows::verifier()
{
    /*
     * verifier que les champs minimaux sont remplis
     * formater les donnees (date, operations)
     * attention aux exceptions
     * si tout est ok:
     *  tm.ajouterTransaction(...);
     *  accept();
     */

    //verifier que les champs minimaux sont remplis : seul rfrence et mot explicatif peuvent tre vide
    if(design->memoLineEdit->text().isEmpty() || design->referenceLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"Information","Veuillez remplir tous les champs");
        return;
    }

    QString ref = design->referenceLineEdit->text();
    QString memo = design->memoLineEdit->text();
    QDateTime date = qdate->dateTime();
    QDateTime heure = qtime->dateTime();

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
        tm.ajouterTransaction(date_t,ref.toStdString(),memo.toStdString(),operations);
        emit signalDone();
        accept();
    } catch (Exception e) {
        QMessageBox::warning(this,"Erreur",QString::fromStdString(e.getMessage()));
        return;
    }
}

void ajoutertransactionwindows::suppressionDernier()
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

ajoutertransactionwindows::~ajoutertransactionwindows()
{
    delete design;
}
