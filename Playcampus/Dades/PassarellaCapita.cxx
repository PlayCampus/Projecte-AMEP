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
    }
}