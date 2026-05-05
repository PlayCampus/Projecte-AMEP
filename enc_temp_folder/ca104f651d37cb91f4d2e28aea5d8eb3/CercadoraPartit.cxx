#include "pch.h"
#include "CercadoraPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        CercadoraPartit::CercadoraPartit(String^ connStr) {
            connectionString = connStr;
        }

        DataTable^ CercadoraPartit::ObtenirPartits() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idPartit, dataHora, ubicacio, estat, golsLocal, golsVisitant, idJornada, idEquipLocal, idEquipVisitant FROM Partit";
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(query, conn);
                da->Fill(dt);
                return dt;
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }
    }
}