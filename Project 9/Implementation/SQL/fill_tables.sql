---------------------------------------
-------------DATABASE FILL-------------
---------------------------------------


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
VALUES ('juju', 'Justine', 'Tigoutte', to_date('20001225', 'YYYYMMDD'), 0612345678, 'Justine.Tigoutte@hotmail.fr', typAdresse('Rue de Paris','754','Compiegne','60200'), 50.50);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('yvon', 'Yves', 'Egée',to_date('19570401','YYYYMMDD'), 0612345680, 'Yves.Egée@hotmail.com', typAdresse('Rue de Bouvines','17','Compiegne','60200'), 0.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('kim', 'Kimberley', 'Tartine',to_date('19801021','YYYYMMDD'), 0600000102, 'Kimberley.tartine@hotmail.com', typAdresse('Boulevard Magenta','28','Paris','75001'), 1000.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('Purporc', 'Sophie', 'Sonsek',to_date('20050506','YYYYMMDD'), NULL, 'Justin.bridon@gmail.com', typAdresse('Avenue des Champs Elysée','12','Paris','75005'), 123.45);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('Outch', 'Oussama', 'Faitmal',to_date('20010911','YYYYMMDD'), 0701020304, 'Oussama.Faitmal@gmail.com', typAdresse('Rue Monceau','349','Marseille','13000'), 12.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('toutouille', 'Sacha', 'Touille',to_date('19450508','YYYYMMDD'), 0743215678, 'Sacha.Touille@gmail.com', typAdresse('Rue Foche','13','Compiegne','60200'), 0.00);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('gentleman', 'Arsene', 'Lupin',to_date('18740101','YYYYMMDD'), NULL, 'Arsene.Lupin@hotmail.fr', typAdresse('Rue de la Paix','12','Paris','75001'), 9999.99);
INSERT INTO Utilisateur(pseudo, nom, prenom, date_naissance, tel, mail, ville, code_postal, montant_porte_feuille)
VALUES ('jujubis', 'Justine', 'Tigoutte',to_date('20001225','YYYYMMDD'), 0612345679, 'Justinebis.Tigoutte@hotmail.fr', typAdresse('Rue Antoinette','21','Compiegne','60200'), 60200, 50.50);

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

