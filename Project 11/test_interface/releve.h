#ifndef RELEVE_H
#define RELEVE_H

/**
    @file releve.h
    @brief releve permet de gérer la fenêtre graphique et d'effectuer l'opération de relevé.
    @author Ophélie Delattre, Jérémy Godde
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include "../Compte/header/CompteManager.h"
#include <QDialog>
#include <QTabWidget>
#include <QPaintEvent>
#include <QPdfWriter>
#include <QMessageBox>

/**
    @class Ui::releve "releve.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesigner pour effectuer un relevé.
*/

namespace Ui {
class releve;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class releve "releve.h"
    @brief releve permet de gérer la fenêtre graphique et d'effectuer l'opération de relevé.
*/

class releve : public QDialog
{
    Q_OBJECT


public:
    /**
     * @fn releve::releve(MainWindow* parent) explicit
     * @brief Constructeur de la fenêtre relevé
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit releve(MainWindow* parent);

    /**
     * @fn releve::~releve() override
     * @brief Destructeur de la fenêtre relevé
     */
    ~releve() override;

private slots:
    /**
     * @fn void releve::fairereleve()
     * @brief effectuer l'opération bancaire de relevé
     */
    void fairereleve();
    /**
     * @fn void releve::exporterPDF()
     * @brief génére un document PDF correspond au relevé généré
     */
    void exporterPDF();

private:
    /**
     * @var QDateEdit* releve::debut
     * @brief debut représente le champs permettant au client de choisir la date de début de la période sur laquelle faire le relevé
     */
    QDateEdit *debut;
    /**
     * @var QDateEdit* releve::fin
     * @brief fin représente le champs permettant au client de choisir la date de fin de la période sur laquelle faire le relevé
     */
    QDateEdit* fin;
    /**
     * @var QString releve::devise
     * @brief devise représente le symbole monnaitaire à afficher sur le relevé. Il dépend de la fenêtre parent
     */
    QString devise;
    /**
     * @var bool releve::est_genere
     * @brief est_genere marque la bonne exécution de releve::fairereleve() et autorise quand il vaut true l'exécution de releve::exporterPDF()
     */
    bool est_genere = false;
    /**
     * @var Ui::releve* releve::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesginer pour faire l'opération de relevé
     */
    Ui::releve *design;

    /**
     * @fn void releve::affichertableau(QTableWidget* const _tableau, std::list<CompteHierarchie*> _liste_comptes)
     * @brief génére le contenu du QTableWidget passé en associant à chaque compte son solde sur la période choisie
     * @param _tableau : QTableWidget* const, tableau sur lequel travailler
     * @param _liste_comptes : std::list<CompteHierarchie*> const, liste des comptes a figuré dans le tableau
     */
    void affichertableau(QTableWidget* const _tableau, std::list<CompteHierarchie*> const _liste_comptes);

    /**
     * @fn int releve::makeTableForPDF(QTableWidget* const _tableau, int const _y_origin, QPainter* _painter, QFont* _f)
     * @brief peint le tableau dans le PDF
     * @param _tableau : QTableWidget* const, tableau à peindre dans le PDF
     * @param _y_origin : int const, hauteur à laquelle commencer à peindre
     * @param _painter : QPainter*, pointeur associé au PDF dans lequel peindre le tableau
     * @param _f : QFont*, pointeur associé au paramètre de police
     * @return la hauteur à laquelle le tableau se termine
     */
    int makeTableForPDF(QTableWidget* const _tableau, int const _y_origin, QPainter* _painter, QFont* _f);
};

#endif // RELEVE_H
