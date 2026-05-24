#include "pch.h"
#include "PassarellaJugador.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaJugador::PassarellaJugador(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaJugador::PassarellaJugador(String^ connStr, int d, String^ p, DateTime dn) {
            connectionString = connStr;
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

        PassarellaJugador::PassarellaJugador(String^ connStr, int d, String^ p, DateTime dn, int pj, int a, int as, int fl, int fg, int mj, String^ ie) {
            connectionString = connStr;
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

        void PassarellaJugador::Insereix(String^ idJugador) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "INSERT INTO Jugador (idJugador, dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip) VALUES (@id, @dorsal, @posicio, @data, @pj, @a, @as, @fl, @fg, @mj, @ie)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                int idJugadorInt = Convert::ToInt32(idJugador);
                cmd->Parameters->AddWithValue("@id", idJugadorInt);
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

        void PassarellaJugador::Modifica(String^ idJugador) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "UPDATE Jugador SET dorsal = @dorsal, posicio = @posicio, data_naixement = @data, partitsJugats = @pj, anotacions = @a, assistencies = @as, faltesLleus = @fl, faltesGreus = @fg, minutsJugats = @mj, idEquip = @ie WHERE idJugador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
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
                int idJugadorInt = Convert::ToInt32(idJugador);
                cmd->Parameters->AddWithValue("@id", idJugadorInt);
                cmd->ExecuteNonQuery();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }

        void PassarellaJugador::Esborra(String^ idJugador) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "DELETE FROM Jugador WHERE idJugador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                int idJugadorInt = Convert::ToInt32(idJugador);
                cmd->Parameters->AddWithValue("@id", idJugadorInt);
                cmd->ExecuteNonQuery();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }

        PassarellaJugador^ PassarellaJugador::Llegeix(String^ connStr, String^ idJ) {
            PassarellaJugador^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ query = "SELECT dorsal, posicio, data_naixement, partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus, minutsJugats, idEquip FROM Jugador WHERE idJugador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                int idJInt = Convert::ToInt32(idJ);
                cmd->Parameters->AddWithValue("@id", idJInt);

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

                    resultat = gcnew PassarellaJugador(connStr, dorsal, posicio, data, pj, a, as, fl, fg, mj, ie);
                }
                reader->Close();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return resultat;
        }

        void PassarellaJugador::ActualitzarDorsalIPosicio(String^ idJugador, int dorsalNou, String^ posicioNova) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE Jugador SET dorsal = @dorsal, posicio = @posicio WHERE idJugador = @idJugador";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@dorsal", dorsalNou);
                cmd->Parameters->AddWithValue("@posicio", posicioNova);
                cmd->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmd->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaJugador::EliminarJugadorDeEquip(String^ idJugador, String^ idEquip) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "DELETE FROM Jugador WHERE idJugador = @idJugador AND idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                int files = cmd->ExecuteNonQuery();
                if (files <= 0) {
                    throw gcnew Exception("No s'ha pogut eliminar el jugador de l'equip.");
                }
            }
            finally {
                conn->Close();
            }
        }


        void PassarellaJugador::ExpulsarJugadorDeEquip(String^ idJugador, String^ idEquip) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ queryUpdate = "UPDATE Jugador SET idEquip = NULL WHERE idJugador = @idJugador AND idEquip = @idEquip";
                MySqlCommand^ cmdUpdate = gcnew MySqlCommand(queryUpdate, conn);
                cmdUpdate->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmdUpdate->Parameters->AddWithValue("@idEquip", idEquip);

                int files = cmdUpdate->ExecuteNonQuery();
                if (files != 1) {
                    throw gcnew Exception("No s'ha pogut expulsar el jugador de l'equip.");
                }

                String^ queryUsuari = "UPDATE Usuari SET Tipus = 'Estudiant' WHERE identificador = @idJugador";
                MySqlCommand^ cmdUsuari = gcnew MySqlCommand(queryUsuari, conn);
                cmdUsuari->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmdUsuari->ExecuteNonQuery();

                String^ queryBorrarJugador = "DELETE FROM Jugador WHERE idJugador = @idJugador AND idEquip IS NULL";
                MySqlCommand^ cmdBorrarJugador = gcnew MySqlCommand(queryBorrarJugador, conn);
                cmdBorrarJugador->Parameters->AddWithValue("@idJugador", Convert::ToInt32(idJugador));
                cmdBorrarJugador->ExecuteNonQuery();
            }
            finally {
                conn->Close();
            }
        }

    }
}
