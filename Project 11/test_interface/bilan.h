#ifndef BILAN_H
#define BILAN_H

/**
    @file bilan.h
    @brief bilan permet de gérer la fenêtre graphique utilisée pour générer le bilan actif/passif.
    @author Ophélie Delattre, Jérémy Godde
    @version v3
    @date 08 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "../Compte/header/CompteManager.h"
#include <QDialog>
#include <QPaintEvent>
#include <QPdfWriter>
#include <QMessageBox>

/**
    @class Ui::bilan "bilan.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour faire le bilan actif/passif
*/
namespace Ui {
class bilan;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class bilan "bilan.h"
    @brief bilan permet de générer le bilan actif/passif (donne à une date donnée, le total des créances et dettes et leur répartition dans les sous-comptes).
*/
class bilan : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  bilan::bilan(MainWIndow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de générer le bilan actif/passif.
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit bilan(MainWindow *parent);

    /**
     * @fn bilan::~bilan()
     * @brief Destructeur de la fenêtre graphique permettant de générer le bilan actif/passif.
    */
    ~bilan();

private slots:
    /**
        @fn void bilan::fairebilan()
        @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "Afficher bilan".  Il permet de faire le bilan, c'est à dire qui synthétise l'ensemble de ce que possède l'association (l'actif) et ce que l'association doit aux tiers (le passif)à la fin d'une période donnée, ainsi que leur répartition dans les sous-comptes.
    */
    void fairebilan();
    /**
     * @fn void bilan::exporterPDF()
     * @brief génére un document PDF correspond au relevé généré
     */
    void exporterPDF();

private:
    /**
     * @var  QDateEdit * bilan::date
     * @brief date est un widget qui permettra à l'utilisateur d'entrer la date pour laquelle il souhaite obtenir le bilan.
     */
    QDateEdit *date;
    /**
     * @var QString bilan::devise
     * @brief devise représente le symbole monnaitaire à afficher sur le bilan. Il dépend de la fenêtre parent
     */
    QString devise;
    /**
     * @var bool bilan::est_genere
     * @brief est_genere marque la bonne exécution de releve::fairebilan() et autorise quand il vaut true l'exécution de bilan::exporterPDF()
     */
    bool est_genere = false;
    /**
     * @var Ui::bilan* bilan::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour faire l'opération de bilan
     */
    Ui::bilan *design;

    /**
     * @fn void bilan::affichertableau(QTableWidget* const _tableau, std::list<CompteHierarchie*> _liste_comptes)
     * @brief génére le contenu du QTableWidget passé en associant à chaque compte son solde sur la période choisie
     * @param _tableau : QTableWidget* const, tableau sur lequel travailler
     * @param _liste_comptes : std::list<CompteHierarchie*> const, liste des comptes a figuré dans le tableau
     * @return le solde total de la liste des comptes
     */
    double affichertableau(QTableWidget* const _tableau, std::list<CompteHierarchie*> const _liste_comptes);

    /**
     * @fn int bilan::makeTableForPDF(QTableWidget* const _tableau, int const _y_origin, QPainter* _painter, QFont* _f)
     * @brief peint le tableau dans le PDF
     * @param _tableau : QTableWidget* const, tableau à peindre dans le PDF
     * @param _y_origin : int const, hauteur à laquelle commencer à peindre
     * @param _painter : QPainter*, pointeur associé au PDF dans lequel peindre le tableau
     * @param _f : QFont*, pointeur associé au paramètre de police
     * @return la hauteur à laquelle le tableau se termine
     */
    int makeTableForPDF(QTableWidget* const _tableau, int const _y_origin, QPainter* _painter, QFont* _f);
};

#endif // BILAN_H
