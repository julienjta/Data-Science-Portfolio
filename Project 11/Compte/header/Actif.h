#ifndef ACTIF_H_INCLUDED
#define ACTIF_H_INCLUDED

/**
    @file Actif.h
    @brief Actif permet de représenter les comptes de poste Actif
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning compile
    @note
*/

#include "../header/Passif.h"

/**
    @class Actif "Actif.h"
    @brief Actif permet de représenter les propriétés des comptes de poste Actif.
    @see PosteAD
    @see PosteCompte
*/

class Actif: public PosteAD{
public:
     /**
     @fn virtual Poste Actif::getPoste() const noexcept override;
     @brief Redéfinition de la méthode virtuelle getPoste de PosteCompte. Cette méthode retourne le nom du poste actif : ACTIF.
     @return ACTIF
    */
    Poste getPoste() const noexcept override {return ACTIF;}
     /**
        @fn virtual string Actif::getLetter() const noexcept override;
        @brief Redéfinition de la méthode virtuelle getLetter de PosteCompte. Cette méthode renvoie la premiére lettre du nom d'un poste actif : A.
        @return A
    */
    string getLetter() const noexcept override {return "A";}
    /**
        @fn static const PosteCompte& Actif::getInstance() noexcept;
        @brief Méthode qui permet d'obtenir l'instance Actif.
        @return instance
    */
    static const PosteCompte& getInstance() noexcept {return instance;}
private:
    //attribut
    /**
        @var static Actif::Actif instance
        @brief instance Actif
    */
    static Actif instance;

    //méthodes
    /**
        @fn Actif::Actif();
        @brief Constructeur privé.
    */
    Actif() = default;
    /**
        @fn Actif::~Actif();
        @brief Destructeur privé.
    */
    ~Actif() = default;
    /**
        @fn  Actif::Actif (const Actif& _a);
        @brief Constructeur par recopie privé.
        @param _a : const Actif&, référence constante sur le poste actif à recopier.
    */
    Actif (const Actif& _a) = default;

    /**
        @fn  Actif& Actif::operator=(const Actif& _a);
        @brief Surcharge de l'opérateur d'affectation privé.
        @param _a : const Actif&, référence constante sur le poste actif à affecter.
    */
    Actif& operator=(const Actif& _a) = default;

};

#endif // ACTIF_H_INCLUDED
