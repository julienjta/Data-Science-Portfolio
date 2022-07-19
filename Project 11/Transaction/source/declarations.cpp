/**
    @file declarations.cpp
    @brief Définition des fonctions membres de la classe declarations.
    @author Jérémy Godde
    @version v2
    @date 2 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucun
*/
#include "../header/declarations.h"


bool tool::double_equal(const double _a, const double _b){
    double _c = (_a<_b) ? _a : _b;
    double _d = (_a<_b) ? _b : _a;

    return (_d*100. - _c*100.) < 0.1;
}
