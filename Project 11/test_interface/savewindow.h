#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H

/**
    @file savewindow.h
    @brief savewindow permet de gérer la fenêtre graphique utilisée pour sauvegarder la session actuelle dans un fichier.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include <QDialog>
#include <QFileDialog>
#include <QAbstractButton>
#include <QMessageBox>

/**
    @class Ui::Sauvegarde "savewindow.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesigner pour sauvegarder la session actuelle dans un fichier.
*/

namespace Ui {
class Sauvegarde;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class savewindow "savewindow.h"
    @brief savewindow permet de gérer la fenêtre graphique utilisée pour sauvegarder la session actuelle dans un fichier.
*/
class savewindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  savewindow::savewindow(MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de sauvegarder la session actuelle dans un fichier.
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit savewindow(MainWindow *parent);

    /**
     * @fn savewindow()::~savewindow()
     * @brief Destructeur de la fenêtre graphique permettant de sauvegarder la session actuelle dans un fichier.
    */
    ~savewindow();

signals:
    /**
     * @fn savewindow::sauvegarderFichier(QString)
     * @brief Ce signal est émis lorsque l'utilisateur clique sur le bouton "Parcourir" et que le chemin du fichier où sauvegarder la session actuelle est renseigné.  Il est capté par mainwindow et permet de sauvegarder la session actuelle dans le fichier.
     */
    void sauvegarderFichier(QString);

private slots:
    /**
     * @fn void savewindow::sauver()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "OK". Il permet de construire le chemin  du fichier renseigné dans la QFilDialog, afin de sauvegarder la session actuelle dans ce dernier.
     */
    void sauver();

    /**
     * @fn void savewindow::fermer()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton le bouton "Annuler". Il permet de fermer la QFileDialog.
     */
    void fermer();
    /**
     * @fn void savewindow::ouvrirFileDialog()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "Parcourir".  Il permet d'ouvrir un QFileDialog afin que l'utilisateur puisse choisir le dossier ou il souhaite enregistrer son fichier.
    */
    void ouvrirFileDialog();

private:
    /**
     * @var Ui::Sauvegarde* savewindow::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesginer pour sauvegarder la session actuelle dans un fichier.
     */
    Ui::Sauvegarde *design;
};


#endif // SAVEWINDOW_H
