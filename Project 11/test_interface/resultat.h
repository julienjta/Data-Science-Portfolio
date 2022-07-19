#ifndef RESULTAT_H
#define RESULTAT_H

/**
    @file resultat.h
    @brief resultat permet de gérer la fenêtre graphique utilisée pour génerer le resultat.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include <QDialog>
#include "../Compte/header/CompteManager.h"


/**
    @class Ui::Resultat "resultat.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesigner pour generer le resultat.
*/

namespace Ui {
class Resultat;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class Resultat "resultat.h"
    @brief Resultat permet de gérer la fenêtre graphique permettant de génerer le resultat.
*/
class Resultat : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  Resultat::Resultat(std::list<int> const _liste_id,MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de génerer le resultat.
     * @param _liste_id : std::list<int> const, liste des ids des comptes réels de la hierarchie.
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit Resultat(std::list<int> const _liste_id,MainWindow *parent);
    /**
     * @fn Resultat::~Resultat()
     * @brief Destructeur de la fenêtre resultat
    */
    ~Resultat();

private:
    /**
     * @var Ui::Resultat* Resultat::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesginer pour génerer le resultat.
     */
    Ui::Resultat *design;

    /**
        @var CompteManager& Resultat::cm
        @brief cm représente le CompteManager.
    */
    CompteManager& cm = CompteManager::getInstance();

    /**
     * @var TransactionManager& Resultat::tm
     * @brief tm représente le TransactionManager.
     */
    TransactionManager& tm = TransactionManager::getInstance();
};

#endif // RESULTAT_H
