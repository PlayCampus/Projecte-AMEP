USE amep06;


CREATE TABLE IF NOT EXISTS Jornada (
    idJornada VARCHAR(36) PRIMARY KEY,
    idTemporada VARCHAR(36) NOT NULL,
    numero INT NOT NULL,
    dataInici DATETIME NOT NULL,
    dataFi DATETIME NOT NULL,
    estat VARCHAR(50) NOT NULL,
    CONSTRAINT fk_jornada_temporada FOREIGN KEY (idTemporada) REFERENCES Temporada(idTemporada) ON DELETE CASCADE
);