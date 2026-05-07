#include "pch.h"
#include "CercadoraJugador.hxx"

using namespace System;
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
    }
}
