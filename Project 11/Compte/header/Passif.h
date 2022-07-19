#ifndef PASSIF_H_INCLUDED
#define PASSIF_H_INCLUDED

/**
    @file Passif.h
    @brief Passif permet de représenter les comptes de poste Passif
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/PostePR.h"

/**
    @class Passif "Passif.h"
    @brief Passif permet de représenter les propriétés des comptes de poste Passif.
*/

class Passif: public PostePR{
public:
     /**
     @fn virtual Poste Passif::getPoste() const noexcept  override;
     @brief  Redéfinition de la méthode virtuelle getPoste de PosteCompte. Cette méthode retourne le nom du poste passif : PASSIF.
     @return PASSIF
    */
    Poste getPoste() const noexcept override {return PASSIF;}
     /**
        @fn  virtual string Passif::getLetter() const noexcept override;
        @brief Redéfinition de la méthode virtuelle getLetter de PosteCompte. Cette méthode renvoie la première lettre de le nom d'un poste passif : P.
        @return P
    */
    string getLetter() const noexcept override {return "P";}
    /**
        @fn static Passif& Passif::getInstance() noexcept;
        @brief Méthode qui permet d'obtenir l'instance Passif.
        @return instance
    */
    static const PosteCompte& getInstance() noexcept {return instance;}
private:
    //attribut
    /**
        @var static Passif::Passif instance
        @brief instance Passif
    */
    //méthodes
    static Passif instance;
    /**
        @fn Passif::Passif();
        @brief Constructeur privé
    */
    Passif() = default;
    /**
        @fn Passif::~Passif();
        @brief Destructeur privé
    */
    ~Passif()=default;
    /**
        @fn  Passif::Passif (const Passif& _p);
        @brief Constructeur par recopie privé
        @param _p : const Passif&, référence constante sur le poste passif à recopier.
    */
    Passif (const Passif& _p) = default;

    /**
        @fn  const PosteCompte& Passif::operator=(const Passif& _p);
        @brief Surcharge de l'opérateur d'affectation privé
        @param _p : const Passif&, référence constante sur le poste passif à affecter.
    */
    Passif& operator=(const Passif& _p) = default;
};

#endif // PASSIF_H_INCLUDED
