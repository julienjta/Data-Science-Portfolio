#ifndef AJOUTERTRANSACTIONWINDOWS_H
#define AJOUTERTRANSACTIONWINDOWS_H
/**
    @file ajoutertransactionwindows.h
    @brief ajoutertransactionwindows permet de gérer la fenêtre graphique utilisée pour ajouter des transactions.
    @author Jérémy Godde
    @version v3
    @date 07 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include <QDialog>
#include <QtWidgets>
#include <QMessageBox>
#include <list>
#include "../Compte/header/CompteManager.h"

/**
    @class Ui::fenetreAjouterTransaction "ajoutertransactionwindows.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour ajouter des transactions
*/

namespace Ui {
class fenetreAjouterTransaction;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class ajoutertransactionwindows "ajoutertransactionwindows.h"
    @brief ajoutertransactionwindows permet de gérer la fenêtre graphique utilisée pour ajouter des transactions.
*/


class ajoutertransactionwindows : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  ajoutertransactionwindows::ajoutertransactionwindows(QStringList const _comptes, std::list<int> const liste_id, MainWIndow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant d'ajouter des transactions.
     * @param _comptes : QStringList const, liste des comptes réels de la hierarchie
     * @param _liste_id : std::list<int> const liste des ids des comptes réels de la hierarchie correspondant aux compte de _comptes
     * @param parent : MainWindow*, fenêtre parent
     */

    explicit ajoutertransactionwindows(QStringList const _comptes, std::list<int> const liste_id, MainWindow *parent);
    /**
     * @fn ajoutertransactionwindows::~ajoutertransactionwindows()
     * @brief Destructeur de la fenêtre graphique permettant d'ajouter des transactions.
    */
    ~ajoutertransactionwindows();

signals:
    /**
     * @fn void ajoutertransactionwindows::signalDone()
     * @brief signalDone est un signal qui est émis lorsqu'une transaction a été ajoutée. Il sera capté par la classe MainWindow afin de mettre à jour le tableau de transactions.
     */
    void signalDone();

private slots:
    /**
     * @fn void ajoutertransactionwindows::ajouterOperation()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "ajouter une opération". Il permet d'ajouter une opération à la fenêtre graphique.
     */
    void ajouterOperation();
    /**
     * @fn void ajoutertransactionwindows::supprimerDernier()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "supprimer" à la fin d'une ligne opération. Il permet de supprimer une opération à la fenêtre graphique.
     */
    void suppressionDernier();
    /**
     * @fn void ajoutertransactionwindows::verifier()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "OK". Il permet de vérifier les informations saisies par l'utilisateur et si elles sont correctes d'ajouter la transaction.
     */
    void verifier();

private:
    /**
        @var CompteManager& ajoutertransactionwindows::cm
        @brief cm représente le CompteManager.
    */
    CompteManager& cm;

    /**
     * @var TransactionManager& ajoutertransactionwindows::tm
     * @brief tm représente le TransactionManager.
     */
    TransactionManager& tm;

    /**
     * @var QStringList const ajoutertransactionwindows::comptes
     * @brief compte représente la liste des comptes réels de la hierarchie.
     */
    QStringList const comptes;

    /**
     * @var std::list<int> const ajoutertransactionwindows::liste_id
     * @brief liste_id représente la liste des ids des comptes réels de la hierarchie correspondant aux compte : comptes.
     */
    std::list<int> const liste_id;

    /**
     * @var QString ajoutertransactionwindows::devise
     * @brief devise représente la devise (€,$,...).
     */
    QString devise  = QString("€");

    /**
     * @var  QDateEdit * ajoutertransactionwindows::qdate
     * @brief qdate est un widget qui permettra à l'utilisateur d'entrer la date de la transaction.
     */
    QDateEdit *qdate;

    /**
     * @var  QTimeEdit * ajoutertransactionwindows::qtime
     * @brief qtime est un widget qui permettra à l'utilisateur d'entrer l'heure de la transaction.
     */
    QTimeEdit *qtime;

    /**
     * @var QList<QComboBox*> ajoutertransactionwindows::selecteurs
     * @brief selecteur est une liste de QComboBox*. Chaque QComboBox contient la liste des comptes auxquels ont peut attribués une opération. Il y a autant de QComboBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QComboBox*> selecteurs;

    /**
     * @var QList<QDoubleSpinBox*> ajoutertransactionwindows::credits
     * @brief credits est une liste de QDoubleSpinBox*. Chaque QDoubleSpinBox correspond au crédit d'une opération. Il y a autant de QDoubleSpinBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QDoubleSpinBox*> credits;

    /**
     * @var QList<QDoubleSpinBox*> ajoutertransactionwindows::debits
     * @brief debits est une liste de QDoubleSpinBox*. Chaque QDoubleSpinBox correspond au débit d'une opération. Il y a autant de QDoubleSpinBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QDoubleSpinBox*> debits;

    /**
     * @var QList<QPushButton*> ajoutertransactionwindows::supprimers
     * @brief supprimers est une liste de QPushButton*. Chaque QPushButton* correspond au boutton supprimer à la fin de la ligne d'une opération. Il y a autant de QPushButton* dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QPushButton*> supprimers;

    /**
     * @var  Ui::fenetreAjouterTransaction* ajoutertransactionwindows::design;
     * @brief design représente la fenêtre graphique réalisée sur QTDesginer pour ajouter des transactions
    */
    Ui::fenetreAjouterTransaction *design;
};

#endif // AJOUTERTRANSACTIONWINDOWS_H
