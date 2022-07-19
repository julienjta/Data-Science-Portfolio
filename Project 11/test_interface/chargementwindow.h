#ifndef CHARGEMENTWINDOW_H
#define CHARGEMENTWINDOW_H
/**
    @file chargementwindow.h
    @brief chargementwindow permet de gérer la fenêtre graphique utilisée pour charger un fichier à l'ouverture de l'application.
    @author Jérémy Godde
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include <QDialog>
#include <QFileDialog>
#include <QAbstractButton>
#include <QMessageBox>

/**
    @class Ui::fenetreChargement "chargementwindow.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour charger un fichier à l'ouverture de l'application.
*/
namespace Ui {
class fenetreChargement;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class chargementwindow "chargementwindow.h"
    @brief chargementwindow permet de gérer la fenêtre graphique utilisée pour charger un fichier à l'ouverture de l'application.
*/
class chargementwindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  chargementwindow::chargementwindow(MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de charger un fichier à l'ouverture de l'application.
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit chargementwindow(MainWindow *parent);
    /**
     * @fn chargementwindow()::~chargementwindow()
     * @brief Destructeur de la fenêtre graphique permettant de charger un fichier à l'ouverture de l'application.
    */
    ~chargementwindow();

signals:
    /**
     * @fn void chargementwindow::initialiser()
     * @brief Ce signal est émis lorsque l'utilisateur clique sur le bouton "Passer". Il est capté par mainwindow permet d'initialiser l'application : le compte racine est crée, le QTree et le tableau des transactions sont affichés.
     */
    void initialiser();
    /**
     * @fn chargementwindow::chargerFichier(QString)
     * @brief Ce signal est émis lorsque l'utilisateur clique sur le bouton "Charger" et le chemin du fichier a charger est renseigné.  Il est capté par mainwindow et permet de charger le fichier dont le chemin est renseigné et d'initialiser la hiérarchie des comptes et les transactions avec.
     */
    void chargerFichier(QString);

private slots:
    /**
     * @fn void chargementwindow::ouvrirFileDialog()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "Repertoire".  Il permet d'ouvrir un QFileDialog afin que l'utilisateur puisse choisir le fichier qu'il souhaire chargé.
    */
    void ouvrirFileDialog();
    /**
     * @fn void chargementwindow::verifierChamps()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "Charger". Si l'utilisateur a renseigné le chemin du fichier un chargé il emet le signal chargerFichier(QString) afin d'initiliser l'application grâce au chargement du fichier dont le chemin est renseigné.
     */
    void verifierChamps();

    /**
     * @fn void chargementwindow::passer()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "Charger". Il emet le signal initialiser() afin d'initiliser l'application avec la création du compte racine.
     */
    void passer();

private:
    /**
     * @var  Ui::enetreChargement chargementwindow::design;
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour charger un fichier à l'ouverture de l'application.
    */
    Ui::fenetreChargement *design;
};

#endif // CHARGEMENTWINDOW_H
