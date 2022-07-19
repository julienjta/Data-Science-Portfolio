# Doxygen

Il s'agit de commentaires de documentation permettant de génération facilement une documentation pdf et/ou html. Ces commentaires s'écrivent :

```C++
//! sur une ligne pour documenter ce qui suit

/*!
  sur plusieurs lignes pour documenter ce qui suit
*/

/**
  sur plusieurs lignes pour documenter ce qui suit
*/

//!< sur une ligne pour documenter ce qui precede

/*!<
  sur plusieurs lignes pour documenter ce qui precede
*/

/**<
  sur plusieurs lignes pour documenter ce qui precede
*/

```

## Balises

Dans un commentaire de documention, les balises commencent toutes par `@` ou `\`.

### Balises d'en-tête de document

- `@file nom.extension` indique le début du fichier nom.extension
- `@details blablabla` décrit du fichier
- `@author Jean` indique que l'auteur du fichier est Jean
- `@version v1.0` indique la version du fichier
- `@date 25-04-2020` indique la version du fichier
- `@bug aucun` indique un bug encore non-corrigé
- `@warning aucun` indique un comportement utilisateur à risque (par exemple si les input ne sont pas vérifier avant d'être utilisées)
- `@copyright nom du copyright` indique le copyright utilisé (je pense qu'on en aura pas besoin ici)
- `@note blabla` laisse une note aux autres développeurs 

### Balises de classes ou d'espace de nom

- `@class MaClasse ma_classe.h "mes_header/ma_classe.h"` indique le nom, le fichier et l'adresse de la classe depuis la racine du projet
- `@namespace MonEspace mon_espace.h "mes_header/mon_espace.h"` indique le nom, le fichier et l'adresse de l'espace de nom depuis la racine du projet
- `@brief resume` description résumée de la classe
- `autres informations` informations pertinentes concernant la classe

### Balises de méthodes ou d'attributs

- `@fn bool MaClasse::isBissextile(unsigned int _a)` indique le prototype complet de la fonction
- `@var domaine MaClasse::attribut` indique un attribut de la classe
- `@brief verifie si une annee est bissextile` résumé du comportement de la fonction
- `@param _a est une annee` décrit un paramètre (une balise est nécessaire pour chaque paramètre)
- `@exception blablabla` décrit une exception pouvant être lancée depuis la fonction
- `@return Un booleen vrai si l'annee est bissextile, faux sinon` décrit la valeur de retour de la fonction (pour les constructeurs, destructeurs, et fonction void non nécessaire)

### Balises d'énumération

Pour l'énumération

- `@enum MaClasse::MonEnum` indique le nom de l'énumération
- `@brief blablabla` description de l'énumération

Puis pour chaque variable

- `@brief blablabla` description de la variable
