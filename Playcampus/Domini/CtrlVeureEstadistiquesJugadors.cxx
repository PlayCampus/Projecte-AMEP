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

		DataTable^ CtrlVeureEstadistiquesJugadors::ObtenirEstadistiquesPartit(String^ idPartit) {
			DataTable^ dt = gcnew DataTable();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				String^ query =
					"SELECT idJugador AS IdJugador, nomJugador AS NomJugador, posicio AS Posicio, "
					"targetesgrogues AS TargetesGrogues, targetesvermelles AS TargetesVermelles, golsmarcat AS GolsMarcats, "
					"asistencies AS Assistencies, targetesgroguesobtenides AS TargetesGroguesObtenides, targetesvermelllesobtenides AS TargetesVermelllesObtenides, dataActualitzacio AS DataActualitzacio "
					"FROM PartitEstadisticaIndividual WHERE idPartit = @idPartit";

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

