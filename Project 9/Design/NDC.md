**PLATEFORME D’ECHANGE A L’UTC**


L'objectif de notre projet est de réaliser une plateforme d'échange à l'UTC.
*  Le projet intégrera des biens et des services.
*  Le projet intégrera des actions de dons, d'échanges ou de ventes ainsi qu'une gestion d'une monnaie interne sans entrer dans le détail d'une devise.
*  Les utilisateurs pourront déposer des offres ou des demandes.
*  Les annonces pourront être classées selon des rubriques mais également des mots clés.
*  Nous irons également ajouter des mécanismes d'enchère et de négociation par messagerie interposée entre les utilisateurs.



Une annonce sera donc composée de :

    • Id : String en UNIQUE
    • Date Dépôt : timestamp
    • Titre : String en NOT NULL
    • Photo[0..3]: Fichier
    • Description : String
    • status valider : boolean

De ce fait un utilisateur sera représenté de cette façon:

    • Pseudo : String en UNIQUE
    • Nom : String en NOT NULL
    • Prénom : String en NOT NULL
    • Date_Naissance : Date en NOT NULL
    • Tel : Integer en UNIQUE
    • Mail : String en UNIQUE NOT NULL
    • Note_moyenne : float
    • Ville : String
    • code postal : Integer
    • status valider : boolean
    
Comme on ne gère pas de livraisons, connaître la ville seule est suffisant.

Caractéristique d'un bien ou objet :

    • Référence : Integer en UNIQUE
    • Nom : String
    • Etat : {neuf, bon, moyen, mauvais}
    • Taille : {petit, moyen, grand, très grand}
    • Année : numeric(4,0)
    • Description : String
 
 Une annonce peut concerner une vente (avec un prix), un service (avec un prix à l'heure) ou une enchère.
 
 Un enchère est composée de :

    • Prix_départ : Float
    • Durée : Integer (en jours)
    * Date_Fin : Fonction (Date_Depot + Durée)
    * Prix_actuel
    
Une vente est composée uniquement des attribut de l'annonce.
Un service, en plus des attributs de l'annonce est décrite par un type de service.

Une rubrique sera un moyen de classifier les annonces et ainsi pouvoir les rechercher :

    • Nom : String en UNIQUE NOT NULL

Une système de messagerie pourra être utilisé afin de faciliter les échanges entre les utilisateurs :

    • Référence du message : Integer en UNIQUE
    • Contenu du message : String
    * Date et heure de l'envoi : timestamp
    * Statut : {envoyé, reçu, lu}


Une évaluation pourra être émise au moment d'une transaction entre un utilisateur et une annonce:

    • Note : 0..5
    • Commentaire : String

Une Transaction aura :

    • Un Identifiant : String en UNIQUE
    • Une Date : date
    • Une Description : String

Il y aura aussi une gestion d'un Porte_Feuille avec :

    • Montant : Integer
    * Un approvisionnement
    * Une récupération

Un Administrateur peut également valider ou supprimer une annonce ou un utilisateur, il aura un Pseudo en String et en UNIQUE (/!\ Il ne sera pas un utilisateur).

Des Mot_Cles seront ajouter afin de réaliser des recherches sur les annonces.