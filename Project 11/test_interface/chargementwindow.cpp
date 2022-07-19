/**
    @file chargementwindow.cpp
    @brief définition des fonctions membres de la classe chargementwindow.
    @author Jérémy Godde
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "chargementwindow.h"
#include "ui_chargementwindow.h"
#include "mainwindow.h"

chargementwindow::chargementwindow(MainWindow *parent) :
    QDialog(parent),
    design(new Ui::fenetreChargement)
{
    design->setupUi(this);
    connect(design->cheminPushButton,SIGNAL(clicked()),this,SLOT(ouvrirFileDialog()));
    connect(design->chargerPushButton,SIGNAL(clicked()),this,SLOT(verifierChamps()));
    connect(design->passerPushButton,SIGNAL(clicked()),this,SLOT(passer()));
}

void chargementwindow::ouvrirFileDialog()
{
    QString chemin = QFileDialog::getOpenFileName(this,
      "Selectionnez votre sauvegarde",
      "../Backups/","business (*.business);;XML (*.xml);;Tous les fichiers (*.*)");
    design->cheminLineEdit->setText(chemin);
}

void chargementwindow::verifierChamps()
{
    QString chemin = design->cheminLineEdit->text();

    if(!chemin.isEmpty()) //chargement de fichier prioritaire sur nouvelle session
    {
        emit chargerFichier(chemin); // on emet le chemin du fichier a charge
        close();                     // on ferme la dialog
    }
}

void chargementwindow::passer()
{
    emit initialiser();
    close();
}

chargementwindow::~chargementwindow()
{
    delete design;
}
