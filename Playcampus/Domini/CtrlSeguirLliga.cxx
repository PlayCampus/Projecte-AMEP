#include "pch.h"
#include "CtrlSeguirLliga.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {

        CtrlSeguirLliga::CtrlSeguirLliga() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        int CtrlSeguirLliga::ObtenirIdUsuariPerCorreu(String^ correu) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT identificador FROM Usuari WHERE correu_electronic = @correu";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ result = cmd->ExecuteScalar();
                if (result == nullptr || result == DBNull::Value) throw gcnew Exception("Usuari no trobat.");
                return Convert::ToInt32(result);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        String^ CtrlSeguirLliga::ObtenirDisciplinaLliga(String^ idLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT disciplina FROM Lliga WHERE idLliga = @idLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result == nullptr || result == DBNull::Value) return nullptr;
                return result->ToString();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        String^ CtrlSeguirLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nomLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result == nullptr || result == DBNull::Value) return nullptr;
                return result->ToString();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        String^ CtrlSeguirLliga::ObtenirNomLligaPerId(String^ idLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT nom FROM Lliga WHERE idLliga = @idLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result == nullptr || result == DBNull::Value) return nullptr;
                return result->ToString();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        String^ CtrlSeguirLliga::ObtenirIdLligaSeguida(String^ correuUsuari) {
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM UsuariSegueixLliga WHERE idUsuari = @idUsuari LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idUsuari", idUsuari);
                Object^ result = cmd->ExecuteScalar();
                if (result == nullptr || result == DBNull::Value) return nullptr;
                return result->ToString();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        bool CtrlSeguirLliga::TeLligaSeguida(String^ correuUsuari) {
            return ObtenirIdLligaSeguida(correuUsuari) != nullptr;
        }

        void CtrlSeguirLliga::SeguirLliga(String^ correuUsuari, String^ nomLliga) {
            String^ idLliga = ObtenirIdLligaPerNom(nomLliga);
            if (String::IsNullOrEmpty(idLliga)) throw gcnew Exception("La lliga no existeix.");

            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                // Ens assegurem que l'usuari només en segueixi una.
                String^ delQuery = "DELETE FROM UsuariSegueixLliga WHERE idUsuari = @idUsuari";
                MySqlCommand^ delCmd = gcnew MySqlCommand(delQuery, conn);
                delCmd->Parameters->AddWithValue("@idUsuari", idUsuari);
                delCmd->ExecuteNonQuery();

                String^ insQuery = "INSERT INTO UsuariSegueixLliga (idUsuari, idLliga, dataSeguiment) VALUES (@idUsuari, @idLliga, NOW())";
                MySqlCommand^ insCmd = gcnew MySqlCommand(insQuery, conn);
                insCmd->Parameters->AddWithValue("@idUsuari", idUsuari);
                insCmd->Parameters->AddWithValue("@idLliga", idLliga);
                insCmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        void CtrlSeguirLliga::DeixarDeSeguir(String^ correuUsuari) {
            int idUsuari = ObtenirIdUsuariPerCorreu(correuUsuari);
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "DELETE FROM UsuariSegueixLliga WHERE idUsuari = @idUsuari";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idUsuari", idUsuari);
                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        String^ CtrlSeguirLliga::ObtenirIdTemporadaRellevant(String^ idLliga) {
            // Preferim una temporada EnCurs; si no n'hi ha, la més recent.
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga AND estat = 'EnCurs' ORDER BY dataInici DESC LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) return result->ToString();

                String^ query2 = "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC LIMIT 1";
                MySqlCommand^ cmd2 = gcnew MySqlCommand(query2, conn);
                cmd2->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result2 = cmd2->ExecuteScalar();
                if (result2 != nullptr && result2 != DBNull::Value) return result2->ToString();
                return nullptr;
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        DataTable^ CtrlSeguirLliga::ObtenirClassificacioLliga(String^ idLliga) {
            // Reutilitzem la consulta de CtrlVeureEstadistiquesLliga.
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            DataTable^ dt = gcnew DataTable();
            try {
                conn->Open();

                String^ disciplina = ObtenirDisciplinaLliga(idLliga);
                bool esFutbol = !String::IsNullOrEmpty(disciplina) && disciplina->Equals("Futbol", StringComparison::OrdinalIgnoreCase);
                String^ labelFavor = esFutbol ? "GF" : "PF";
                String^ labelContra = esFutbol ? "GC" : "PC";
                String^ labelDif = esFutbol ? "DG" : "DP";

                String^ query = "SELECT E.nom AS Equip, E.partitsJugats AS PJ, E.victories AS V, E.empats AS E, "
                    "E.derrotes AS D, E.golsAFavor AS " + labelFavor + ", E.golsEnContra AS " + labelContra + ", "
                    "E.diferenciaGols AS " + labelDif + ", E.punts AS Punts "
                    "FROM Equip E "
                    "INNER JOIN Temporada T ON E.idTemporada = T.idTemporada "
                    "WHERE T.idLliga = @idLliga "
                    "ORDER BY E.punts DESC, E.diferenciaGols DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }

        DataTable^ CtrlSeguirLliga::ObtenirProximsPartits(String^ idLliga, int limit) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DATE_FORMAT(p.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                    "COALESCE(el.nom, '(TBD)') AS Local, COALESCE(ev.nom, '(TBD)') AS Visitant, "
                    "p.ubicacio AS Ubicacio, p.estat AS Estat "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                    "LEFT JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "LEFT JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE t.idLliga = @idLliga AND p.estat = 'Pendent' "
                    "ORDER BY p.dataHora ASC "
                    "LIMIT " + limit;

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
             cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }

        DataTable^ CtrlSeguirLliga::ObtenirUltimsResultats(String^ idLliga, int limit) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ disciplina = ObtenirDisciplinaLliga(idLliga);
                bool esFutbol = !String::IsNullOrEmpty(disciplina) && disciplina->Equals("Futbol", StringComparison::OrdinalIgnoreCase);
                String^ labelLocal = esFutbol ? "Gols locals" : "Punts locals";
                String^ labelVisitant = esFutbol ? "Gols visitant" : "Punts visitant";

                String^ query =
                    "SELECT DATE_FORMAT(p.dataHora, '%d/%m/%Y %H:%i') AS DataHora, "
                 "COALESCE(el.nom, '(TBD)') AS Local, COALESCE(ev.nom, '(TBD)') AS Visitant, "
                    "p.golsLocal AS `" + labelLocal + "`, p.golsVisitant AS `" + labelVisitant + "` "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                   "INNER JOIN Temporada t ON j.idTemporada = t.idTemporada "
                    "LEFT JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "LEFT JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE t.idLliga = @idLliga AND p.estat = 'Finalitzat' "
                    "ORDER BY p.dataHora DESC "
                    "LIMIT " + limit;

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
             cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }

    }
}
