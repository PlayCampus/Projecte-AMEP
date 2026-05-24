#include "pch.h"
#include "PassarellaCapita.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;

namespace Playcampus {
    namespace Dades {

        PassarellaCapita::PassarellaCapita(String^ connStr) {
            connectionString = connStr;
        }

        void PassarellaCapita::DesassignarEquip(String^ idEquip) {

            MySqlConnection^ conn =
                gcnew MySqlConnection(connectionString);

            try {
                conn->Open();

                String^ sql =
                    "UPDATE Capita "
                    "SET idEquip = NULL "
                    "WHERE idEquip = @idEquip";

                MySqlCommand^ cmd =
                    gcnew MySqlCommand(sql, conn);

                cmd->Parameters->AddWithValue("@idEquip", idEquip);

                int files = cmd->ExecuteNonQuery();

            }
            finally {
                if (conn->State ==
                    System::Data::ConnectionState::Open) {
                    conn->Close();
                }
            }
        }

        void PassarellaCapita::AssignarEquip(String^ idCapita, String^ idEquip) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ queryUpdateCapita = "UPDATE Capita SET idEquip = @idEquip WHERE identificador = @idCapita";
                MySqlCommand^ cmd = gcnew MySqlCommand(queryUpdateCapita, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@idCapita", idCapita);
                int filesAfectades = cmd->ExecuteNonQuery();
                if (filesAfectades != 1) {
                    throw gcnew Exception("No s'ha pogut actualitzar el capita amb l'equip creat.");
                }

                String^ queryVerificacio = "SELECT COUNT(*) FROM Capita WHERE identificador = @idCapita AND idEquip = @idEquip";
                MySqlCommand^ cmdVerificacio = gcnew MySqlCommand(queryVerificacio, conn);
                cmdVerificacio->Parameters->AddWithValue("@idCapita", idCapita);
                cmdVerificacio->Parameters->AddWithValue("@idEquip", idEquip);
                int filesVerificades = Convert::ToInt32(cmdVerificacio->ExecuteScalar());
                if (filesVerificades != 1) {
                    throw gcnew Exception("La base de dades no ha confirmat l'assignacio de l'equip al capita.");
                }
            }
            finally {
                conn->Close();
            }
        }

    }
}