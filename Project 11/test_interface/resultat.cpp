/**
    @file resultat.cpp
    @brief définition des fonctions membres de la classe resultat.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "resultat.h"
#include "ui_resultat.h"
#include "mainwindow.h"

Resultat::Resultat(std::list<int> const _liste_id,MainWindow *parent) :
    QDialog(parent),
    design(new Ui::Resultat)
{
    design->setupUi(this);

    QString devise = parent->getDevise();

    double resultat = 0.;
    std::list<int>::const_iterator it_id = _liste_id.begin();
    for (;
         it_id != _liste_id.end();
         it_id++
    )
    {
        try
        {
            CompteHierarchie* compte = cm.getCompte(*it_id);
            if(compte->getType() == REEL && (compte->getPoste() == RECETTE || compte->getPoste() == DEPENSE))
            {
                Memento* memento = compte->getDernierMemento();

                if(compte->getPoste() == DEPENSE)
                {
                    resultat -= memento->getSolde();
                }
                else
                {
                    resultat += memento->getSolde();
                }

            }
        }
        catch(Exception& except)
        {
            QMessageBox::warning(this,"Erreur",QString::fromStdString(except.getMessage()));
        }
    }

    if(resultat < 0.)
    {
        design->ExcedentDeficitLabel->setText("Déficit");
    }

    design->valeurLabel->setText(QString::number(resultat,'f',2)+" "+devise);
}

Resultat::~Resultat()
{
    delete design;
}
