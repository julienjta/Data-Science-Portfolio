/**
    @file parametrewindow.cpp
    @brief définition des fonctions membres de la classe parametrewindow.
    @author Axel Huillard
    @version v3
    @date 10 juin 2020
    @bug aucun détecté
    @warning compile
    @note Aucune
*/
#include "parametrewindow.h"
#include "ui_parametrewindow.h"
#include "mainwindow.h"


parametrewindow::parametrewindow(MainWindow *parent) :
  QDialog(parent),
  design(new Ui::parametrewindow)
{
  design->setupUi(this);

  design->choixDeviseComboBox->setCurrentText(parent->getDevise());
  design->choixFormatDateComboBox->setCurrentText(parent->getFormatDate());

  connect(design->buttonBox,SIGNAL(accepted()),this,SLOT(registerParams()));
  connect(design->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

void parametrewindow::registerParams()
{
    QStringList params;
    params.push_back(design->choixDeviseComboBox->currentText());
    params.push_back(design->choixFormatDateComboBox->currentText());

    emit modifParams(params);
    accept();
}

parametrewindow::~parametrewindow()
{
    delete design;
}
