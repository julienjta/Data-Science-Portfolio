#-------------------------------------------------
#
# Project created by QtCreator 2020-05-09T21:19:23
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT_XCB_NATIVE_PAINTING = 1

TARGET = test_interface
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        ajoutertransactionwindows.cpp \
        ajouterwindow.cpp \
    cloture.cpp \
    deplacercompte.cpp \
        main.cpp \
        mainwindow.cpp \
    chargementwindow.cpp \
    parametrewindow.cpp \
    savewindow.cpp \
    ../Compte/source/Actif.cpp \
    ../Compte/source/CompteHierarchie.cpp \
    ../Compte/source/CompteManager.cpp \
    ../Compte/source/CompteReel.cpp \
    ../Compte/source/CompteVirtuel.cpp \
    ../Compte/source/Depense.cpp \
    ../Compte/source/HierarchieBuilder.cpp \
    ../Compte/source/Memento.cpp \
    ../Compte/source/Passif.cpp \
    ../Compte/source/Racine.cpp \
    ../Compte/source/Recette.cpp \
    ../Compte/source/VisiteurAffichage.cpp \
    ../Compte/source/VisiteurFree.cpp \
    ../Compte/source/VisiteurGetSolde.cpp \
    ../Compte/source/VisiteurPere.cpp \
    ../Compte/source/VisiteurPoste.cpp \
    ../Compte/source/VisiteurRecherche.cpp \
    ../Transaction/source/operation.cpp \
    ../Transaction/source/transaction.cpp \
    ../Transaction/source/transactionbuilder.cpp \
    ../Transaction/source/transactionmanager.cpp \
    ../Transaction/source/declarations.cpp \
    bilan.cpp \
    rapprochement.cpp \
    releve.cpp \
    resultat.cpp \
    modifiertransaction.cpp \
    ../Compte/source/visiteurlistecompte.cpp

HEADERS += \
        ajoutertransactionwindows.h \
        ajouterwindow.h \
    cloture.h \
    deplacercompte.h \
        mainwindow.h \
    chargementwindow.h \
    parametrewindow.h \
    savewindow.h \
    ../Compte/header/Actif.h \
    ../Compte/header/CompteHierarchie.h \
    ../Compte/header/CompteManager.h \
    ../Compte/header/CompteReel.h \
    ../Compte/header/CompteVirtuel.h \
    ../Compte/header/Depense.h \
    ../Compte/header/Exception.h \
    ../Compte/header/ExceptionCompte.h \
    ../Compte/header/HierarchieBuilder.h \
    ../Compte/header/Memento.h \
    ../Compte/header/Originator.h \
    ../Compte/header/Passif.h \
    ../Compte/header/PosteAD.h \
    ../Compte/header/PosteCompte.h \
    ../Compte/header/PostePR.h \
    ../Compte/header/Racine.h \
    ../Compte/header/Recette.h \
    ../Compte/header/Visiteur.h \
    ../Compte/header/VisiteurAffichage.h \
    ../Compte/header/VisiteurFree.h \
    ../Compte/header/VisiteurGetSolde.h \
    ../Compte/header/VisiteurPere.h \
    ../Compte/header/VisiteurPoste.h \
    ../Compte/header/VisiteurRecherche.h \
    ../Transaction/header/declarations.h \
    ../Transaction/header/exceptiontransaction.h \
    ../Transaction/header/operation.h \
    ../Transaction/header/transaction.h \
    ../Transaction/header/transactionbuilder.h \
    ../Transaction/header/transactionmanager.h \
    bilan.h \
    rapprochement.h \
    releve.h \
    resultat.h \
    modifiertransaction.h \
    ../Compte/header/visiteurlistecompte.h

FORMS += \
        ajoutertransactionwindows.ui \
        ajouterwindow.ui \
    cloture.ui \
    deplacercompte.ui \
        mainwindow.ui \
    chargementwindow.ui \
    parametrewindow.ui \
    savewindow.ui \
    bilan.ui \
    rapprochement.ui \
    releve.ui \
    resultat.ui \
    modifiertransaction.ui

RESOURCES += ressources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    ressources.qrc
