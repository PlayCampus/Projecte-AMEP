USE amep06;

CREATE TABLE IF NOT EXISTS Lliga (
    idLliga VARCHAR(36) PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    disciplina VARCHAR(50) NOT NULL,
    descripcio TEXT,
    estat VARCHAR(50) NOT NULL,
    contrasenya VARCHAR(255)
);

DELETE FROM Lliga WHERE nom IN ('Lliga UPC', 'Lliga EPSEVG');

INSERT INTO Lliga (idLliga, nom, disciplina, descripcio, estat, contrasenya)
VALUES ('LL1', 'Lliga UPC', 'Futbol', 'Lliga universitària', 'Activa', NULL);

INSERT INTO Lliga (idLliga, nom, disciplina, descripcio, estat, contrasenya)
VALUES ('LL2', 'Lliga EPSEVG', 'Basquet', 'Competició interna', 'Activa', NULL);