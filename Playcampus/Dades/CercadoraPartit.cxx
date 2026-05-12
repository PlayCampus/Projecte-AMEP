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
                String^ query = "SELECT p.idPartit, p.dataHora, p.ubicacio, p.estat, "
                    "el.Nom AS equipLocal, ev.Nom AS equipVisitant "
                    "FROM Partit p "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE p.idJornada = @idJornada "
                    "ORDER BY p.dataHora ASC";


                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idJornada", idJornada);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ partit = gcnew Dictionary<String^, String^>();
                    partit["idPartit"] = reader["idPartit"]->ToString();
                    partit["dataHora"] = Convert::ToDateTime(reader["dataHora"]).ToString("dd/MM/yyyy HH:mm");
                    partit["ubicacio"] = reader["ubicacio"]->ToString();
                    partit["estat"] = reader["estat"]->ToString();
                    partit["equipLocal"] = reader["equipLocal"]->ToString();
                    partit["equipVisitant"] = reader["equipVisitant"]->ToString();
                    llista->Add(partit);
                }
            }
            finally {
                conn->Close();
            }

            return llista;
        }

        DataTable^ CercadoraPartit::ObtenirPartitsFinalitzatsPerTemporada(String^ idTemporada) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Hacemos JOIN con Jornada para filtrar por temporada, y con Equip para sacar los nombres. Filtramos por estado 'Finalitzat'
                String^ query =
                    "SELECT p.idPartit, el.nom AS EquipLocal, ev.nom AS EquipVisitant "
                    "FROM Partit p "
                    "INNER JOIN Jornada j ON p.idJornada = j.idJornada "
                    "INNER JOIN Equip el ON p.idEquipLocal = el.idEquip "
                    "INNER JOIN Equip ev ON p.idEquipVisitant = ev.idEquip "
                    "WHERE j.idTemporada = @idTemporada AND p.estat = 'Finalitzat' "
                    "ORDER BY p.dataHora DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
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
