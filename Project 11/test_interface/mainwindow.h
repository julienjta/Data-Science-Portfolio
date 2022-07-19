#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/**
    @file mainwindow.h
    @brief mainwindow permet de gérer la fenêtre princiale de notre interface.
    @author Jérémy Godde
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/


#include "../Compte/header/CompteManager.h" //notre noyau applicatif

#include "ajouterwindow.h"
#include "deplacercompte.h"
#include "ajoutertransactionwindows.h"
#include "modifiertransaction.h"
#include "chargementwindow.h"
#include "savewindow.h"
#include "parametrewindow.h"

#include "bilan.h"
#include "releve.h"
#include "resultat.h"
#include "rapprochement.h"
#include "cloture.h"


/**
    @class Ui::fenetrePrincipale "mainwindow.h"
    @brief Classe qui représente la fenêtre principale de l'interface, réalisée sur QTDesginer.
*/
namespace Ui {
class fenetrePrincipale;
}

/**
 * @class QTreeWidgetPerso "mainwindow.h"
 * @brief herite de QTreeWidget, permet de définir le comportement du drag&drop
 */

class QTreeWidgetPerso : public QTreeWidget
{
    Q_OBJECT
public:
    /**
     * @fn  QTreeWidgetPerso::QTreeWidgetPerso(QWidget *parent)
     * @brief Constructeur du QTreeWidget
     * @param parent : QWidget*, fenêtre parent
     */
    QTreeWidgetPerso(QWidget* _parent);
    /**
     * @fn QTreeWidgetPerso::~QTreeWidgetPerso
     * @brief Destructeur du QTreeWidgetPerso
    */
    ~QTreeWidgetPerso() override = default;

signals:
    /**
     * @fn void QTreeWidgetPerso::dragAndDrop(int _id_bouge,int _id_recoit);
     * @brief dragAndDrop est un signal émis lorsque l'utilisateur tente de déplacer un compte dans le QTreeWidget.
     * @param _id_bouge : int, id du compte que l'utilisateur est en train de déplacer
     * @param _id_recoit : int, id du compte sous lequel l'utilisateur a déplacé le compte
     */
    void dragAndDrop(int _id_bouge,int _id_recoit);

private:
    /**
     * @fn void QTreeWidgetPerso::dropEvent(QDropEvent* event) override
     * @brief Méthode utilisée pour gérer le drag&drop
     * @param event : QDropEvent*, QDropEvent représente l'évènement d'un drop dans le Qtreewidget.
     */
    void dropEvent(QDropEvent* event) override;
};

/**
 * @class MainWindow  "mainwindow.h"
 * @brief Définit le comportement de la fenêtre principale
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @fn  MainWindow::MainWindow(QWidget *parent=nullptr) explicit
     * @brief Constructeur de la fenêtre fenêtre principale.
     * @param parent : QWidget*, fenêtre parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @fn QString MainWindow::getDevise() const
     * @brief Méthode qui retourne la devise.
     * @return La devise
     */
    QString getDevise() const { return devise; }

    /**
     * @fn QString MainWindow::getFormatDate() const
     * @brief Méthode qui retourne le format de date.
     * @return Le format de date
     */
    QString getFormatDate() const { return formatDate; }

    /**
     * @fn  MainWindow::~MainWindow() override
     * @brief Destructeur de la fenêtre principale.
     */
    ~MainWindow() override;

private slots:
    /**
     * @fn void MainWindow::afficherFormulaireCompte()
     * @brief afficherFormulaireCompte ouvre une fenêtre permettant de créer un compte.
    */
    void afficherFormulaireCompte();

    /**
     * @fn void MainWindow::afficherFormulaireDeplacerCompte()
     * @brief afficherFormulaireDeplacerCompte ouvre une fenêtre permettant de déplacer un compte.
     */
    void afficherFormulaireDeplacerCompte();
    /**
     * @fn void MainWindow::afficherFormulaireTransaction()
     * @brief afficherFormulaireTransaction ouvre une fenêtre permettant de créer une transaction.
     */
    void afficherFormulaireTransaction();

    /**
     * @fn void MainWindow::afficherFormulaireEnregistrement()
     * @brief afficherFormulaireEnregistrement ouvre une fenêtre permettant d'enregistrer la session actuelle.
     */
    void afficherFormulaireEnregistrement();

    /**
     * @fn void MainWindow::afficherFormulaireEnregistrementSous()
     * @brief afficherFormulaireEnregistrementSous ouvre une fenêtre permettant d'enregistrer sous la session actuelle.
     */
    void afficherFormulaireEnregistrementSous();

    /**
     * @fn void MainWindow::afficherFormulaireOuvrir_1()
     * @brief afficherFormulaireOuvrir_1 ouvre une fenêtre permettant à l'utilisateur de sauvegarder sa session actuelle avant de charger un fichier(grâce à afficherFormulaireOuvrir_2())
     */
    void afficherFormulaireOuvrir_1();

    /**
     * @fn void MainWindow::aficherFormulaireOuvrir_2()
     * @brief afficherFormulaireOuvrir_2 ouvre une fenêtre permettant à l'utilisateur de choisir un fichier à charger.
     */
    void afficherFormulaireOuvrir_2();

    /**
     * @fn void MainWindow::afficherFormulaireModificationTransaction()
     * @brief afficherFormulaireModificationTransaction ouvre une fenêtre permettant de modifier une transaction.
     */
    void afficherFormulaireModificationTransaction();

    /**
     * @fn void MainWindow::afficherBilan()
     * @brief afficherBilan ouvre une fenêtre permettant d'effectuer le bilan des comptes passifs/actifs.
     */
    void afficherBilan();

    /**
     * @fn void MainWindow::afficherReleve()
     * @brief afficherReleve ouvre une fenêtre permettant d'effectuer le releve des comptes dépenses/recettes.
     */
    void afficherReleve();

    /**
     * @fn void MainWindow::afficherResultat()
     * @brief afficherResultat ouvre une fenêtre permettant d'afficher le bilan.
     */
    void afficherResultat();

    /**
     * @fn void MainWindow::afficherRapprochement()
     * @brief afficherRapprochement ouvre une fenêtre permettant de rapprocher un compte.
     */
    void afficherRapprochement();

    /**
     * @fn void MainWindow::afficherCloture()
     * @brief afficherCloture ouvre une fenêtre permettant d'effectuer une cloture.
     */
    void afficherCloture();

    /**
     * @fn void MainWindow::afficherParametre()
     * @brief afficherParametre ouvre une fenêtre permettant d'accéder aux paramètres de l'application.
     */
    void afficherParametre();

    /**
     * @fn void MainWindow::selectionnerCompte(QTreeWidgetItem* _item_compte)
     * @brief selectionnerCompte permet de mettre à jour l'attribut compte_selectionne, de débloquer l'action supprimer compte, et si le compte est Reel les informations de l'onglet Compte sur la fenêtre principal (date rapprochement,poste, opérations).
     * @param _item_compte : QTreeWidgetItem*, compte (QTreeWidgetItem)  sélectionné sur le QTreeWidget.
     */
    void selectionnerCompte(QTreeWidgetItem* _item_compte);

    /**
     * @fn void MainWindow::deplacerCompte(int const _id_bouge, int const _id_recoit)
     * @brief deplacerCompte permet de déplacer un compte dans la hiérarchie des comptes (suite à un drag&drop)
     * @param _id_bouge : int const, id du compte que l'on souhaite déplacé
     * @param _id_recoit : int cont, id du compte sous lequel on souhaire déplacé le compte (nouveau père)
     */
    void deplacerCompte(int const _id_bouge, int const _id_recoit);

    /**
     * @fn void MainWindow::selectionnerTransaction(int row,int column)
     * @brief selectionnerTransaction permet de mettra à jour l'attribut transac_selectionne et déploquer les actions supprimer et modifier transaction.
     * @param row : int, ligne du tableau de transaction sélectionnée
     * @param column : int, colonne du tableau de transaction sélectionée
     */
    void selectionnerTransaction(int row,int column);

    /**
     * @fn void MainWindow::supprimerCompte()
     * @brief supprimerCompte permet de supprimer un compte de la hiérarchie des comptes.
     */
    void supprimerCompte();

    /**
     * @fn void MainWindow::supprimerTransaction()
     * @brief supprimerTransaction permet de supprimer une transaction.
     */
    void supprimerTransaction();

    /**
     * @fn void MainWindow::chargerContexte(string const& _path)
     * @brief chargerContexte permet de charger le contexte sauvegardé dans le fichier dont le chemin est passé en paramètre (devise et format)
     * @param _path : string const&, chemin du fichier à charger
     */
    void chargerContexte(string const& _path);

    /**
     * @fn void MainWindow::charger(QString fichier)
     * @brief charger permet de charger le fichier dont le chemin est passé en paramètre (hierarchie des comptes, transaction, contexte (grâce à chargerContexte))
     * @param fichier : QString, chemin du fichier à charger
     */
    void charger(QString fichier);

    /**
     * @fn void MainWindow::initialiser()
     * @brief initialiser permet d'initialiser l'application si on décide de ne pas charger un fichier à l'ouverture de cette dernière.
     */
    void initialiser();

    /**
     * @fn void MainWindow::ajouterContexte(string const& _path)
     * @brief ajouterContexte permet d'ajouter le contexte au fichier dont le chemin est passé au paramètre.
     * @param _path : string const&, chemin du fichier auquel on souhaire ajouter le contexte
     */
    void ajouterContexte(string const& _path);

    /**
     * @fn void MainWindow::refreshContexte(QStringList params)
     * @brief refreshContexte permet de mettre à jour le contexte : devise et format de date.
     * @param params : QStringList, QStringList comportant les nouvelles valeurs de la devise et du format de date.
     */
    void refreshContexte(QStringList params);

    /**
     * @fn void MainWindow::sauvegarder(QString fichier)
     * @brief sauvegarder permet de sauvegarder la session actuelle dans un fichier donc le chemin est passé en paramètre.
     * @param fichier : QString, chemin du fichier dans lequel on souhaite sauvegarder la session actuelle
     */
    void sauvegarder(QString fichier);

    /**
     * @fn void MainWindow::afficherHierarchie()
     * @brief afficherHierarchie permet d'afficher la Hierarchie des comptes dans le QTree.
     */
    void afficherHierarchie();

    /**
     * @fn void MainWindow::afficherTransaction()
     * @brief afficherTransaction permet d'afficher le tableau de transactions dans l'onglet Transaction.
     */
    void afficherTransaction();

    /**
     * @fn void MainWindow::afficherCompte()
     * @brief afficherCompte permet d'afficher le tableau des opérations du compte sélectionné.
     */
    void afficherCompte();

    /**
     * @fn void MainWindow::setSizeObjects()
     * @brief setSizeObjects permet de calculer la dimension de chaque objet de la fenêtre par rapport à la taille de cette dernière.
     */
    void setSizeObjects();

    /**
     * @fn void MainWindow::resizeEvent(QResizeEvent* event) override
     * @brief resizeEvent est une méthode de QWidget surchargé qui est applée lorsque la fenêtre change de taille.
     * @param event : QResizeEvent*, évenement déclenché lorsqu'on change de tialle la fenêtre
     */
    void resizeEvent(QResizeEvent* event) override;


private:
    /**
     * @var  Ui::fenetrePrincipale* MainWindow::design;
     * @brief design représente la fenêtre principale réalisée sur QTDesigner.
    */
    Ui::fenetrePrincipale *design;

    /**
        @var CompteManager& MainWindow::compte_manager
        @brief compte_manager représente le CompteManager.
    */
    CompteManager& compte_manager = CompteManager::getInstance();

    /**
     * @var TransactionManager& MainWindow::transaction_manager
     * @brief transaction_manager représente la TransactionManager
     */
    TransactionManager& transaction_manager = TransactionManager::getInstance();

    /**
     * @var QTreeWidgetItem*::MainWindow::compte_selectionne
     * @brief compte_selectionne représente le compte (QTreeWidget) selectionnée dans le QTree.
     */
    QTreeWidgetItem* compte_selectionne = nullptr;

    /**
     * @var QTreeWidgetItem*::MainWindow::transac_selectionne
     * @brief transac_selectionne représente la transaction (QTableWidgetItem) selectionnée dans le tableau de transaction.
     */
    QTableWidgetItem* transac_selectionne = nullptr;

    /**
     * @var QString MainWindow::devise
     * @brief devise représente la devise (€,$,...).
     */
    QString devise = QString("€");
    /**
     * @var QString MainWindow::formatDate
     * @brief formatDate représente le format de date
     */
    QString formatDate = QString("dd/mm/yy");
};

#endif // MAINWINDOW_H
