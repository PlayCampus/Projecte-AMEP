USE amep06;

CREATE TABLE IF NOT EXISTS Temporada (
    idTemporada VARCHAR(36) PRIMARY KEY,
    idLliga VARCHAR(36) NOT NULL,
    dataInici DATETIME NOT NULL,
    dataFi DATETIME NOT NULL,
    estat VARCHAR(50),
    CONSTRAINT fk_temporada_lliga FOREIGN KEY (idLliga) REFERENCES Lliga(idLliga) ON DELETE CASCADE
);