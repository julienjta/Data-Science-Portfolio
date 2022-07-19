#ifndef CLOTURE_H
#define CLOTURE_H
/**
    @file cloture.h
    @brief cloture permet de gérer la fenêtre graphique utilisée pour effectuer une cloture.
    @author Ophélie Delattre
    @version v3
    @date 11 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/

#include <QDialog>
#include "../Compte/header/CompteManager.h"
/**
    @class Ui::cloture "cloture.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour effectuer une cloture.
*/
namespace Ui {
class cloture;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class cloture "cloture.h"
    @brief cloture permet de gérer la fenêtre graphique utilisée pour charger effectuer une cloture.
*/
class cloture : public QDialog
{
    Q_OBJECT

public:
    /**
     * @fn  cloture:cloture(std::list<int> const _liste_id, MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant d'effectuer une cloture.
     * @param _liste_id : std::list<int> const, liste des ids des comptes de la hierarchie
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit cloture(std::list<int> const _liste_id, MainWindow *parent);

    /**
     * @fn cloture::~cloture()
     * @brief Destructeur de la fenêtre graphique permettant d'effectuer une cloture.
    */
    ~cloture();

signals:
    /**
     * @fn void cloture::ajout()
     * @brief ajout est un signal émit à la fin de la cloture. Il sera capté par la classe MainWindow afin de mettre à jour le QTree (représentant la hiérarchie des comptes)
     */
    void ajout();
    /**
     * @fn void cloture::ajouttransaction()
     * @brief ajouttransaction est un signal émis à la fin de la cloture. Il sera cpaté par la classe MainWindow afin de mettre à ajour le tableau de transactions.
     */
    void ajouttransaction();

private slots:

    /**
     * @fn void cloture::nvcomptecloture()
     * @brief Ce slot est appelé lorsque l'utilisateur modifie la valeur courante des listes déroulantes permettant de choisir le compte de cloture. Lorsque le texte courant vaut "Nouveau", le formulaire permettant de créer un nouveau compte de cloture est affiché.
     * @param text : const QString&, texte courant de la liste déroulante permettant de choisir le compte de cloture
    */
    void nvcomptecloture(const QString&);

    /**
        @fn void cloture::fairecloture()
        @brief Ce slot est appelé lorsque l'utilisateur clique sur le bouton "OK".  Il permet d'effectuer une cloture, c'est à dire remettre à zéro les comptes de recettes et de dépenses par l’intermédiaire d’un compte appelé Résultat et à transférer la différence vers un compte appelé Excédentou Déficit.
    */
    void fairecloture();


private:
    /**
        @var CompteManager& cloture::cm
        @brief cm représente le CompteManager.
    */
    CompteManager& cm;

    /**
     * @var Ui::cloture* cloture::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour effectuer une cloture.
     */
    Ui::cloture *design;
};

#endif // CLOTURE_H
