
#include "pch.h"
#include "CercadoraEquip.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {

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



        List<String^>^ CercadoraEquip::ObtenirNomsEquipsPerTemporada(String^ idTemporada) {
            List<String^>^ nomsEquips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT nom FROM Equip WHERE idTemporada = @idTemporada ORDER BY nom";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    nomsEquips->Add(reader["nom"]->ToString());
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return nomsEquips;
        }

        String^ CercadoraEquip::ObtenirIdEquipPerNomITemporada(String^ nomEquip, String^ idTemporada) {
            String^ idEquip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Equip WHERE nom COLLATE utf8mb4_bin = @nom AND idTemporada = @idTemporada LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomEquip);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idEquip = resultat->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idEquip;
        }

        String^ CercadoraEquip::ObtenirIdEquipPerNom(String^ nomEquip) {
            String^ idEquip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Equip WHERE nom COLLATE utf8mb4_bin = @nom LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomEquip);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idEquip = resultat->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idEquip;
        }

        String^ CercadoraEquip::ObtenirIdEquipCapita(String^ correuCapita) {
            String^ idEquip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT C.idEquip FROM Capita C "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuCapita);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idEquip = resultat->ToString()->Trim();
                }
            }
            finally {
                conn->Close();
            }
            return idEquip;
        }

        bool CercadoraEquip::ExisteixEquipPerId(String^ idEquip) {
            bool existeix = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                existeix = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return existeix;
        }

        bool CercadoraEquip::ExisteixEquipPerNom(String^ nomEquip) {
            bool existeix = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM Equip WHERE nom = @nomEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomEquip", nomEquip);
                existeix = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return existeix;
        }

        List<Dictionary<String^, String^>^>^ CercadoraEquip::ObtenirJugadorsEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT J.idJugador, U.nom, J.dorsal, J.posicio "
                    "FROM Jugador J "
                    "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                    "WHERE J.idEquip = @idEquip "
                    "ORDER BY J.dorsal ASC, U.nom ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
                    jugador["idJugador"] = reader["idJugador"]->ToString();
                    jugador["nom"] = reader["nom"]->ToString();
                    jugador["dorsal"] = reader->IsDBNull(reader->GetOrdinal("dorsal")) ? "" : reader["dorsal"]->ToString();
                    jugador["posicio"] = reader->IsDBNull(reader->GetOrdinal("posicio")) ? "" : reader["posicio"]->ToString();
                    jugadors->Add(jugador);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return jugadors;
        }

        DataTable^ CercadoraEquip::ObtenirPlantillaEquip(String^ idEquip) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT j.idJugador AS IdJugador, u.nom AS Nom, j.dorsal AS Dorsal, j.posicio AS `Posició` "
                    "FROM Jugador j "
                    "INNER JOIN Usuari u ON j.idJugador = u.identificador "
                    "WHERE j.idEquip = @idEquip "
                    "ORDER BY j.dorsal ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        List<String^>^ CercadoraEquip::ObtenirNomsEquipsPerLliga(String^ nomLliga) {
            List<String^>^ equips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DISTINCT E.nom "
                    "FROM Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE L.nom = @nomLliga "
                    "ORDER BY E.nom";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    equips->Add(reader["nom"]->ToString());
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return equips;
        }

        static DataTable^ ExecutarConsultaEquipLocal(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            DataTable^ resultat = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for (int i = 0; i < parametres->Length; i++) {
                        cmd->Parameters->Add(parametres[i]);
                    }
                }
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(resultat);
            }
            finally {
                conn->Close();
            }
            return resultat;
        }

        static Object^ ExecutarEscalarEquipLocal(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            Object^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for (int i = 0; i < parametres->Length; i++) {
                        cmd->Parameters->Add(parametres[i]);
                    }
                }
                resultat = cmd->ExecuteScalar();
            }
            finally {
                conn->Close();
            }
            return resultat;
        }

        static bool EquipTeColumnaLocal(String^ connectionString, String^ nomColumna) {
            String^ consulta =
                "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS "
                "WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Equip' AND COLUMN_NAME = @nomColumna";
            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomColumna", nomColumna);
            Object^ resultat = ExecutarEscalarEquipLocal(connectionString, consulta, parametres);
            return resultat != nullptr && resultat != DBNull::Value && Convert::ToInt32(resultat) > 0;
        }

        DataTable^ CercadoraEquip::ObtenirLliguesEquip(String^ nomEquip) {
            String^ consulta;
            bool teIdTemporada = EquipTeColumnaLocal(connectionString, "idTemporada");
            if (teIdTemporada) {
                consulta =
                    "SELECT DISTINCT L.idLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "UNION "
                    "SELECT DISTINCT L.idLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
                    "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                    "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "ORDER BY NomLliga";
            }
            else {
                consulta =
                    "SELECT DISTINCT L.idLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Lliga L ON E.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "UNION "
                    "SELECT DISTINCT L.idLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN Partit P ON E.idEquip = P.idEquipLocal OR E.idEquip = P.idEquipVisitant "
                    "INNER JOIN Jornada J ON P.idJornada = J.idJornada "
                    "INNER JOIN Temporada T ON J.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "ORDER BY NomLliga";
            }
            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);
            return ExecutarConsultaEquipLocal(connectionString, consulta, parametres);
        }

        DataTable^ CercadoraEquip::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            String^ consulta;
            bool teIdTemporada = EquipTeColumnaLocal(connectionString, "idTemporada");
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
            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(2);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);
            parametres[1] = gcnew MySqlParameter("@idLliga", idLliga);
            return ExecutarConsultaEquipLocal(connectionString, consulta, parametres);
        }

        DataTable^ CercadoraEquip::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            String^ condicioAssociacio = "P.idPartit IS NOT NULL";
            bool teIdTemporada = EquipTeColumnaLocal(connectionString, "idTemporada");
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
                "WHERE E.nom = @nomEquip AND L.idLliga = @idLliga AND (" + condicioAssociacio + ") "
                "GROUP BY L.nom, T.idTemporada, T.dataInici, T.dataFi, E.idEquip, E.nom, E.esport, E.posicioClassificacio "
                "ORDER BY Punts DESC, DiferenciaGols DESC, E.nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(3);
            parametres[0] = gcnew MySqlParameter("@nomEquip", nomEquip);
            parametres[1] = gcnew MySqlParameter("@idLliga", idLliga);
            parametres[2] = gcnew MySqlParameter("@idTemporada", idTemporada);

            return ExecutarConsultaEquipLocal(connectionString, consultaBase, parametres);
        }

    }
}
