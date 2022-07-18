DROP TABLE Utilisateur;
DROP TABLE Annonce;
DROP TABLE Transaction;


CREATE TABLE Utilisateur(
	pseudo varchar(30) PRIMARY KEY,
	prenom varchar(30) NOT NULL,
	nom varchar(30) NOT NULL,
	ddn Date NOT NULL,
	mail varchar(30) UNIQUE NOT NULL,
	adresse JSON,
	telephones JSON
);

INSERT INTO Utilisateur VALUES(
    'juju',
    'Justine',
    'Tigoutte',
    '2000-09-16',
    'juju@gmail.com',
    '{
        "rue":"Rue de Paris",
        "numero":"7","ville":"Compiègne",
        "code postal":"60200"
    }',
    '["0606060708","0612345678"]'
);


INSERT INTO Utilisateur VALUES(
    'toto',
    'Jean',
    'Tigoutte',
    '1974-09-16',
    'toto@gmail.com',
    '{
        "rue":"Rue Victor Hugo",
        "numero":"12","ville":"Paris",
        "code postal":"75003"
    }',
    '["0606060700","0612345611"]'
);

CREATE TABLE Annonce (
    id varchar primary key,
    date_depot timestamp NOT NULL,
    titre varchar(50) NOT NULL,
    photo1 varchar,
    photo2 varchar,
    photo3 varchar,
    description varchar(250),
    deposeur JSON NOT NULL,
    validation bool NOT NULL,
    administrateur JSON,
    bien JSON,
    check (case
    when validation = 'f' then administrateur is NULL
    when validation = 't' then administrateur is NOT NULL
    end)
);

INSERT INTO Annonce VALUES(
    'AZLD738920',
    '20191012 163455',
    'Telephone de OUF',
    NULL,
    NULL,
    NULL,
    'Bonjour, je vous propose un téléphone exceptionnel à 1500.',
    '{
        "pseudo":"juju",
        "nom":"Justine",
        "prenom":"Tigoutte",
        "ddn":"20001225",
        "tel": ["0606060708","0612345678"],
        "mail":"juju@gmail.com",
        "porte-feuille":"50.50",
        "adresse":{"rue":"Rue de Paris","numero":"7","ville":"Compiègne","code postal":"60200"}
    }',
    '1',
    '{
        "pseudo":"admin1"
    }',
    '{
        "nom":"téléphone",
        "état":"bon",
        "taille":"petit",
        "année d''achat":"2018",
        "description":"Nokia 3310",
        "rubrique":"Téléphonie"
    }'
);


CREATE TABLE Transaction(
    annonce varchar primary key,
    date_transaction date,
    utilisateur JSON,
    note integer,
    commentaire varchar,
    CHECK ((note IS NULL and commentaire IS NULL) OR (note IS NOT NULL and commentaire IS NOT NULL))
);

INSERT INTO Transaction VALUES(
    'Ourson',
    '{
        "Justine",
        "Tigoutte",
        "2000-09-16",
        "juju@gmail.com",
        "adresse":{"rue":"Rue de Paris","numero":"7","ville":"Compiègne","code postal":"60200"}
    }',
    "telephone":["0606060708","0612345678"],
    '20014-09-16',
    '5',
    'Prend en soin'
);

INSERT INTO Transaction VALUES(
    'Iphone',
    '{
        "toto",
        "Jean",
        "Tigoutte",
        "1974-09-16",
        "toto@gmail.com",
        "adresse"{"rue":"Rue Victor Hugo","numero":"12","ville":"Paris","code postal":"75003"}
    }',
    "telephone":["0606060700","0612345611"],
    '2013-09-16',
    '1',
    'ne s''allume pas'
);