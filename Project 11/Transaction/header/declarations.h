#ifndef DECLARATIONS_H_INCLUDED
#define DECLARATIONS_H_INCLUDED

/**
    @file declarations.h
    @brief Sommaire des déclarations des classes et des en-têtes pour la partie noyau
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucun
*/

#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <memory>
#include <time.h>
#include <ctime>
#include <sstream> //std::stringstream

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QtXml/qxml.h>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QTextCodec>

#include <QtWidgets>

using namespace std;

namespace tool{
    /**
        @fn template<typename T> string tool::NumberToString(const T _i)
        @brief convertir un nombre quelconque en string
    */
    template<typename T> string NumberToString(const T _i){
        if(   typeid(T) == typeid(const int)
           || typeid(T) == typeid(const double)
           || typeid(T) == typeid(const float)
           || typeid(T) == typeid(const unsigned)
           || typeid(T) == typeid(const time_t)
        ){
            std::stringstream s;
            s << _i;
            return s.str();
        }
        return "";
    }

    bool double_equal(const double _a, const double _b);
}

class Exception;
class ExceptionComptabilite;
class ExceptionHierarchie;
class ExceptionFichier;
class ExceptionTransaction;
class Memento;
class Originator;
class PosteCompte;
class Racine;
class PosteAD;
class PostePR;
class Passif;
class Actif;
class Depense;
class Recette;
class CompteHierarchie;
class Visiteur;
class VisiteurFree;
class VisiteurGetSolde;
class VisiteurAffichage;
class VisiteurPere;
class VisiteurPoste;
class VisiteurRecherche;
class CompteVirtuel;
class CompteReel;
class Operation;
class Transaction;
class TransactionBuilder;
class HierarchieBuilder;
class TransactionManager;
class CompteManager;

#endif // DECLARATIONS_H_INCLUDED
