USE amep06;

CREATE TABLE IF NOT EXISTS AssignacioJugadorPartit (
    idPartit VARCHAR(100) NOT NULL,
    idJugador INT NOT NULL,
    dataAssignacio DATETIME NOT NULL,

    PRIMARY KEY (idPartit, idJugador),
    CONSTRAINT fk_assignacio_partit FOREIGN KEY (idPartit) REFERENCES Partit(idPartit) ON DELETE CASCADE,
    CONSTRAINT fk_assignacio_jugador FOREIGN KEY (idJugador) REFERENCES Jugador(idJugador) ON DELETE CASCADE
);
