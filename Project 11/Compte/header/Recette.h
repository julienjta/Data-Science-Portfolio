#ifndef RECETTE_H_INCLUDED
#define RECETTE_H_INCLUDED

/**
    @file Recette.h
    @brief Recette permet de représenter le comportement des comptes de de poste Recette.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/Depense.h"

/**
    @class Recette "Recette.h"
    @brief Recette permet de représenter le comportement des comptes de poste Recette.
*/

class Recette: public PostePR{
public:
     /**
     @fn virtual Poste Recette::getPoste() const noexcept override;
     @brief  Redéfinition de la méthode virtuelle getPoste de PosteCompte. Cette méthode retourne le nom du poste Recette: RECETTE.
     @return RECETTE
    */
    Poste getPoste() const noexcept override {return RECETTE;}
     /**
        @fn  virtual string Recette::getLetter() const noexcept override;
        @brief Redéfinition de la méthode virtuelle getLetter de PosteCompte. Cette méthode renvoie la première lettre du nom d'un poste Recette : R.
        @return R
    */
    string getLetter() const noexcept override {return "R";}
    /**
        @fn static const PosteCompte& Recette::getInstance() noexcept;
        @brief Méthode qui permet d'obtenir l'instance Recette.
        @return instance
    */
    static const PosteCompte& getInstance() noexcept {return instance;}
private:
    //attribut
    /**
        @var static Recette::Recette instance
        @brief instance Recette
    */
    //méthodes
    static Recette instance;
    /**
        @fn Recette::Recette();
        @brief Constructeur privé
    */
    Recette() = default;
    /**
        @fn Recette::~Recette();
        @brief Destructeur privé
    */
    ~Recette()=default;
    /**
        @fn  Recette::Recette(const Recette& _r);
        @brief Constructeur par recopie privé
        @param _r : const Recette&, référence constante sur le poste recette à recopier.
    */
    Recette (const Recette& _r) = default;

    /**
        @fn  Recette& Recette::operator=(const Recette& _r);
        @brief Surcharge de l'opérateur d'affectation privé
        @param _r : const Recette&, référence constante sur le poste recette à affecter.
    */
    Recette& operator=(const Recette& _r) = default;

};

#endif // RECETTE_H_INCLUDED
