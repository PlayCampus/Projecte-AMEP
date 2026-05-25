USE amep06;

create table if not exists EquipTemporada (

    idEquip VARCHAR(100) NOT NULL,
    idTemporada VARCHAR(36) NOT NULL,
    partitsJugats INT DEFAULT 0,
    victories INT DEFAULT 0,
    derrotes INT DEFAULT 0,
    empats INT DEFAULT 0,
    punts INT DEFAULT 0,
    golsAFavor INT DEFAULT 0,
    golsEnContra INT DEFAULT 0,
    diferenciaGols INT DEFAULT 0,
    posicioClassificacio INT DEFAULT 0,

    PRIMARY KEY (idEquip, idTemporada),
    CONSTRAINT fk_et_equip FOREIGN KEY (idEquip) REFERENCES Equip(idEquip) ON DELETE CASCADE,
    CONSTRAINT fk_et_temporada FOREIGN KEY (idTemporada) REFERENCES Temporada(idTemporada) ON DELETE CASCADE
);