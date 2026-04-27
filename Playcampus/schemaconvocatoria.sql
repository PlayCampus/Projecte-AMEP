USE amep06;

CREATE TABLE IF NOT EXISTS Convocatoria (
    idConvocatoria VARCHAR(36) PRIMARY KEY,
    idPartit VARCHAR(36) NOT NULL,
    idEquip VARCHAR(36) NOT NULL
);

CREATE TABLE IF NOT EXISTS ConvocatoriaJugador (
    idConvocatoria VARCHAR(36),
    nomJugador VARCHAR(100),
    assistira BOOLEAN DEFAULT NULL,
    PRIMARY KEY (idConvocatoria, nomJugador),
    CONSTRAINT fk_convocatoria_jugador FOREIGN KEY (idConvocatoria) REFERENCES Convocatoria(idConvocatoria) ON DELETE CASCADE
);
