#include "pch.h"
#include "CtrlVeureEstadistiquesJugadors.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
	namespace Domini {

		CtrlVeureEstadistiquesJugadors::CtrlVeureEstadistiquesJugadors() {
			connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
		}

		DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesJugador(String^ idJugador) {
			DataTable^ dt = gcnew DataTable();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				String^ query =
					"SELECT u.identificador AS IdJugador, u.nom AS Nom, j.dorsal AS Dorsal, j.posicio AS Posicio, "
					"j.partitsJugats AS PartitsJugats, j.anotacions AS Anotacions, j.assistencies AS Assistencies, "
					"j.faltesLleus AS FaltesLleus, j.faltesGreus AS FaltesGreus, j.minutsJugats AS MinutsJugats, j.idEquip AS IdEquip "
					"FROM Jugador j INNER JOIN Usuari u ON j.idJugador = u.identificador "
					"WHERE j.idJugador = @idJugador";

				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				cmd->Parameters->AddWithValue("@idJugador", idJugador);

				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
				adapter->Fill(dt);
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}

			return dt;
		}

		//Return: El ID del partido, el nombre del equipo local, el nombre del equipo visitante, los goles locales y los goles visitantes.
		DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirDetallsPartit(String^ idPartit) {
			DataTable^ dt = gcnew DataTable();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				// Se usan idEquipLocal e idEquipVisitant según la definición de la tabla Partit
				String^ query =
					"SELECT p.idPartit, el.nom AS EquipLocal, ev.nom AS EquipVisitant, "
					"p.golsLocal AS GolsLocals, p.golsVisitant AS GolsVisitants "
					"FROM Partit p "
					"INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
					"INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
					"WHERE p.idPartit = @idPartit";

				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				cmd->Parameters->AddWithValue("@idPartit", idPartit);

				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
				adapter->Fill(dt);
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}
			return dt;
		}

		//Return: Las estadísticas individuales de cada jugador en el partido (goles, tarjetas, asistencias, etc.) y su respectivo equipo (IdEquip) para poder agruparlos por equipo local y visitante.
		DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesPartit(String^ idPartit) {
			DataTable^ dt = gcnew DataTable();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				// Se incluyen todas las métricas de PartitEstadisticaIndividual 
				String^ query =
					"SELECT pei.idJugador AS IdJugador, pei.nomJugador AS NomJugador, pei.posicio AS Posicio, "
					"pei.targetesgrogues AS TargetesGrogues, pei.targetesvermelles AS TargetesVermelles, pei.golsmarcat AS GolsMarcats, "
					"pei.asistencies AS Assistencies, pei.targetesgroguesobtenides AS TargetesGroguesObtenides, "
					"pei.targetesvermelllesobtenides AS TargetesVermelllesObtenides, pei.dataActualitzacio AS DataActualitzacio, "
					"j.idEquip AS IdEquip "
					"FROM PartitEstadisticaIndividual pei "
					"INNER JOIN Jugador j ON pei.idJugador = j.idJugador "
					"WHERE pei.idPartit = @idPartit "
					"ORDER BY j.idEquip";

				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				cmd->Parameters->AddWithValue("@idPartit", idPartit);

				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
				adapter->Fill(dt);
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}

			return dt;
		}

	}
}