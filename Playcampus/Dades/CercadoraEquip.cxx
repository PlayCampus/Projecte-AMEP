
#include "pch.h"
#include "CercadoraEquip.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
	namespace Dades {

		static void AfegeixParametres(MySqlCommand^ cmd, Dictionary<String^, Object^>^ parametres) {
			if (parametres != nullptr) {
				for each (KeyValuePair<String^, Object^> parella in parametres) {
					Object^ valor = parella.Value;
					if (valor == nullptr) {
						valor = DBNull::Value;
					}
					cmd->Parameters->AddWithValue(parella.Key, valor);
				}
			}
		}

		static DataTable^ ExecutaConsulta(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
			DataTable^ taula = gcnew DataTable();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				AfegeixParametres(cmd, parametres);
				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
				adapter->Fill(taula);
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}
			return taula;
		}

		static Object^ ExecutaEscalar(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
			Object^ resultat = nullptr;
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				AfegeixParametres(cmd, parametres);
				resultat = cmd->ExecuteScalar();
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}
			return resultat;
		}

		static Dictionary<String^, Object^>^ Params1(String^ k1, Object^ v1) {
			Dictionary<String^, Object^>^ p = gcnew Dictionary<String^, Object^>();
			p[k1] = v1;
			return p;
		}

		static Dictionary<String^, Object^>^ Params2(String^ k1, Object^ v1, String^ k2, Object^ v2) {
			Dictionary<String^, Object^>^ p = Params1(k1, v1);
			p[k2] = v2;
			return p;
		}

		static Dictionary<String^, Object^>^ Params3(String^ k1, Object^ v1, String^ k2, Object^ v2, String^ k3, Object^ v3) {
			Dictionary<String^, Object^>^ p = Params2(k1, v1, k2, v2);
			p[k3] = v3;
			return p;
		}

		static String^ EscalarString(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
			String^ valor = nullptr;
			Object^ resultat = ExecutaEscalar(connectionString, query, parametres);
			if (resultat != nullptr && resultat != DBNull::Value) {
				valor = resultat->ToString();
			}
			return valor;
		}

		static bool EscalarBoolCount(String^ connectionString, String^ query, Dictionary<String^, Object^>^ parametres) {
			bool existeix = false;
			Object^ resultat = ExecutaEscalar(connectionString, query, parametres);
			if (resultat != nullptr && resultat != DBNull::Value) {
				existeix = Convert::ToInt32(resultat) > 0;
			}
			return existeix;
		}

		CercadoraEquip::CercadoraEquip(String^ connStr) {
			connectionString = connStr;
		}

		List<String^>^ CercadoraEquip::ObtenirIdsEquipsPerTemporada(String^ idTemporada) {
			List<String^>^ idsEquips = gcnew List<String^>();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			try {
				conn->Open();
				String^ query = "SELECT idEquip FROM Equip WHERE idTemporada = @idTemporada";
				MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
				cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
				MySqlDataReader^ reader = cmd->ExecuteReader();
				while (reader->Read()) {
					idsEquips->Add(reader["idEquip"]->ToString());
				}
			}
			finally {
				conn->Close();
			}
			return idsEquips;
		}

		bool CercadoraEquip::ExisteixEquip(String^ idEquip) {
			return EscalarBoolCount(connectionString,
				"SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip",
				Params1("@idEquip", idEquip));
		}

		bool CercadoraEquip::JugadorPertanyAEquip(String^ idJugador, String^ idEquip) {
			return EscalarBoolCount(connectionString,
				"SELECT COUNT(*) FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip",
				Params2("@idJugador", idJugador, "@idEquip", idEquip));
		}

		List<String^>^ CercadoraEquip::ObtenirNomsEquipsPerLliga(String^ nomLliga) {
			List<String^>^ equips = gcnew List<String^>();
			DataTable^ taula = ExecutaConsulta(connectionString,
				"SELECT e.nom FROM Equip e INNER JOIN Temporada t ON e.idTemporada = t.idTemporada INNER JOIN Lliga l ON t.idLliga = l.idLliga WHERE l.nom = @nomLliga",
				Params1("@nomLliga", nomLliga));
			for each (DataRow^ fila in taula->Rows) {
				equips->Add(fila["nom"]->ToString());
			}
			return equips;
		}

		List<Dictionary<String^, String^>^>^ CercadoraEquip::ObtenirPartitsDisponiblesEquip(String^ idEquip) {
			List<Dictionary<String^, String^>^>^ partits = gcnew List<Dictionary<String^, String^>^>();
			String^ query =
				"SELECT p.idPartit, p.dataHora, p.ubicacio, p.estat, "
				"el.nom AS equipLocal, ev.nom AS equipVisitant "
				"FROM Partit p "
				"INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
				"INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
				"WHERE (p.idEquipLocal = @idEquip OR p.idEquipVisitant = @idEquip) "
				"AND (p.estat IS NULL OR LOWER(p.estat) <> 'finalitzat') "
				"ORDER BY p.dataHora ASC";
			DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idEquip", idEquip));
			for each (DataRow^ row in taula->Rows) {
				Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
				partit["idPartit"] = row["idPartit"]->ToString();
				partit["dataHora"] = row["dataHora"]->ToString();
				partit["ubicacio"] = row["ubicacio"]->ToString();
				partit["estat"] = row["estat"]->ToString();
				partit["equipLocal"] = row["equipLocal"]->ToString();
				partit["equipVisitant"] = row["equipVisitant"]->ToString();
				partits->Add(partit);
			}
			return partits;
		}

		List<Dictionary<String^, String^>^>^ CercadoraEquip::ObtenirJugadorsEquipPerAssignacio(String^ idEquip) {
			List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
			String^ query =
				"SELECT J.idJugador, U.nom, J.dorsal, J.posicio "
				"FROM Jugador J "
				"INNER JOIN Usuari U ON J.idJugador = U.identificador "
				"WHERE J.idEquip = @idEquip "
				"ORDER BY J.dorsal ASC, U.nom ASC";
			DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idEquip", idEquip));
			for each (DataRow^ row in taula->Rows) {
				Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
				jugador["idJugador"] = row["idJugador"]->ToString();
				jugador["nom"] = row["nom"]->ToString();
				jugador["dorsal"] = row["dorsal"]->ToString();
				jugador["posicio"] = row["posicio"]->ToString();
				jugadors->Add(jugador);
			}
			return jugadors;
		}

		List<Dictionary<String^, String^>^>^ CercadoraEquip::ObtenirPlantillaPerEquip(String^ idEquip) {
			List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
			String^ query =
				"SELECT j.idJugador, u.nom, j.dorsal, j.posicio "
				"FROM Jugador j "
				"INNER JOIN Usuari u ON j.idJugador = u.identificador "
				"WHERE j.idEquip = @idEquip "
				"ORDER BY j.dorsal ASC";
			DataTable^ taula = ExecutaConsulta(connectionString, query, Params1("@idEquip", idEquip));
			for each (DataRow^ row in taula->Rows) {
				Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
				jugador["idJugador"] = row["idJugador"]->ToString();
				jugador["nom"] = row["nom"]->ToString();
				jugador["dorsal"] = row["dorsal"]->ToString();
				jugador["posicio"] = row["posicio"]->ToString();
				jugadors->Add(jugador);
			}
			return jugadors;
		}

		bool CercadoraEquip::ExisteixEquipPerNom(String^ nomEquip) {
			return EscalarBoolCount(connectionString,
				"SELECT COUNT(*) FROM Equip WHERE nom = @nomEquip",
				Params1("@nomEquip", nomEquip));
		}

		static bool EquipTeColumnaSistema(String^ connectionString, String^ nomColumna) {
			return EscalarBoolCount(connectionString,
				"SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Equip' AND COLUMN_NAME = @nomColumna",
				Params1("@nomColumna", nomColumna));
		}

		DataTable^ CercadoraEquip::ObtenirLliguesEquip(String^ nomEquip) {
			String^ consulta = nullptr;
			bool teIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
			if (teIdTemporada) {
				consulta =
					"SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
					"FROM Equip E "
					"INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
					"INNER JOIN Lliga L ON T.idLliga = L.idLliga "
					"WHERE E.nom = @nomEquip "
					"UNION "
					"SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
					"FROM Equip E "
					"INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
					"INNER JOIN Jornada J ON P.idJornada = J.idJornada "
					"INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
					"INNER JOIN Lliga L ON T.idLliga = L.idLliga "
					"WHERE E.nom = @nomEquip "
					"ORDER BY NomLliga ASC";
			}
			else {
				consulta =
					"SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
					"FROM Equip E "
					"INNER JOIN Lliga L ON E.idLliga = L.idLliga "
					"WHERE E.nom = @nomEquip "
					"UNION "
					"SELECT DISTINCT L.idLliga AS IdLliga, L.nom AS NomLliga "
					"FROM Equip E "
					"INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
					"INNER JOIN Jornada J ON P.idJornada = J.idJornada "
					"INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
					"INNER JOIN Lliga L ON T.idLliga = L.idLliga "
					"WHERE E.nom = @nomEquip "
					"ORDER BY NomLliga ASC";
			}
			return ExecutaConsulta(connectionString, consulta, Params1("@nomEquip", nomEquip));
		}

		DataTable^ CercadoraEquip::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
			String^ consulta = nullptr;
			bool teIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
			if (teIdTemporada) {
				consulta =
					"SELECT DISTINCT T.idTemporada AS IdTemporada, "
					"CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
					"FROM Equip E "
					"INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
					"WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
					"UNION "
					"SELECT DISTINCT T.idTemporada AS IdTemporada, "
					"CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
					"FROM Equip E "
					"INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
					"INNER JOIN Jornada J ON P.idJornada = J.idJornada "
					"INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
					"WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
					"ORDER BY NomTemporada DESC";
			}
			else {
				consulta =
					"SELECT DISTINCT T.idTemporada AS IdTemporada, "
					"CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
					"FROM Equip E "
					"INNER JOIN Lliga L ON E.idLliga = L.idLliga "
					"INNER JOIN Temporada T ON T.idLliga = L.idLliga "
					"WHERE E.nom = @nomEquip AND L.idLliga = @idLliga "
					"UNION "
					"SELECT DISTINCT T.idTemporada AS IdTemporada, "
					"CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
					"FROM Equip E "
					"INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
					"INNER JOIN Jornada J ON P.idJornada = J.idJornada "
					"INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
					"WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
					"ORDER BY NomTemporada DESC";
			}
			return ExecutaConsulta(connectionString, consulta, Params2("@nomEquip", nomEquip, "@idLliga", idLliga));
		}

		DataTable^ CercadoraEquip::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
			String^ condicioAssociacio = "P.idPartit IS NOT NULL";
			bool teIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
			if (teIdTemporada) {
				condicioAssociacio = "E.idTemporada = T.idTemporada OR P.idPartit IS NOT NULL";
			}
			else {
				condicioAssociacio = "E.idLliga = L.idLliga OR P.idPartit IS NOT NULL";
			}
			String^ consultaBase =
				"SELECT L.nom AS Lliga, "
				"CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS Temporada, "
				"E.nom AS Equip, E.esport AS Esport, "
				"COUNT(CASE WHEN P.estat = 'Finalitzat' THEN P.idPartit END) AS PartitsJugats, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND ((P.idEquipLocal = E.idEquip AND P.golsLocal > P.golsVisitant) OR (P.idEquipVisitant = E.idEquip AND P.golsVisitant > P.golsLocal)) THEN 1 ELSE 0 END), 0) AS Victories, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.golsLocal = P.golsVisitant THEN 1 ELSE 0 END), 0) AS Empats, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND ((P.idEquipLocal = E.idEquip AND P.golsLocal < P.golsVisitant) OR (P.idEquipVisitant = E.idEquip AND P.golsVisitant < P.golsLocal)) THEN 1 ELSE 0 END), 0) AS Derrotes, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND ((P.idEquipLocal = E.idEquip AND P.golsLocal > P.golsVisitant) OR (P.idEquipVisitant = E.idEquip AND P.golsVisitant > P.golsLocal)) THEN 3 WHEN P.estat = 'Finalitzat' AND P.golsLocal = P.golsVisitant THEN 1 ELSE 0 END), 0) AS Punts, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsLocal, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsVisitant, 0) ELSE 0 END), 0) AS GolsAFavor, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsVisitant, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsLocal, 0) ELSE 0 END), 0) AS GolsEnContra, "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsLocal, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsVisitant, 0) ELSE 0 END), 0) - "
				"IFNULL(SUM(CASE WHEN P.estat = 'Finalitzat' AND P.idEquipLocal = E.idEquip THEN IFNULL(P.golsVisitant, 0) WHEN P.estat = 'Finalitzat' AND P.idEquipVisitant = E.idEquip THEN IFNULL(P.golsLocal, 0) ELSE 0 END), 0) AS DiferenciaGols, "
				"E.posicioClassificacio AS PosicioClassificacio "
				"FROM Equip E "
				"INNER JOIN Temporada T ON T.idTemporada = @idTemporada "
				"INNER JOIN Lliga L ON L.idLliga = T.idLliga "
				"LEFT JOIN Jornada J ON J.idTemporada = T.idTemporada "
				"LEFT JOIN Partit P ON P.idJornada = J.idJornada AND (P.idEquipLocal = E.idEquip OR P.idEquipVisitant = E.idEquip) "
				"WHERE E.nom = @nomEquip AND T.idLliga = @idLliga AND T.idTemporada = @idTemporada "
				"AND (";
			String^ consultaFinal =
				") "
				"GROUP BY L.nom, T.idTemporada, T.dataInici, T.dataFi, E.idEquip, E.nom, E.esport, E.posicioClassificacio "
				"ORDER BY E.nom ASC";
			return ExecutaConsulta(connectionString, consultaBase + condicioAssociacio + consultaFinal,
				Params3("@nomEquip", nomEquip, "@idLliga", idLliga, "@idTemporada", idTemporada));
		}

		DataTable^ CercadoraEquip::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
			String^ consulta =
				"SELECT E.idEquip AS IdEquip, E.nom AS Equip, E.esport AS Esport, "
							"E.partitsJugats AS Partits, E.victories AS Victories, E.punts AS Punts "
							"FROM Equip E "
							"INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
							"INNER JOIN Lliga L ON T.idLliga = L.idLliga "
							"INNER JOIN Usuari U ON L.idAdministrador = U.identificador "
							"WHERE U.correu_electronic = @correuAdmin "
							"ORDER BY E.nom";
						return ExecutaConsulta(connectionString, consulta, Params1("@correuAdmin", correuAdmin));
					}

					bool CercadoraEquip::CapitaTeEquip(String^ correu) {
						String^ consulta = "SELECT COUNT(*) FROM Capita C INNER JOIN Equip E ON E.idEquip = C.idEquip INNER JOIN Usuari U ON U.identificador = C.identificador WHERE U.correu_electronic = @correu";
						Object^ resultat = ExecutaEscalar(connectionString, consulta, Params1("@correu", correu));
						if (resultat != nullptr && resultat != DBNull::Value) {
							return Convert::ToInt32(resultat) > 0;
						}
						return false;
					}

					bool CercadoraEquip::EquipEstaEnLliga(String^ correu) {
						bool equipTeIdTemporada = EquipTeColumnaSistema(connectionString, "idTemporada");
						String^ consulta;
						if (equipTeIdTemporada) {
							consulta = "SELECT COUNT(*) FROM Capita C INNER JOIN Equip E ON E.idEquip = C.idEquip INNER JOIN Temporada T ON T.idTemporada = E.idTemporada INNER JOIN Lliga L ON L.idLliga = T.idLliga INNER JOIN Usuari U ON U.identificador = C.identificador WHERE U.correu_electronic = @correu";
						} else {
							consulta = "SELECT COUNT(*) FROM Capita C INNER JOIN Equip E ON E.idEquip = C.idEquip INNER JOIN Lliga L ON L.idLliga = E.idLliga INNER JOIN Usuari U ON U.identificador = C.identificador WHERE U.correu_electronic = @correu";
						}
						Object^ resultat = ExecutaEscalar(connectionString, consulta, Params1("@correu", correu));
						if (resultat != nullptr && resultat != DBNull::Value) {
							return Convert::ToInt32(resultat) > 0;
						}
						return false;
					}

					PassarellaEquip^ CercadoraEquip::LlegeixCapitaPerCorreu(String^ correu) {
						MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
						try {
							conn->Open();
							String^ query = "SELECT E.idEquip, E.nom, E.data_fundacio, E.esport, E.partitsJugats, E.victories, E.derrotes, E.empats, E.punts, E.golsAFavor, E.golsEnContra, E.diferenciaGols, E.posicioClassificacio, E.idTemporada "
								"FROM Equip E "
								"INNER JOIN Capita C ON E.idEquip = C.idEquip "
								"INNER JOIN Usuari U ON C.identificador = U.identificador "
								"WHERE U.correu_electronic = @correu LIMIT 1";
							MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
							cmd->Parameters->AddWithValue("@correu", correu);

							MySqlDataReader^ reader = cmd->ExecuteReader();
							if (reader->Read()) {
								String^ idEquip = reader["idEquip"]->ToString();
								String^ nom = reader["nom"]->ToString();
								DateTime dataFundacio = reader->GetDateTime("data_fundacio");
								String^ esport = reader["esport"]->ToString();
								unsigned int partitsJugats = (unsigned int)reader["partitsJugats"];
								unsigned int victories = (unsigned int)reader["victories"];
								unsigned int derrotes = (unsigned int)reader["derrotes"];
								unsigned int empats = (unsigned int)reader["empats"];
								unsigned int punts = (unsigned int)reader["punts"];
								unsigned int golsAFavor = (unsigned int)reader["golsAFavor"];
								unsigned int golsEnContra = (unsigned int)reader["golsEnContra"];
								int diferenciaGols = reader["diferenciaGols"] == DBNull::Value ? 0 : reader->GetInt32("diferenciaGols");
								int posicioClassificacio = reader["posicioClassificacio"] == DBNull::Value ? 0 : reader->GetInt32("posicioClassificacio");
								String^ idTemporada = reader["idTemporada"] == DBNull::Value ? nullptr : reader["idTemporada"]->ToString();

								reader->Close();
								return gcnew PassarellaEquip(connectionString, idEquip, nom, dataFundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio, idTemporada);
							}
							reader->Close();
							return nullptr;
						}
						finally {
							conn->Close();
						}
					}

					PassarellaEquip^ CercadoraEquip::LlegeixCapitaPerIdentificador(String^ identificador) {
						MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
						try {
							conn->Open();
							String^ query = "SELECT E.idEquip, E.nom, E.data_fundacio, E.esport, E.partitsJugats, E.victories, E.derrotes, E.empats, E.punts, E.golsAFavor, E.golsEnContra, E.diferenciaGols, E.posicioClassificacio, E.idTemporada "
								"FROM Equip E "
								"INNER JOIN Capita C ON E.idEquip = C.idEquip "
								"WHERE C.identificador = @identificador LIMIT 1";
							MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
							cmd->Parameters->AddWithValue("@identificador", identificador);

							MySqlDataReader^ reader = cmd->ExecuteReader();
							if (reader->Read()) {
								String^ idEquip = reader["idEquip"]->ToString();
								String^ nom = reader["nom"]->ToString();
								DateTime dataFundacio = reader->GetDateTime("data_fundacio");
								String^ esport = reader["esport"]->ToString();
								unsigned int partitsJugats = (unsigned int)reader["partitsJugats"];
								unsigned int victories = (unsigned int)reader["victories"];
								unsigned int derrotes = (unsigned int)reader["derrotes"];
								unsigned int empats = (unsigned int)reader["empats"];
								unsigned int punts = (unsigned int)reader["punts"];
								unsigned int golsAFavor = (unsigned int)reader["golsAFavor"];
								unsigned int golsEnContra = (unsigned int)reader["golsEnContra"];
								int diferenciaGols = reader["diferenciaGols"] == DBNull::Value ? 0 : reader->GetInt32("diferenciaGols");
								int posicioClassificacio = reader["posicioClassificacio"] == DBNull::Value ? 0 : reader->GetInt32("posicioClassificacio");
								String^ idTemporada = reader["idTemporada"] == DBNull::Value ? nullptr : reader["idTemporada"]->ToString();

								reader->Close();
								return gcnew PassarellaEquip(connectionString, idEquip, nom, dataFundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio, idTemporada);
							}
							reader->Close();
							return nullptr;
						}
						finally {
							conn->Close();
						}
					}

					PassarellaEquip^ CercadoraEquip::LlegeixPerNomExacte(String^ nomEquip) {
						MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
						try {
							conn->Open();
							String^ query = "SELECT idEquip, nom, data_fundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio, idTemporada FROM Equip WHERE nom COLLATE utf8mb4_bin = @nom LIMIT 1";
							MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
							cmd->Parameters->AddWithValue("@nom", nomEquip);

							MySqlDataReader^ reader = cmd->ExecuteReader();
							if (reader->Read()) {
								String^ idEquip = reader["idEquip"]->ToString();
								String^ nom = reader["nom"]->ToString();
								DateTime dataFundacio = reader->GetDateTime("data_fundacio");
								String^ esport = reader["esport"]->ToString();
								unsigned int partitsJugats = (unsigned int)reader["partitsJugats"];
								unsigned int victories = (unsigned int)reader["victories"];
								unsigned int derrotes = (unsigned int)reader["derrotes"];
								unsigned int empats = (unsigned int)reader["empats"];
								unsigned int punts = (unsigned int)reader["punts"];
								unsigned int golsAFavor = (unsigned int)reader["golsAFavor"];
								unsigned int golsEnContra = (unsigned int)reader["golsEnContra"];
								int diferenciaGols = reader["diferenciaGols"] == DBNull::Value ? 0 : reader->GetInt32("diferenciaGols");
								int posicioClassificacio = reader["posicioClassificacio"] == DBNull::Value ? 0 : reader->GetInt32("posicioClassificacio");
								String^ idTemporada = reader["idTemporada"] == DBNull::Value ? nullptr : reader["idTemporada"]->ToString();

								reader->Close();
								return gcnew PassarellaEquip(connectionString, idEquip, nom, dataFundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio, idTemporada);
							}
							reader->Close();
							return nullptr;
						}
						finally {
							conn->Close();
						}
					}
				}
				}

