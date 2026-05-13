USE amep06;

CREATE TABLE IF NOT EXISTS Partit (
    idPartit VARCHAR(36) PRIMARY KEY,
    idJornada VARCHAR(36) NOT NULL,
    idEquipLocal VARCHAR(100),
    idEquipVisitant VARCHAR(100),
    dataHora DATETIME NOT NULL,
    ubicacio VARCHAR(255) DEFAULT NULL,
    estat VARCHAR(50) DEFAULT 'Pendent',
    golsLocal INT DEFAULT NULL,
    golsVisitant INT DEFAULT NULL,
    
    CONSTRAINT fk_partit_jornada FOREIGN KEY (idJornada) REFERENCES Jornada(idJornada) ON DELETE CASCADE,
    CONSTRAINT fk_partit_equip_local FOREIGN KEY (idEquipLocal) REFERENCES Equip(idEquip) ON DELETE SET NULL,
    CONSTRAINT fk_partit_equip_visitant FOREIGN KEY (idEquipVisitant) REFERENCES Equip(idEquip) ON DELETE SET NULL
);
