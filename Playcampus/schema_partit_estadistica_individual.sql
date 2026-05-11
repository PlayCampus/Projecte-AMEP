USE amep06;

CREATE TABLE IF NOT EXISTS PartitEstadisticaIndividual (
    idPartit VARCHAR(64) NOT NULL,
    disciplina VARCHAR(30) NOT NULL,
    idJugador INT NOT NULL,
    nomJugador VARCHAR(255) NOT NULL,
    posicio VARCHAR(50) DEFAULT NULL,
    targetesgrogues INT DEFAULT 0,
    targetesvermelles INT DEFAULT 0,
    golsmarcat INT DEFAULT 0,
    asistencies INT DEFAULT 0,
    targetesgroguesobtenides INT DEFAULT 0,
    targetesvermelllesobtenides INT DEFAULT 0,
    dataActualitzacio DATETIME NOT NULL,

    PRIMARY KEY (idPartit, idJugador),
    CONSTRAINT fk_estadistica_partit FOREIGN KEY (idPartit) REFERENCES Partit(idPartit) ON DELETE CASCADE,
    CONSTRAINT fk_estadistica_jugador FOREIGN KEY (idJugador) REFERENCES Jugador(idJugador) ON DELETE CASCADE
);
