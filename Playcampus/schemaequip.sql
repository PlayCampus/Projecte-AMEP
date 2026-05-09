USE amep06;

CREATE TABLE IF NOT EXISTS Equip (
    idEquip VARCHAR(100) PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    dataFundacio DATETIME NOT NULL,
    esport VARCHAR(100) NOT NULL,
    partitsJugats INT DEFAULT 0,
    victories INT DEFAULT 0,
    derrotes INT DEFAULT 0,
    empats INT DEFAULT 0,
    punts INT DEFAULT 0,
    golsAFavor INT DEFAULT 0,
    golsEnContra INT DEFAULT 0,
    diferenciaGols INT DEFAULT 0,
    posicioClassificacio INT DEFAULT 0,
    idTemporada VARCHAR(36) NULL,
    CONSTRAINT fk_equip_temporada FOREIGN KEY (idTemporada) REFERENCES Temporada(idTemporada) ON DELETE SET NULL
);