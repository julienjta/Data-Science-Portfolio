#ifndef DEPENSE_H_INCLUDED
#define DEPENSE_H_INCLUDED

/**
    @file Depense.h
    @brief Depense permet de représenter les comptes de poste Depense
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/Actif.h"

/**
    @class Depense "Depense.h"
    @brief Depense permet de représenter les propriétés des comptes de poste Depense.
*/

class Depense: public PosteAD{
public:
     /**
     @fn virtual Poste Depense::getPoste() const  noexcept override;
     @brief  Redéfinition de la méthode virtuelle getPoste de PosteCompte. Cette méthode retourne le nom du poste Depense: DEPENSE.
     @return DEPENSE
    */
    Poste getPoste() const noexcept override {return DEPENSE;}
     /**
        @fn  virtual string Depense::getLetter() const noexcept override;
        @brief Redéfinition de la méthode virtuelle getLetter de PosteCompte. Cette méthode renvoie la première lettre d'un poste Depense : D.
        @return D
    */
    string getLetter() const noexcept override {return "D";}
    /**
        @fn static const PosteCompte& Depense::getInstance() noexcept;
        @brief Méthode qui permet d'obtenir l'instance Depense.
        @return instance
    */
    static const PosteCompte& getInstance() noexcept {return instance;}
private:
    //attribut
    /**
        @var static Depense::Depense instance
        @brief instance Depense
    */
    static Depense instance;

    //méthodes
    /**
        @fn Depense::Depense();
        @brief Constructeur privé
    */
    Depense() = default;
    /**
        @fn Depense::~Depense();
        @brief Destructeur privé
    */
    ~Depense()=default;
    /**
        @fn  Depense::Depense(const Depense& _d);
        @brief Constructeur par recopie privé.
        @param _d : const Depense&, référence constante sur le poste dépense à recopier.
    */
    Depense(const Depense& _d) = default;

    /**
        @fn  Depense& Depense::operator=(const Depense& _d);
        @brief Surcharge de l'opérateur d'affectation privé.
        @param _d : const Depense&, référence constante sur le poste dépense à affecter.
    */
    Depense& operator=(const Depense& _d) = default;
};
#endif // DEPENSE_H_INCLUDED
