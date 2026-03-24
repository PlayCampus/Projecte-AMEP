-- Creació de la base de dades utilitzada al mètode de connexió Transaction Script
CREATE DATABASE IF NOT EXISTS playcampus_db;
USE playcampus_db;

-- Taula d'Usuari basada en el diagrama UML
CREATE TABLE IF NOT EXISTS Usuari (
    identificador VARCHAR(50) PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    contrasenya VARCHAR(255) NOT NULL,
    data_registre DATE NOT NULL,
    correu_electronic VARCHAR(150) NOT NULL UNIQUE,
    Tipus VARCHAR(50) NOT NULL -- 'Administrador', 'Capita', 'Estudiant'
);

-- Extensions per subtipus (Class Table Inheritance)
CREATE TABLE IF NOT EXISTS Administrador (
    identificador VARCHAR(50) PRIMARY KEY,
    telefonContacte VARCHAR(20),
    FOREIGN KEY (identificador) REFERENCES Usuari(identificador) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Capita (
    identificador VARCHAR(50) PRIMARY KEY,
    telefonContacte VARCHAR(20),
    idEquip VARCHAR(50),
    validatPerAdmin BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (identificador) REFERENCES Usuari(identificador) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Estudiant (
    identificador VARCHAR(50) PRIMARY KEY,
    carrera VARCHAR(100),
    FOREIGN KEY (identificador) REFERENCES Usuari(identificador) ON DELETE CASCADE
);
