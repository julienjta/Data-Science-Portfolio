--------------------------------------------
----------CREATION OF THE DATABASE----------
--------------------------------------------

CREATE OR REPLACE TYPE TAdresse AS OBJECT (rue varchar(25),
  rue VARCHAR2(20),
  numero number(3),
  ville varchar(25),
  code_postal numeric(5,0)
);
/

CREATE TABLE Adresse OF TAdresse( 
  PRIMARY KEY (rue,numero,ville,code_postal)
); 
/

CREATE TABLE Administrateur (
	pseudo varchar(30) PRIMARY KEY
);
/

CREATE TABLE Utilisateur(
  pseudo varchar(30) PRIMARY KEY,
  nom varchar(30) NOT NULL,
  prenom varchar(30) NOT NULL,
  date_naissance DATE NOT NULL,
  tel  numeric(10,0) UNIQUE,
  mail varchar(50) UNIQUE NOT NULL,
  adresse REF TAdresse,
  montant_porte_feuille numeric(6,2) CHECK (montant_porte_feuille >= 0)
); 
/

CREATE TABLE Rubrique(
  nom varchar PRIMARY KEY
);
/

CREATE TABLE Annonce (
  id varchar PRIMARY KEY,
  date_depot timestamp NOT NULL,
  titre varchar(50) NOT NULL,
  photo1 varchar,
  photo2 varchar,
  photo3 varchar,
  description varchar(250),
  deposeur varchar(30) REFERENCES Utilisateur(pseudo) NOT NULL,
  validation bool NOT NULL,
  administrateur varchar(30) REFERENCES Administrateur(pseudo),
  CHECK (CASE
        	WHEN validation = 'f' THEN administrateur is NULL
        	WHEN validation = 't' THEN administrateur IS NOT NULL
        END)
);
/

CREATE TABLE Service(
  id_serv varchar PRIMARY KEY,
  prix_heure float,
  rubrique varchar,
  FOREIGN KEY(id_serv) REFERENCES Annonce(id),
  FOREIGN KEY(rubrique) REFERENCES Rubrique(nom)
); 
/

CREATE TABLE Transaction(
	annonce varchar PRIMARY KEY,
  date_transaction date,
  utilisateur varchar(30),
  FOREIGN KEY(annonce) REFERENCES Annonce (id),
  FOREIGN KEY(utilisateur) REFERENCES Utilisateur(pseudo),
  note integer,
  commentaire varchar,
  CHECK ((note IS NULL AND commentaire IS NULL) OR (note IS NOT NULL AND commentaire IS NOT NULL))
);
/

CREATE TABLE Bien(
	reference varchar PRIMARY KEY,
  nom varchar NOT NULL,
  etat varchar,
  taille varchar,
  annee numeric(4,0),
  description varchar,
  rubrique varchar,
  FOREIGN KEY(rubrique) REFERENCES Rubrique(nom),
	CHECK (etat IN ('neuf', 'bon', 'moyen', 'mauvais')),
  CHECK (taille IN ('petit', 'moyen', 'grand', 'très grand'))
);
/

CREATE TABLE Enchere(
  annonce varchar UNIQUE,
  bien varchar UNIQUE,
  PRIMARY KEY (annonce,bien),
  prix_depart float NOT NULL,
  duree_jours integer NOT NULL,
	FOREIGN KEY(annonce) REFERENCES Annonce(id),
  FOREIGN KEY(bien) REFERENCES Bien(reference)
);
/

CREATE TABLE Encherit(
  enchere varchar,
  encherisseur varchar,
  montant float,
  date_enchere timestamp,
	FOREIGN KEY(enchere) REFERENCES Enchere (annonce),
  FOREIGN KEY(encherisseur) REFERENCES Utilisateur(pseudo)
);
/

CREATE TABLE Vente_Directe(
	annonce varchar,
  bien varchar,
  prix float NOT NULL,
  PRIMARY KEY(annonce, bien),
  FOREIGN KEY(annonce) REFERENCES Annonce(id),
  FOREIGN KEY(bien) REFERENCES Bien(reference)
);
/

CREATE TABLE Message (
reference varchar PRIMARY KEY,
contenu_message varchar(250),
heure_message timestamp NOT NULL,
statut varchar NOT NULL,
destinateur varchar NOT NULL,
destinataire varchar NOT NULL,
FOREIGN KEY(destinateur) REFERENCES Utilisateur(pseudo),
FOREIGN KEY(destinataire) REFERENCES Utilisateur(pseudo),
CHECK (statut IN ('envoyé', 'reçu', 'lu'))
);
/


CREATE TABLE Mot_cle(
	mot_cle varchar(30),
  annonce varchar REFERENCES Annonce (id),
  PRIMARY KEY (mot_cle,annonce) 
);
/
