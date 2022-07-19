#ifndef MODIFIERTRANSACTION_H
#define MODIFIERTRANSACTION_H
/**
    @file modifiertransaction.h
    @brief modifiertransaction permet de gérer la fenêtre graphique utilisée pour modifier une transaction.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
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
    @class Ui::modifiertransaction "modifiertransaction.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour modifier une transaction.
*/
namespace Ui {
class modifiertransaction;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class modifiertransaction "modifiertransaction.h"
    @brief modifiertransaction permet de gérer la fenêtre graphique utilisée pour modifier une transaction.
*/
class modifiertransaction : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  modifiertransaction::modifiertr(QStringList const _reference,QStringList const _comptes, std::list<int> const liste_id, MainWIndow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de modifier une transaction.
     * @param _reference : QString const, reférence de la transaction à modifiée (celle sélectionné dans le tableau transaction)
     * @param _comptes : QStringList const, liste des comptes réels de la hierarchie
     * @param _liste_id : std::list<int> const liste des ids des comptes réels de la hierarchie correspondant aux compte de _comptes
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit modifiertransaction(QString const _reference, QStringList const _comptes, std::list<int> const _liste_id, MainWindow *parent);

    /**
     * @fn modifiertransaction::~modifiertransaction()
     * @brief Destructeur de la fenêtre graphique permettant de modifier une transaction.
     */
    ~modifiertransaction();

signals:
    /**
     * @fn void modifiertransaction::modifiant()
     * @brief modifiant est un signal qui est émis lorsqu'une transaction a été modifiée. Il sera capté par la classe MainWindow afin de mettre à jour le tableau de transactions.
     */
    void modifiant();

private slots:
    /**
     * @fn void modifiertransaction::ajouterOperation()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "ajouter une opération". Il permet d'ajouter une opération à la fenêtre graphique.
     */
    void ajouterOperation();
    /**
     * @fn void modifiertransaction::supprimerDernier()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "supprimer" à la fin d'une ligne opération. Il permet de supprimer une opération à la fenêtre graphique.
     */
    void suppressionDernier();
    /**
     * @fn void modifiertransaction::modifierTransaction()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "OK". Il permet de vérifier les informations saisies par l'utilisateur et si elles sont correctes de modifier la transaction.
     */
    void modifierTransaction();

private:
    /**
     * @var Ui::modifiertransaction* modifiertransaction::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour modifier une transaction.
     */
    Ui::modifiertransaction *design;

    /**
        @var CompteManager& modifiertransaction::cm
        @brief cm représente le CompteManager.
    */
    CompteManager& cm = CompteManager::getInstance();

    /**
     * @var TransactionManager& modifiertransaction::tm
     * @brief tm représente le TransactionManager.
     */
    TransactionManager& tm = TransactionManager::getInstance();

    /**
     * @var QStringList const modifiertransaction::comptes
     * @brief compte représente la liste des comptes réels de la hierarchie.
     */
    QStringList const comptes;

    /**
     * @var std::list<int> const modifiertransaction::liste_id
     * @brief liste_id représente la liste des ids des comptes réels de la hierarchie correspondant aux compte : comptes.
     */
    std::list<int> const liste_id;

    /**
     * @var QList<QComboBox*> modifiertransaction::selecteurs
     * @brief selecteur est une liste de QComboBox*. Chaque QComboBox contient la liste des comptes auxquels ont peut attribués une opération. Il y a autant de QComboBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QComboBox*> selecteurs;

    /**
     * @var QList<QDoubleSpinBox*> modifiertransaction::credits
     * @brief credits est une liste de QDoubleSpinBox*. Chaque QDoubleSpinBox correspond au crédit d'une opération. Il y a autant de QDoubleSpinBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QDoubleSpinBox*> credits;

    /**
     * @var QList<QDoubleSpinBox*> modifiertransaction::debits
     * @brief debits est une liste de QDoubleSpinBox*. Chaque QDoubleSpinBox correspond au débit d'une opération. Il y a autant de QDoubleSpinBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QDoubleSpinBox*> debits;

    /**
     * @var QList<QPushButton*> modifiertransaction::supprimers
     * @brief supprimers est une liste de QPushButton*. Chaque QPushButton* correspond au boutton supprimer à la fin de la ligne d'une opération. Il y a autant de QPushButton* dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QPushButton*> supprimers;

    /**
     * @var QString modifiertransaction::reference
     * @brief reference est la référence de la transaction que l'on modifie.
     */
    QString reference;
    /**
     * @var QString modifiertransaction::devise
     * @brief devise représente la devise (€,$,...).
     */
    QString devise = QString("€");
};

#endif // MODIFIERTRANSACTION_H
