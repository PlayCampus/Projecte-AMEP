USE amep06;

DROP TABLE IF EXISTS \ConvocatoriaPartit\;
CREATE TABLE \ConvocatoriaPartit\ (
  \idPartit\ varchar(36) NOT NULL,
  \idJugador\ int(11) NOT NULL,
  \convocat\ tinyint(1) DEFAULT NULL,
  \confirmat\ tinyint(1) DEFAULT NULL,
  PRIMARY KEY (\idPartit\,\idJugador\),
  KEY \k_convocatoria_jugador\ (\idJugador\),
  CONSTRAINT \k_convocatoria_partit\ FOREIGN KEY (\idPartit\) REFERENCES \Partit\ (\idPartit\) ON DELETE CASCADE,
  CONSTRAINT \k_convocatoria_jugador\ FOREIGN KEY (\idJugador\) REFERENCES \Jugador\ (\idJugador\) ON DELETE CASCADE
);
