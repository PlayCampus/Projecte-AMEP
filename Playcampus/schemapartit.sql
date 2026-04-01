USE amep06;

CREATE TABLE IF NOT EXISTS Partit (
    idPartit VARCHAR(36) PRIMARY KEY,
    idLliga VARCHAR(36) NOT NULL,
    idJornada INT,
    idEquipLocal VARCHAR(100) NOT NULL,
    idEquipVisitant VARCHAR(100) NOT NULL,
    dataHora DATETIME NOT NULL,
    ubicacio VARCHAR(255) DEFAULT NULL,
    estat VARCHAR(50) DEFAULT 'Pendent',
    golsLocal INT DEFAULT NULL,
    golsVisitant INT DEFAULT NULL,
    
    CONSTRAINT fk_partit_lliga FOREIGN KEY (idLliga) REFERENCES Lliga(idLliga) ON DELETE CASCADE,
    CONSTRAINT fk_partit_equip_local FOREIGN KEY (idEquipLocal) REFERENCES Equip(idEquip) ON DELETE CASCADE,
    CONSTRAINT fk_partit_equip_visitant FOREIGN KEY (idEquipVisitant) REFERENCES Equip(idEquip) ON DELETE CASCADE
);
