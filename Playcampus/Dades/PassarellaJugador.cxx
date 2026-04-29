#include "pch.h"
#include "PassarellaJugador.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaJugador::PassarellaJugador(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaJugador::PassarellaJugador(String^ connStr, String^ id, String^ n, int d, String^ p, DateTime dn) {
            connectionString = connStr;
            idJugador = id;
            nom = n;
            dorsal = d;
            posicio = p;
            dataNaixement = dn;
            partitsJugats = 0;
            anotacions = 0;
            assistencies = 0;
            faltesLleus = 0;
            faltesGreus = 0;
            minutsJugats = 0;
            idEquip = nullptr;
        }

        PassarellaJugador::PassarellaJugador(String^ connStr, String^ id, String^ n, int d, String^ p, DateTime dn, int pj, int a, int as, int fl, int fg, int mj, String^ ie) {
            connectionString = connStr;
            idJugador = id;
            nom = n;
            dorsal = d;
            posicio = p;
            dataNaixement = dn;
            partitsJugats = pj;
            anotacions = a;
            assistencies = as;
            faltesLleus = fl;
            faltesGreus = fg;
            minutsJugats = mj;
            idEquip = ie;
        }

        String^ PassarellaJugador::GetIdJugador() { return idJugador; }
        String^ PassarellaJugador::GetNom() { return nom; }
        int PassarellaJugador::GetDorsal() { return dorsal; }
        String^ PassarellaJugador::GetPosicio() { return posicio; }
        DateTime PassarellaJugador::GetDataNaixement() { return dataNaixement; }
        int PassarellaJugador::GetPartitsJugats() { return partitsJugats; }
        int PassarellaJugador::GetAnotacions() { return anotacions; }
        int PassarellaJugador::GetAssistencies() { return assistencies; }
        int PassarellaJugador::GetFaltesLleus() { return faltesLleus; }
        int PassarellaJugador::GetFaltesGreus() { return faltesGreus; }
        int PassarellaJugador::GetMinutsJugats() { return minutsJugats; }
        String^ PassarellaJugador::GetIdEquip() { return idEquip; }

        void PassarellaJugador::SetIdEquip(String^ ie) { idEquip = ie; }
        void PassarellaJugador::SetDorsal(int d) { dorsal = d; }

        void PassarellaJugador::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "INSERT INTO Jugador (idJugador, nom, dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip) VALUES (@id, @nom, @dorsal, @posicio, @data, @pj, @a, @as, @fl, @fg, @mj, @ie)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idJugador);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@dorsal", dorsal);
                cmd->Parameters->AddWithValue("@posicio", (posicio != nullptr) ? posicio : "");
                cmd->Parameters->AddWithValue("@data", dataNaixement);
                cmd->Parameters->AddWithValue("@pj", partitsJugats);
                cmd->Parameters->AddWithValue("@a", anotacions);
                cmd->Parameters->AddWithValue("@as", assistencies);
                cmd->Parameters->AddWithValue("@fl", faltesLleus);
                cmd->Parameters->AddWithValue("@fg", faltesGreus);
                cmd->Parameters->AddWithValue("@mj", minutsJugats);
                cmd->Parameters->AddWithValue("@ie", (idEquip != nullptr) ? (Object^)idEquip : (Object^)DBNull::Value);
                cmd->ExecuteNonQuery();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaJugador::Modifica() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "UPDATE Jugador SET nom = @nom, dorsal = @dorsal, posicio = @posicio, data_naixement = @data, partitsJugats = @pj, anotacions = @a, assistencies = @as, faltesLleus = @fl, faltesGreus = @fg, minutsJugats = @mj, idEquip = @ie WHERE idJugador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@dorsal", dorsal);
                cmd->Parameters->AddWithValue("@posicio", (posicio != nullptr) ? posicio : "");
                cmd->Parameters->AddWithValue("@data", dataNaixement);
                cmd->Parameters->AddWithValue("@pj", partitsJugats);
                cmd->Parameters->AddWithValue("@a", anotacions);
                cmd->Parameters->AddWithValue("@as", assistencies);
                cmd->Parameters->AddWithValue("@fl", faltesLleus);
                cmd->Parameters->AddWithValue("@fg", faltesGreus);
                cmd->Parameters->AddWithValue("@mj", minutsJugats);
                cmd->Parameters->AddWithValue("@ie", (idEquip != nullptr) ? (Object^)idEquip : (Object^)DBNull::Value);
                cmd->Parameters->AddWithValue("@id", idJugador);
                cmd->ExecuteNonQuery();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaJugador::Esborra() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "DELETE FROM Jugador WHERE idJugador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idJugador);
                cmd->ExecuteNonQuery();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
        }

        PassarellaJugador^ PassarellaJugador::Llegeix(String^ connStr, String^ idJ) {
            PassarellaJugador^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ query = "SELECT idJugador, nom, dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip FROM Jugador WHERE idJugador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idJ);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    String^ id = reader["idJugador"]->ToString();
                    String^ nom = reader->GetString("nom");
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

                    resultat = gcnew PassarellaJugador(connStr, id, nom, dorsal, posicio, data, pj, a, as, fl, fg, mj, ie);
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
    }
}
