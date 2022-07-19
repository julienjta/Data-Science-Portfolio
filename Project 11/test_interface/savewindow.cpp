/**
    @file savewindow.cpp
    @brief définition des fonctions membres de la classe savewindow.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "savewindow.h"
#include "ui_savewindow.h"
#include "mainwindow.h"

savewindow::savewindow(MainWindow *parent) :
    QDialog(parent),
    design(new Ui::Sauvegarde)
{
    design->setupUi(this);
    connect(design->selectionFichierBouton,SIGNAL(clicked()),this,SLOT(ouvrirFileDialog()));//selection fichier ->parcourir
    connect(design->validationFichierBouton,SIGNAL(accepted()),this,SLOT(sauver())); //bouton OK -> lancer la sauvegarde()
    connect(design->validationFichierBouton,SIGNAL(rejected()),this,SLOT(fermer())); //bouton close -> fonction fermer()
}

savewindow::~savewindow()
{
    delete design;
}
void savewindow::fermer()//copie chargementwindow
{
    close();            //on ferme la dialog
}
void savewindow::ouvrirFileDialog()//copie chargementwindow
{
    QString chemin = QFileDialog::getExistingDirectory (this,
        "Selectionnez un dossier où sauvegarde","../Backups/");
    design->cheminLineEdit->setText(chemin);
}

void savewindow::sauver()//doit lancer la sauvegarde
{
    QString chemin = design->cheminLineEdit->text();
    QString fichier = design->fichierLineEdit->text();

    if(!chemin.isEmpty() && !fichier.isEmpty())
    {
        QString extension = design->extensionComboBox->currentText();
        if(*(extension.begin()) == '.')
        {
            fichier += extension;
        }
        if(*(chemin.rbegin()) != '/')
        {
            chemin += '/';
        }
        emit sauvegarderFichier(chemin+fichier); // on emet le chemin complet du fichier a charge
        close();                     // on ferme la dialog
    }
    else
        QMessageBox::information(this,"Information","Veuillez renseigner un chemin et un nom fichier pour enregistrer les donnees");
}
