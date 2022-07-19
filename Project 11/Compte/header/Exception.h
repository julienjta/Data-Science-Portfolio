#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

/**
    @file Exception.h
    @brief Classe mère de toutes les exceptions.
    @author Ophélie Delattre / Simon Lepage / Jérémy Godde
    @version v4
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
*/

#include "../../Transaction/header/declarations.h"

/**
    @class Exception "Exception.h"
    @brief Exception permet de gérer une erreur ainsi que son message.
*/
class Exception{
    //attribut
    /**
        @var string message
        @brief Explication des raisons de la création de l'exception.
    */
    string message;
    /**
        @var int code_erreur
        @brief Code permettant l'identification de l'erreur en vue de son traitement.
    */
    int code_erreur;

public:
    /**
        @fn const string& Exception::getMessage() const noexcept;
        @brief Méthode qui permet d'obtenir le message d'erreur.
        @return Le message d'erreur.
    */
    const string& getMessage() const noexcept {return message;}
    /**
        @fn const string& Exception::getCode() const noexcept;
        @brief Méthode qui permet d'obtenir le code d'erreur en vue de son traitement.
        @return Le code d'erreur.
    */
    int getCode() const noexcept {return code_erreur;}
protected:
    /**
        @fn Exception::Exception(string _s, int _code_erreur) noexcept;
        @brief Constructeur.
    */
    Exception(string _s, int _code_erreur) noexcept : message(_s),code_erreur(_code_erreur){}
};


#endif // EXCEPTION_H_INCLUDED
