#ifndef AJOUTERWINDOW_H
#define AJOUTERWINDOW_H

/**
    @file ajouterwindow.h
    @brief ajouterwindow permet de gérer la fenêtre graphique utilisée pour ajouter des comptes.
    @author Ophélie Delattre
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include <QDialog>
#include <QtWidgets>
#include <list>
#include "../Compte/header/CompteManager.h"

/**
    @class Ui::fenetreAjouterCompte "ajouterwindow.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour ajouter des comptes
*/
namespace Ui {
class fenetreAjouterCompte;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class ajouterwindow "ajouterwindow.h"
    @brief ajouterwindow permet de gérer la fenêtre graphique utilisée pour ajouter des comptes.
*/
class ajouterwindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  ajouterwindow::ajouterwindow(std::list<int> const _liste_id,QTreeWidgetItem * _compte_selectionne, MainWIndow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant d'ajouter des comptes.
     * @param _liste_id : std::list<int> liste des ids des comptes de la hierarchie
     * @param  _compte_selectionne: QTreeWidgetItem *, compte sélectionné dans le QTree
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit ajouterwindow(std::list<int> const _liste_id,QTreeWidgetItem * _compte_selectionne, MainWindow *parent);

    /**
     * @fn ajouterwindow::~ajouterwindow()
     * @brief Destructeur de la fenêtre graphique permettant d'ajouter des comptes.
    */
    ~ajouterwindow();

signals:
    /**
     * @fn void ajouterwindow::ajout()
     * @brief ajout est un signal qui est émis lorsqu'un compte a été ajouté. Il sera capté par la classe MainWindow afin de mettre à jour le QTree (représentant la hiérarchie des comptes) et le tableau de transactions.
     */
    void ajout();

private slots:
    /**
     * @fn void ajouterwindow::ajouterCompte()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "OK". Il permet de vérifier les informations saisies par l'utilisateur et d'ajouter un compte à la hiérarchie des comptes si ces dernières sont exactes.
     */
    void ajouterCompte();
    /**
     * @fn void ajouterwindow::capitauxpropre()
     * @brief Ce slot est appelé lorsque l'utilisateur modifie la valeur courante des listes déroulantes permettant de choisir le type et le poste du nouveau compte. Lorsque le type du nouveau compte est REEL (compte) et le poste Actif ou Passif, alors le formulaire permettant de saisir un compte de capitaux propre est affiché.
     */
    void capitauxpropre();
    /**
     * @fn void ajouterwindow::nvcapitauxpropre()
     * @brief Ce slot est appelé lorsque l'utilisateur modifie la valeur courante des listes déroulantes permettant de choisir le compte de capitaux propre. Lorsque le texte courant vaut "Nouveau", le formulaire permettant de créer un nouveau compte de capitaux propre est affiché.
     * @param text : const QString&, texte courant de la liste déroulante permettant de choisir le compte de capitaux propre
    */
    void nvcapitauxpropre(const QString &text);

private:
    /**
        @var CompteManager& ajouterwindow::cm
        @brief cm représente le CompteManager.
    */
    CompteManager& cm;

    /**
     * @var std::list<int> const ajouterwindow::liste_id
     * @brief liste_id représente la liste des ids des comptes de la hierarchie.
     */
    std::list<int> const liste_id;

    /**
     * @var QComboBox* ajouterwindow::selecteurs
     * @brief liste déroulante permettant de choisir le père du nouveau compte.
    */
    QComboBox * selecteurs;

    /**
     * @var  Ui::fenetreAjouterCompte* ajouterwindow::design;
     * @brief design représente la fenêtre graphique réalisée sur QTDesginer pour ajouter des compte
    */
    Ui::fenetreAjouterCompte *design;

};

#endif // AJOUTERWINDOW_H
