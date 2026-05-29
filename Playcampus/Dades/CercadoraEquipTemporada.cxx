#include "pch.h"
#include "CercadoraEquipTemporada.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {

        CercadoraEquipTemporada::CercadoraEquipTemporada(String^ connStr) {
            connectionString = connStr;
        }

        List<String^>^ CercadoraEquipTemporada::ObtenirIdsEquipsPerTemporada(String^ idTemporada) {
            List<String^>^ idsEquips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM EquipTemporada WHERE idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    idsEquips->Add(reader["idEquip"]->ToString());
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return idsEquips;
        }

        String^ CercadoraEquipTemporada::ObtenirIdTemporadaPerEquip(String^ idEquip) {
            String^ idTemporada = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT ET.idTemporada "
                    "FROM EquipTemporada ET "
                    "INNER JOIN Temporada T ON T.idTemporada = ET.idTemporada "
                    "WHERE ET.idEquip = @idEquip "
                    "ORDER BY CASE "
                    "WHEN T.estat = 'EnCurs' THEN 0 "
                    "WHEN T.estat <> 'Finalitzat' THEN 1 "
                    "ELSE 2 END, T.dataInici DESC, T.dataFi DESC "
                    "LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                if (reader->Read()) {
                    idTemporada = reader["idTemporada"]->ToString();
                }
                reader->Close();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return idTemporada;
        }

        List<String^>^ CercadoraEquipTemporada::ObtenirNomsEquipsPerTemporada(String^ idTemporada) {
            List<String^>^ nomsEquips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT E.nom FROM Equip E "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "WHERE ET.idTemporada = @idTemporada "
                    "ORDER BY E.nom";
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

        String^ CercadoraEquipTemporada::ObtenirIdEquipPerNomITemporada(String^ nomEquip, String^ idTemporada) {
            String^ idEquip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT E.idEquip FROM Equip E "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "WHERE E.nom COLLATE utf8mb4_bin = @nom AND ET.idTemporada = @idTemporada LIMIT 1";
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

        List<String^>^ CercadoraEquipTemporada::ObtenirNomsEquipsPerLliga(String^ nomLliga) {
            List<String^>^ equips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DISTINCT E.nom "
                    "FROM Equip E "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
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

        DataTable^ CercadoraEquipTemporada::ObtenirLliguesEquip(String^ nomEquip) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DISTINCT L.idLliga, L.nom AS NomLliga "
                    "FROM Equip E "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip "
                    "ORDER BY NomLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomEquip", nomEquip);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraEquipTemporada::ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DISTINCT T.idTemporada AS IdTemporada, "
                    "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS NomTemporada "
                    "FROM Equip E "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "WHERE E.nom = @nomEquip AND T.idLliga = @idLliga "
                    "ORDER BY NomTemporada DESC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomEquip", nomEquip);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraEquipTemporada::ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Ahora lee directo de EquipTemporada respetando el alias exacto y el orden.
                String^ query =
                    "SELECT L.nom AS Lliga, "
                    "CONCAT('Temporada ', DATE_FORMAT(T.dataInici, '%Y'), '-', DATE_FORMAT(T.dataFi, '%Y')) AS Temporada, "
                    "E.nom AS Equip, E.esport AS Esport, "
                    "ET.partitsJugats AS PartitsJugats, "
                    "ET.victories AS Victories, "
                    "ET.empats AS Empats, "
                    "ET.derrotes AS Derrotes, "
                    "ET.punts AS Punts, "
                    "ET.golsAFavor AS GolsAFavor, "
                    "ET.golsEnContra AS GolsEnContra, "
                    "ET.diferenciaGols AS DiferenciaGols, "
                    "ET.posicioClassificacio AS PosicioClassificacio "
                    "FROM Equip E "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "INNER JOIN Temporada T ON ET.idTemporada = T.idTemporada "
                    "INNER JOIN Lliga L ON T.idLliga = L.idLliga "
                    "WHERE E.nom = @nomEquip AND L.idLliga = @idLliga AND T.idTemporada = @idTemporada "
                    "ORDER BY ET.punts DESC, ET.diferenciaGols DESC, E.nom ASC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomEquip", nomEquip);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

    }
}