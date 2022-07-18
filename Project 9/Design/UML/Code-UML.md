@startuml

title Le BON UT

class Utilisateur {
    pseudo : string UNIQUE
    nom : string
    prénom : string
    date_naissance : date
    {field}tel : numeric(10,0)
    mail : string UNIQUE
    statut_validé : boolean
    Moyenne_note() : float
}
class Utilisateur
note right #yellow
Moyenne_note = Somme des notes / Nombre de notes
end note

class Adresse{
    ville : string
    {field}code_postal : numeric(5,0)
}

class Transaction{
    identifiant : string UNIQUE
    date : date
    commentaire : string
    montant_vente : float
    montant_enchere : float
    montant_service()
}

class Transaction
note right #yellow
montant_service = Service->prix_heure * nombre heure
end note

class Annonce {
    id : string UNIQUE
    date_dépôt : timestamp
    titre : string
    photos[0..3] : fichiers
    description : string
    statut_validé : boolean
}

class Bien {
    reference : integer UNIQUE
    nom : string
    état : {neuf,bon,moyen,mauvais}
    {field}année : numeric(4,0)
    Taille : {petit,moyen,grand,tres grand}
    description : string
}

class Rubrique{
    nom : string UNIQUE
}

class Vente_Directe{
    {field}prix : float(.2)
}

class Enchere {
    prix_départ : float
    durée : integer "en jours"
    prix_actuel()
    date_fin()
}

class Enchere
note right #yellow
prix_actuel = prix_depart+montant
date_fin = date-depot+duree
end note

class Messagerie {
    référence : integer UNIQUE
    contenu_message : string
    heure_message : timestamp
    Statut:{envoyé, reçu, lu}
}

class Evaluation{
    Note : 0..5 
    Commentaire : string
}

class Porte_Feuille{
    montant : integer  
    Approvisionnement()
    Recuperation()
}

class Encherit{
    montant : integer
}

class Service{
    {field}prix_heure : float(.2)
}

class Administrateur{
    pseudo : string UNIQUE
    validation_Annonce()
    validation_Utilisateur()
    suppression_Annonce()
    suppression_Utilisateur()
}

class Mot_cles{
    mot : string UNIQUE
}

class Représenter{
  mot-cle : string references Mot_cles (mot)
  annonce : string references Annonce (id)
}


Annonce "*" -right- "1" Administrateur : Valider
Administrateur "1" -- "*" Utilisateur : Administrer
Mot_cles "*" -- "*" Annonce 
(Mot_cles,Annonce) .. Représenter

Annonce <|-- Vente_Directe
Annonce <|-- Enchere
Annonce <|-left-  Service

Utilisateur "1" -- "1" Porte_Feuille : Possède >
Utilisateur "*" -- "1" Adresse : Habite >
Utilisateur "1" -left- "*" Messagerie : Envoie >
Utilisateur "1" -left- "*" Messagerie : Reçoit >
Utilisateur "1" -- "*" Annonce : Dépose >
Utilisateur "1" -- "*" Annonce : Répond >
(Utilisateur, Annonce) .. Transaction
Evaluation "0..1" -- "1" Transaction : Concerner
Utilisateur "1" -- "1" Enchere
(Utilisateur,Enchere) .. Encherit
Service "*" -left- "1" Rubrique
Bien "*" -up- "1" Rubrique : Concerne <
Bien "*" -- "1" Vente_Directe : Concerne <
Bien "*" -- "1" Enchere : Concerne <
@enduml