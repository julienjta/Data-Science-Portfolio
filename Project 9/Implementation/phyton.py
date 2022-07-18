#!/usr/bin/python3

import psycopg2 as ps2

HOST = "tuxa.sme.utc"
USER = "me"
PASSWORD = "xxxxx"
DATABASE = "mydb"


# Connect to an existing database
conn = ps2.connect("host=%s dbname=%s user=%s password=%s" % (HOST, DATABASE, USER, PASSWORD))

# Open a cursor to send SQL commands

cur = conn.cursor()

# Initilisation
sql = "DROP TABLE IF EXISTS AdministrateurRubrique;
DROP TABLE IF EXISTS Annonce;
DROP TABLE IF EXISTS Enchere;
DROP TABLE IF EXISTS Message;
DROP TABLE IF EXISTS Rubrique;
DROP TABLE IF EXISTS Administrateur;
DROP TABLE IF EXISTS Utilisateur;
DROP TABLE IF EXISTS Service;
DROP TABLE IF EXISTS Transaction;
DROP TABLE IF EXISTS Bien;
DROP TABLE IF EXISTS Enchere;
DROP TABLE IF EXISTS Encherit;
DROP TABLE IF EXISTS Mot_cle;
DROP TABLE IF EXISTS Message;
DROP TABLE IF EXISTS Vente_Directe

CREATE TABLE Rubrique(
nom varchar primary key
);
Create table Administrateur (
pseudo varchar(30) primary key
);
CREATE TABLE Utilisateur(
pseudo varchar(30) PRIMARY KEY,
nom varchar(30) NOT NULL,
prenom varchar(30) NOT NULL,
date_naissance DATE NOT NULL,
tel  numeric(10,0) UNIQUE,
mail varchar(50) UNIQUE NOT NULL,
ville varchar(30),
code_postal numeric(5,0),
montant_porte_feuille numeric(6,2) check (montant_porte_feuille >= 0)
);
CREATE TABLE Annonce (
id varchar primary key,
date_depot timestamp NOT NULL,
titre varchar(50) NOT NULL,
photo1 varchar,
photo2 varchar,
photo3 varchar,
description varchar(250),
deposeur varchar(30) references Utilisateur(pseudo) NOT NULL,
validation bool NOT NULL,
administrateur varchar(30) references Administrateur(pseudo),
check (case
when validation = 'f' then administrateur is NULL
when validation = 't' then administrateur is NOT NULL
end)
);
CREATE TABLE Service(
id_serv varchar primary key,
prix_heure float,
rubrique varchar,
foreign key(id_serv) references Annonce(id),
foreign key(rubrique) references Rubrique(nom)
);
CREATE TABLE Transaction(
annonce varchar primary key,
date_transaction date,
utilisateur varchar(30),
foreign key(annonce) references Annonce (id),
foreign key(utilisateur) references Utilisateur(pseudo),
note integer,
commentaire varchar,
CHECK ((note IS NULL and commentaire IS NULL) OR (note IS NOT NULL and commentaire IS NOT NULL))
);
CREATE TABLE Bien(
reference varchar primary key,
nom varchar NOT NULL,
etat varchar,
taille varchar,
annee numeric(4,0),
description varchar,
rubrique varchar,
foreign key(rubrique) references Rubrique(nom),
CHECK (etat in ('neuf', 'bon', 'moyen', 'mauvais')),
CHECK (taille in ('petit', 'moyen', 'grand', 'très grand'))
);
CREATE TABLE Enchere(
annonce varchar UNIQUE,
bien varchar UNIQUE,
PRIMARY KEY (annonce,bien),
prix_depart float NOT NULL,
duree_jours integer NOT NULL,
foreign key(annonce) references Annonce(id),
foreign key(bien) references Bien(reference)
);
CREATE TABLE Encherit(
enchere varchar,
encherisseur varchar,
montant float,
date_enchere timestamp,
foreign key(enchere) references Enchere (annonce),
foreign key(encherisseur) references Utilisateur(pseudo)
);
CREATE TABLE Vente_Directe(
annonce varchar,
bien varchar,
prix float NOT NULL,
primary key(annonce, bien),
foreign key(annonce) references Annonce(id),
foreign key(bien) references Bien(reference)
);
Create table Message (
reference varchar primary key,
contenu_message varchar(250),
heure_message timestamp NOT NULL,
statut varchar NOT NULL,
destinateur varchar NOT NULL,
destinataire varchar NOT NULL,
foreign key(destinateur) references Utilisateur(pseudo),
foreign key (destinataire) references Utilisateur(pseudo),
CHECK (statut in ('envoyé', 'reçu', 'lu'))
);
create table Mot_cle(
mot_cle varchar(30),
annonce varchar references Annonce (id),
primary key (mot_cle,annonce)
);"

cur.execute(sql)

# Commit
conn.commit()


# Execute a SQL INSERT command

sql = "INSERT INTO Rubrique(nom) VALUES ('Maison')"

cur.execute(sql)

# Commit (transactionnal mode is by default)

conn.commit()

# Testing

sql = "SELECT * FROM Rubrique"

cur.execute(sql)

print(cur.fetchall())

# Close connection

conn.close()