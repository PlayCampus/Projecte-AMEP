#include "pch.h"
#include "CercadoraJugador.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        CercadoraJugador::CercadoraJugador(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaJugador^ CercadoraJugador::LlegeixPerEquip(String^ idEquip) {
            PassarellaJugador^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip FROM Jugador WHERE idEquip = @ie LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@ie", idEquip);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    int dorsal = reader->GetInt32("dorsal");
                    String^ posicio = reader->IsDBNull(reader->GetOrdinal("posicio")) ? "" : reader->GetString("posicio");
                    DateTime data = reader->GetDateTime("data_naixement");
                    int pj = reader->GetInt32("partitsJugats");
                    int a = reader->GetInt32("anotacions");
                    int as = reader->GetInt32("assistencies");
                    int fl = reader->GetInt32("faltesLleus");
                    int fg = reader->GetInt32("faltesGreus");
                    int mj = reader->GetInt32("minutsJugats");
                    String^ ie = reader->IsDBNull(reader->GetOrdinal("idEquip")) ? nullptr : reader->GetString("idEquip");

                    resultat = gcnew PassarellaJugador(connectionString, dorsal, posicio, data, pj, a, as, fl, fg, mj, ie);
                }
                reader->Close();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
            return resultat;
        }

        PassarellaJugador^ CercadoraJugador::LlegeixPerDorsalEquip(int dorsal, String^ idEquip) {
            PassarellaJugador^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip FROM Jugador WHERE dorsal = @dorsal AND idEquip = @ie";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@dorsal", dorsal);
                cmd->Parameters->AddWithValue("@ie", idEquip);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    int d = reader->GetInt32("dorsal");
                    String^ posicio = reader->IsDBNull(reader->GetOrdinal("posicio")) ? "" : reader->GetString("posicio");
                    DateTime data = reader->GetDateTime("data_naixement");
                    int pj = reader->GetInt32("partitsJugats");
                    int a = reader->GetInt32("anotacions");
                    int as = reader->GetInt32("assistencies");
                    int fl = reader->GetInt32("faltesLleus");
                    int fg = reader->GetInt32("faltesGreus");
                    int mj = reader->GetInt32("minutsJugats");
                    String^ ie = reader->IsDBNull(reader->GetOrdinal("idEquip")) ? nullptr : reader->GetString("idEquip");

                    resultat = gcnew PassarellaJugador(connectionString, d, posicio, data, pj, a, as, fl, fg, mj, ie);
                }
                reader->Close();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
            return resultat;
        }

        List<PassarellaJugador^>^ CercadoraJugador::LlegeixTsPerEquip(String^ idEquip) {
            List<PassarellaJugador^>^ resultats = gcnew List<PassarellaJugador^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idJugador, dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip FROM Jugador WHERE idEquip = @ie";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@ie", idEquip);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    int idJugadorInt = reader->GetInt32("idJugador");
                    String^ idJugador = idJugadorInt.ToString();
                    int dorsal = reader->GetInt32("dorsal");
                    String^ posicio = reader->IsDBNull(reader->GetOrdinal("posicio")) ? "" : reader->GetString("posicio");
                    DateTime data = reader->GetDateTime("data_naixement");
                    int pj = reader->GetInt32("partitsJugats");
                    int a = reader->GetInt32("anotacions");
                    int as = reader->GetInt32("assistencies");
                    int fl = reader->GetInt32("faltesLleus");
                    int fg = reader->GetInt32("faltesGreus");
                    int mj = reader->GetInt32("minutsJugats");
                    String^ ie = reader->IsDBNull(reader->GetOrdinal("idEquip")) ? nullptr : reader->GetString("idEquip");

                    PassarellaJugador^ jugador = gcnew PassarellaJugador(connectionString, dorsal, posicio, data, pj, a, as, fl, fg, mj, ie);
                    resultats->Add(jugador);
                }
                reader->Close();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
            return resultats;
        }

        bool CercadoraJugador::ExisteixDorsalEnEquip(int dorsal, String^ idEquip) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM Jugador WHERE dorsal = @dorsal AND idEquip = @ie";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@dorsal", dorsal);
                cmd->Parameters->AddWithValue("@ie", idEquip);

                Object^ resultat = cmd->ExecuteScalar();
                int count = Convert::ToInt32(resultat);
                return count > 0;
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
        }

        bool CercadoraJugador::JugadorPertanyAEquip(String^ idJugador, String^ idEquip) {
            bool pertany = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                pertany = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return pertany;
        }

        bool CercadoraJugador::JugadorPertanyAEquipDelCapita(String^ correuCapita, String^ idJugador) {
            bool pertany = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT COUNT(*) "
                    "FROM Jugador J "
                    "INNER JOIN Capita C ON J.idEquip = C.idEquip "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correuCapita AND J.idJugador = @idJugador";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correuCapita", correuCapita);
                cmd->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                pertany = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return pertany;
        }

        DataTable^ CercadoraJugador::ObtenirEstadistiquesJugador(String^ idJugador) {
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
                conn->Close();
            }
            return dt;
        }

        DataTable^ CercadoraJugador::ObtenirUltimsFitxatges(int limit) {
            if (limit <= 0) limit = 10;
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT DATE_FORMAT(J.data_naixement, '%d/%m/%Y') AS Data, "
                    "U.nom AS Jugador, "
                    "COALESCE(E.nom, '(Sense equip)') AS Equip, "
                    "COALESCE(E.esport, '') AS Esport "
                    "FROM Jugador J "
                    "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                    "LEFT JOIN Equip E ON J.idEquip = E.idEquip "
                    "WHERE J.idEquip IS NOT NULL "
                    "ORDER BY J.data_naixement DESC, J.idJugador DESC "
                    "LIMIT " + limit.ToString();
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
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
