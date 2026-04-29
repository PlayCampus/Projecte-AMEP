USE amep06;

CREATE TABLE IF NOT EXISTS Jugador (
    idJugador VARCHAR(36) PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    dorsal INT,
    posicio VARCHAR(50),
    data_naixement DATE,
    partitsJugats INT DEFAULT 0,
    anotacions INT DEFAULT 0,
    assistencies INT DEFAULT 0,
    faltesLleus INT DEFAULT 0,
    faltesGreus INT DEFAULT 0,
    minutsJugats INT DEFAULT 0,
    idEquip VARCHAR(36),
    CONSTRAINT fk_jugador_equip FOREIGN KEY (idEquip) REFERENCES Equip(idEquip) ON DELETE SET NULL
);
