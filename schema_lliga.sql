USE amep06;

CREATE TABLE IF NOT EXISTS Lliga (
    idLliga VARCHAR(36) PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    disciplina VARCHAR(50) NOT NULL,
    descripcio TEXT,
    contrasenya VARCHAR(255),
    idAdministrador INT,
    FOREIGN KEY (idAdministrador) REFERENCES Administrador(identificador) ON DELETE SET NULL
);