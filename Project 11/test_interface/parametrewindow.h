#ifndef PARAMETREWINDOW_H
#define PARAMETREWINDOW_H
/**
    @file parametrewindow.h
    @brief parametrewindow permet de gérer la fenêtre graphique utilisée pour consulter/modifier les paramètres de l'application.
    @author Axel Huillard
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

/**
    @class Ui::parametrewindow "parametrewindow.h"
    @brief Classe qui représente la fenêtre graphique réalisée sur QTDesginer pour consulter/modifer les paramètres de l'application.
*/
namespace Ui{
    class parametrewindow;
}

/**
    @see @class MainWindow "mainwindow.h"
*/
class MainWindow;

/**
    @class parametrewindow "parametrewindow.h"
    @brief parametrewindow permet de gérer la fenêtre graphique utilisée pour consulter/modifer les paramètres de l'application.
*/
class parametrewindow : public QDialog
{
  Q_OBJECT

  public :
    /**
     * @fn  parametrewindow::parametrewindow(MainWindow *parent) explicit
     * @brief Constructeur de la fenêtre graphique permettant de consulter/modifer les paramètres de l'application.
     * @param parent : MainWindow*, fenêtre parent
     */
    explicit parametrewindow(MainWindow *parent);

    /**
      @fn parametrewindow::~parametrewindow()
      @brief Destructeur de la fenêtre graphique permettant de consulter/modifer les paramètres de l'application.
    */
    ~parametrewindow();

  signals:
    /**
     * @fn void parametrewindow::modifParams(QStringList params)
     * @brief modifParams est un signal qui est émis lorsque les paramètres ont été modifiés. Il sera capté par la classe MainWindow afin de mettre à jour permet de mettre à jour le contexte de l'application : devise et format de date.
     * @param params : QStringList, QStringList comportant les nouvelles valeurs de la devise et du format de date.
     */
    void modifParams(QStringList params);

  private slots:
    /**
     * @fn void parametrewindow::registerParams()
     * @brief registerParams est appelé lorsque l'utilisateur clique sur le bouton "OK". Il permet d'enregistrer les nouvelles valeurs des paramètres de l'application (devise, format de date)
     */
    void registerParams();

  private :
    /**
     * @var Ui::parametrewindow* parametrewindow::design
     * @brief design représente la fenêtre graphique réalisée sur QTDesigner pour consulter/modifer les paramètres de l'application.
     */
    Ui::parametrewindow *design;
};

#endif // PARAMETREWINDOW_H
