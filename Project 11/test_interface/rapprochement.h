#ifndef RAPPROCHEMENT_H
#define RAPPROCHEMENT_H
/**
    @file rapprochement.h
    @brief rapprochement permet de gérer la fenêtre graphique utilisée pour rapprocher un compte.
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
    @class Ui::rapprochement "rapprochement.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour rapprocher un compte.
*/
namespace Ui {
class rapprochement;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class rapprochement "rapprochement.h"
    @brief rapprochement permet de gérer la fenêtre graphique utilisée pour rapprocher un compte.
*/
class rapprochement : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  rapprochement::rapprochement(QStringList const _comptes, std::list<int> const _liste_id, MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de rapprocher un compte.
     * @param _comptes : QStringList const, liste des comptes réels de la hierarchie
     * @param _liste_id : std::list<int> const liste des ids des comptes réels de la hierarchie correspondant aux compte de _comptes
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit rapprochement(QStringList const _comptes, std::list<int> const _liste_id, MainWindow *parent);
    /**
      * @fn rapprochement::~rapprochement()
      * @brief Destructeur de la fenêtre graphique permettant de rapprocher un compte.
    */
    ~rapprochement();

signals:
    /**
     * @fn void rapprochement::modifiant()
     * @brief modifiant est un signal qui est émis lorsque l'utilisateur clique sur "Modifier la transaction". Il sera capté par la classe MainWindow afin de mettre à jour le tableau de transactions.
     */
    void modifiant();

private slots:
    /**
     * @fn void rapprochement::changementCompte()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "selectionner un autre compte". Il permet à l'utilisateur d'avoir accès à la liste déroulante de comptes pour choisir un nouveau compte à rapprocher et de masquer les autres champs inutiles de la fenêtre grâce à la fonction: void choixCompte().
     */
    void changementCompte();

    /**
     * @fn void rapprochement::validerChoixCompte()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "Valider" après avoir choisi un compte à rapprocher. Il permet de bloquer la liste permettant de choisir un compte à rapprocher et d'afficher les champs précedemment cachés.
     */
    void validerChoixCompte();

    /**
     * @fn void rapprochement::ajouterOperation()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "ajouter une opération". Il permet d'ajouter une opération à la fenêtre graphique.
     */
    void ajouterOperation();

    /**
     * @fn void rapprochement::supprimerDernier()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "supprimer" à la fin d'une ligne opération. Il permet de supprimer une opération à la fenêtre graphique.
     */
    void suppressionDernier();

    /**
     * @fn void rapprochement::modifierListeTransaction()
     * @brief Ce slot est applé lorsque l'utilisateur clique sur le bouton "Valider" après avoir choisi un compte à rapprocher. Il permet d'afficher les transactions que l'utilisateur peut modifié.
     */
    void modifierListeTransactions();

    /**
     * @fn void rapprochement::modiferListeOperation()
     * @brief Ce slot est appelé lorsque l'utilisateur sélectionne une transaction dans la liste de transaction. Il permet d'afficher les informations de la transaction sélectionnée afin que l'utilisateur puisse la modifier.
     */
    void modifierListeOperations();

    /**
     * @fn void rapprochement::modifierTransaction()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "modifier la transaction". Il permet de vérifier les informations saisies par l'utilisateur et si elles sont correctes de modifier la transaction.
     */
    void modifierTransaction();

    /**
     * @fn void rapprochement::validerCompte()
     * @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "valider le compte". Il permet de rapprocher le compte sélectionné.
     */
    void validerCompte();

private:
    /**
     * @var Ui::rapprochement* rapprochement::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour rapprocher un compte.
     */
    Ui::rapprochement *design;

    /**
        @var CompteManager& rapprochement::cm
        @brief cm représente le CompteManager.
    */
    CompteManager& cm = CompteManager::getInstance();

    /**
     * @var TransactionManager& rapprochement::tm
     * @brief tm représente le TransactionManager.
     */
    TransactionManager& tm = TransactionManager::getInstance();

    /**
     * @var QStringList const rapprochement::comptes
     * @brief compte représente la liste des comptes réels de la hierarchie.
     */
    QStringList const comptes;

    /**
     * @var std::list<int> const rapprochement::liste_id
     * @brief liste_id représente la liste des ids des comptes réels de la hierarchie correspondant aux compte : comptes.
     */
    std::list<int> const liste_id;

    /**
     * @var QString rapprochement::devise
     * @brief devise représente la devise (€,$,...).
     */
    QString devise = QString("€");

    /**
     * @var QList<QComboBox*> rapprochement::selecteurs
     * @brief selecteur est une liste de QComboBox*. Chaque QComboBox contient la liste des comptes auxquels ont peut attribués une opération. Il y a autant de QComboBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QComboBox*> selecteurs;

    /**
     * @var QList<QDoubleSpinBox*> rapprochement::credits
     * @brief credits est une liste de QDoubleSpinBox*. Chaque QDoubleSpinBox correspond au crédit d'une opération. Il y a autant de QDoubleSpinBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QDoubleSpinBox*> credits;

    /**
     * @var QList<QDoubleSpinBox*> rapprochement::debits
     * @brief debits est une liste de QDoubleSpinBox*. Chaque QDoubleSpinBox correspond au débit d'une opération. Il y a autant de QDoubleSpinBox dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QDoubleSpinBox*> debits;

    /**
     * @var QList<QPushButton*> rapprochement::supprimers
     * @brief supprimers est une liste de QPushButton*. Chaque QPushButton* correspond au boutton supprimer à la fin de la ligne d'une opération. Il y a autant de QPushButton* dans liste qu'il y a d'opérations dans la transaction.
    */
    QList<QPushButton*> supprimers;

    /**
     * @fn void rapprochement::choixCompte()
     * @brief choixCompte permet à l'utilisateur de sélectionner une compte à rapprocher : il permet à l'utilisateur d'avoir accès à la liste déroulante de compte pour choisir un nouveau compte à rapprocher et de masquer les autres champs inutiles de la fenêtre.
     */

    void choixCompte();

    /**
     * @fn void rapprochement::clear()
     * @brief clear est appelé lorsque l'utilisateur choisi un nouveau compte à rapprocher. Il permet de vider les listes selecteurs, credits, debits et supprimers.
     */
    void clear();
};

#endif // RAPPROCHEMENT_H
