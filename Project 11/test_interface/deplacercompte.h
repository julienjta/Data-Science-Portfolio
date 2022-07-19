#ifndef DEPLACERCOMPTE_H
#define DEPLACERCOMPTE_H
/**
    @file deplacercompte.h
    @brief deplacercompte permet de gérer la fenêtre graphique utilisée pour déplacer un compte (en plus du drag & drop).
    @author Ophélie Delattre
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include <QDialog>
#include "../Compte/header/CompteManager.h"
/**
    @class Ui::deplacercompte "deplacercompte.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour déplacer un compte.
*/
namespace Ui {
class deplacercompte;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class deplacercompte "deplacercompte.h"
    @brief deplacercompte permet de gérer la fenêtre graphique utilisée pour déplacer un compte.
*/
class deplacercompte : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  deplacercompte:deplacercompte(std::list<int> const _liste_id,MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de déplacer un compte.
     * @param _liste_id : std::list<int> const, liste des ids des comptes de la hierarchie
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit deplacercompte(std::list<int> const _liste_id,MainWindow *parent);

    /**
     * @fn deplacercompte::~deplacercompte()
     * @brief Destructeur de la fenêtre graphique permettant de déplacer un compte.
    */
    ~deplacercompte();
signals:
    /**
     * @fn void deplacement::deplacement()
     * @brief deplacement est un signal émit lorsque le déplacement de compte a été effectué. Il sera capté par la classe MainWindow afin de mettre à jour le QTree (représentant la hiérarchie des comptes)
     */
    void deplacement();

private slots:
    /**
     * void deplacercompte::deplacementcompte()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "VALIDER".  Il permet de déplacer un compte dans la hiérarchie des comptes.
     */
    void deplacementcompte();

private:
    /**
     * @var std::list<int> const deplacercompte::liste_id
     * @brief liste_id représente la liste des ids des comptes de la hierarchie.
     */
    std::list<int> const liste_id;

    /**
     * @var Ui::deplacercompte* deplacercompte::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour déplacer un compte.
     */
    Ui::deplacercompte *design;
};

#endif // DEPLACERCOMPTE_H
