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
);


-----REMPLISSAGE DE LA BASE-----


INSERT INTO Rubrique(nom) VALUES ('Maison');
INSERT INTO Rubrique(nom) VALUES ('Jardin');
INSERT INTO Rubrique(nom) VALUES ('Cuisine');
INSERT INTO Rubrique(nom) VALUES ('Informatique');
INSERT INTO Rubrique(nom) VALUES ('Téléphonie');
INSERT INTO Rubrique(nom) VALUES ('Electroménager');
INSERT INTO Rubrique(nom) VALUES ('Auto & Moto');
INSERT INTO Rubrique(nom) VALUES ('Jeux & Culture');
INSERT INTO Rubrique(nom) VALUES ('Sport');
INSERT INTO Rubrique(nom) VALUES ('Bricolage');
INSERT INTO Rubrique(nom) VALUES ('Mode');
INSERT INTO Rubrique(nom) VALUES ('Education');

INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('juju', 'Justine', 'Tigoutte', to_date('20001225', 'YYYYMMDD'), 0612345678, 'Justine.Tigoutte@hotmail.fr', 'Compiègne', 60200, 50.50);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('yvon', 'Yves', 'Egée',to_date('19570401','YYYYMMDD'), 0612345680, 'Yves.Egée@hotmail.com', 'Paris', 75001, 0.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('kim', 'Kimberley', 'Tartine',to_date('19801021','YYYYMMDD'), 0600000102, 'Kimberley.tartine@hotmail.com', 'Paris', 75018, 1000.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('Purporc', 'Sophie', 'Sonsek',to_date('20050506','YYYYMMDD'), NULL, 'Justin.bridon@gmail.com', 'Compiègne', 60200, 123.45);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('Outch', 'Oussama', 'Faitmal',to_date('20010911','YYYYMMDD'), 0701020304, 'Oussama.Faitmal@gmail.com', 'Marseille', 13000, 12.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('toutouille', 'Sacha', 'Touille',to_date('19450508','YYYYMMDD'), 0743215678, 'Sacha.Touille@gmail.com', 'Compiègne', 60200, 0.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('gentleman', 'Arsene', 'Lupin',to_date('18740101','YYYYMMDD'), NULL, 'Arsene.Lupin@hotmail.fr', 'Paris', 75010, 9999.99);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('jujubis', 'Justine', 'Tigoutte',to_date('20001225','YYYYMMDD'), 0612345679, 'Justinebis.Tigoutte@hotmail.fr', 'Compiègne', 60200, 50.50);

INSERT INTO Message VALUES ('mss1', 'salut','2018-10-25 14:15:21', 'envoyé', 'jujubis','gentleman');
INSERT INTO Message VALUES ('mss2', 'J''aime le piment d''Espelette', '2018-10-25 14:15:41', 'lu', 'kim','Outch');
INSERT INTO Message VALUES ('mss3', 'eh coucou','2018-09-15 13:10:40', 'envoyé', 'toutouille','gentleman');
INSERT INTO Message VALUES ('mss4', 'Toujours à vendre ?', '2018-09-20 11:25:47', 'lu', 'Purporc','yvon');

INSERT INTO Administrateur VALUES('admin1');
INSERT INTO Administrateur VALUES('admin2');
INSERT INTO Administrateur VALUES('admin3');
INSERT INTO Administrateur VALUES('admin4');
INSERT INTO Administrateur VALUES('admin5');

INSERT INTO Annonce VALUES ('AZLD738920', '20191012 163455', 'Telephone de OUF', NULL, NULL, NULL, 'Bonjour, je vous propose un téléphone exceptionnel à 1500.', 'juju','1','admin1');
INSERT INTO Annonce VALUES('ZAZEQSDWXC1423', '20191013 163502','CarWash', 'webphoto1','webphoto2','webphoto3','pour laver vos fringues','juju','1','admin1');
INSERT INTO Annonce VALUES('JFEZOF', '20191201 120505', 'Cours d''histoire', NULL, NULL, NULL, 'venez apprendre','Outch','1','admin1');
INSERT INTO Annonce VALUES('JFUJR7485OE','20191201 120507', 'Play the game', 'photodessus','photosurcôté','photosouscôtée',NULL, 'toutouille', '0');
INSERT INTO Annonce VALUES('HEG', '20191201 120510', 'cours de maths', NULL, NULL, NULL, 'l''axiome du choix met ce cours dans ton panier', 'jujubis', '1', 'admin2');

INSERT INTO Service VALUES('JFEZOF', 42, 'Education');
INSERT INTO Service VALUES('HEG', 73, 'Education');

INSERT INTO Bien
VALUES ('MPLOIJH', 'Machine à laver', 'neuf', 'très grand', 2019, 'Machine à lavé pour laver tout ce qui passe dedans', 'Electroménager');
INSERT INTO Bien
VALUES ('AZLD738946', 'Telephone', 'bon', 'petit', 2018, 'Nokia 3310', 'Téléphonie');
INSERT INTO Bien
VALUES ('JFUJR7485OD', 'PS4', 'moyen', 'moyen', 2018, 'PS4 en état moyen mais peu utilisé', 'Jeux & Culture');
INSERT INTO Bien
VALUES ('cabanedujardin', 'Jardin', 'bon', 'très grand', 2015, 'Cabane de jardin en paille', 'Jeux & Culture');

INSERT INTO Enchere VALUES('JFUJR7485OE','JFUJR7485OD',32,4);
INSERT INTO Encherit VALUES('JFUJR7485OE','juju',1);
INSERT INTO Encherit VALUES('JFUJR7485OE','juju',50,'2018-10-25 14:15:21');

INSERT INTO Vente_Directe(annonce, bien, prix)
VALUES ('AZLD738920', 'AZLD738946', 1500);
INSERT INTO Vente_Directe(annonce, bien, prix)
VALUES ('ZAZEQSDWXC1423', 'MPLOIJH', 350);

INSERT INTO Mot_cle VALUES('ps4','JFUJR7485OE');
INSERT INTO Mot_cle VALUES('telephone','AZLD738920');
INSERT INTO Mot_cle VALUES('iphone','AZLD738920');
INSERT INTO Mot_cle VALUES('histoire','JFEZOF');

INSERT INTO Transaction VALUES('JFUJR7485OE', '20221002','jujubis',4,'cool');
INSERT INTO Transaction VALUES('JFEZOF', '20191015','gentleman',3,'bof');

