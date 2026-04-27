#include "pch.h"
#include "PassarellaConvocatoria.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaConvocatoria::PassarellaConvocatoria(String^ connStr) {
            connectionString = connStr;
        }

        void PassarellaConvocatoria::CrearConvocatoria(String^ idPartit, String^ idEquip) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ idConvocatoria = Guid::NewGuid().ToString();
                String^ query = "INSERT INTO Convocatoria (idConvocatoria, idPartit, idEquip) VALUES (@idConvocatoria, @idPartit, @idEquip)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idConvocatoria", idConvocatoria);
                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) delete conn;
            }
        }

        void PassarellaConvocatoria::AfegirJugadorConvocatoria(String^ idConvocatoria, String^ nomJugador) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO ConvocatoriaJugador (idConvocatoria, nomJugador, assistira) VALUES (@idConvocatoria, @nomJugador, NULL)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idConvocatoria", idConvocatoria);
                cmd->Parameters->AddWithValue("@nomJugador", nomJugador);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) delete conn;
            }
        }

        void PassarellaConvocatoria::ActualitzarDisponibilitatJugador(String^ idConvocatoria, String^ nomJugador, bool assistira) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE ConvocatoriaJugador SET assistira = @assistira WHERE idConvocatoria = @idConvocatoria AND nomJugador = @nomJugador";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idConvocatoria", idConvocatoria);
                cmd->Parameters->AddWithValue("@nomJugador", nomJugador);
                cmd->Parameters->AddWithValue("@assistira", assistira);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) delete conn;
            }
        }

        DataTable^ PassarellaConvocatoria::ObtenirConvocatoria(String^ idConvocatoria) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT nomJugador, assistira FROM ConvocatoriaJugador WHERE idConvocatoria = @idConvocatoria";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idConvocatoria", idConvocatoria);

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                da->Fill(dt);
                return dt;
            }
            finally {
                if (conn != nullptr) delete conn;
            }
        }
    }
}
