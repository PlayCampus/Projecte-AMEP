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
        List<Dictionary<String^, String^>^>^ CercadoraPartit::ObtenirPartitsPerJornada(String^ idJornada) {
            List<Dictionary<String^, String^>^>^ llista = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                String^ query = "SELECT idPartit, dataHora, ubicacio, estat "
                    "FROM Partit WHERE idJornada = @idJornada "
                    "ORDER BY dataHora ASC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idJornada", idJornada);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
                    partit["idPartit"] = reader["idPartit"]->ToString();
                    partit["dataHora"] = Convert::ToDateTime(reader["dataHora"]).ToString("dd/MM/yyyy HH:mm");
                    partit["ubicacio"] = reader["ubicacio"]->ToString();
                    partit["estat"] = reader["estat"]->ToString();
                    llista->Add(partit);
                }
            }
            finally {
                conn->Close();
            }

            return llista;
        }

    }
}