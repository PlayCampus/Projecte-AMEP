USE amep06;

CREATE TABLE IF NOT EXISTS UsuariSegueixLliga (
    idUsuari INT NOT NULL,
    idLliga VARCHAR(36) NOT NULL,
    dataSeguiment DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (idUsuari),
    INDEX idx_usuarisegueixlliga_idlliga (idLliga),
    CONSTRAINT fk_usuarisegueixlliga_usuari FOREIGN KEY (idUsuari) REFERENCES Usuari(identificador) ON DELETE CASCADE,
    CONSTRAINT fk_usuarisegueixlliga_lliga FOREIGN KEY (idLliga) REFERENCES Lliga(idLliga) ON DELETE CASCADE
);
