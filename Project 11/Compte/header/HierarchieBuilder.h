#ifndef HIERARCHIEBUILDER_H_INCLUDED
#define HIERARCHIEBUILDER_H_INCLUDED

/**
    @file HierarchieBuilder.h
    @brief HierarchieBuilder gère la création de la hiérarchie des comptes
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../../Transaction/header/transactionbuilder.h"

/**
    @class HierarchieBuilder "HierarchieBuilder.h"
    @brief HierarchieBuilder gère la création de la hiérarchie des comptes
*/

class HierarchieBuilder{
    friend class CompteManager;
    friend class ajouterwindow;
    friend class cloture;
    /**
        @fn static HierarchieBuilder::creerEmpty() noexcept;
        @brief Méthode qui permet d'initialiser une hiérarchie de comptes vide : crée le compte racine.
        @return Un pointeur vers l'élément racine d'une hiérarchie vide.
    */
    static CompteHierarchie* creerEmpty() noexcept;

    /**
        @fn  static CompteHierarchie* HierarchieBuilder::creerFils(string _nom, Type _t, Poste _p);
        @brief Méthode qui permet de créer un nouveau compte.
        @param _nom : string, nom du nouveau compte
        @param _t : Type, Type du nouveau compte : VIRTUEL ou REEL
        @param _p : Poste, Poste du nouveau compte : DEPENSE ou RECETTE ou ACTIF ou PASSIF
        @exception TYPE_EXC_H Type de compte inconnu
        @exception POSTE_EXC_H Type de poste inconnu
        @return Un pointeur vers un nouvel élément CompteHierarchie.
    */
    static CompteHierarchie* creerFils(string _nom, Type _t, Poste _p);

    /**
        @fn static CompteHierarchie* creerAvecFichier(string _path);
        @brief Méthode qui permet de créer une hiérarchie à partir d'un fichier.
        @param _path : string, chemin vers le fichier à utiliser.
        @exception non implémenté
        @return Un pointeur vers l'élément racine de la hiérarchie construite.
    */
    static CompteHierarchie* creerAvecFichier(string _path);
//attribut
    /**
        @var static int HierarchierBuilder::idcompte
        @brief Attribut qui permet de gérer automatiquement les id des comptes
    */
    static int idcompte;


};




#endif // HIERARCHIEBUILDER_H_INCLUDED
