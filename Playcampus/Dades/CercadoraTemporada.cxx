#include "pch.h"
#include "CercadoraTemporada.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {

        CercadoraTemporada::CercadoraTemporada(String^ connStr) {
            connectionString = connStr;
        }

        List<Dictionary<String^, String^>^>^ CercadoraTemporada::ObtenirTemporadesAdmin(String^ correuAdmin) {

            // ACTUALITZEM ESTATS ABANS DE CONSULTAR
            PassarellaTemporada::ActualitzarEstats(connectionString);


            List<Dictionary<String^, String^>^>^ llista = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                String^ query = "SELECT t.idTemporada, t.dataInici, t.dataFi, t.estat "
                    "FROM Temporada t "
                    "INNER JOIN Lliga ll ON t.idLliga = ll.idLliga "
                    "INNER JOIN Usuari u ON ll.idAdministrador = u.identificador "
                    "WHERE u.correu_electronic = @correuAdmin";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ temp = gcnew Dictionary<String^, String^>();
                    temp["idTemporada"] = reader["idTemporada"]->ToString();
                    temp["dataInici"] = Convert::ToDateTime(reader["dataInici"]).ToString("dd/MM/yyyy HH:mm");
                    temp["dataFi"] = Convert::ToDateTime(reader["dataFi"]).ToString("dd/MM/yyyy HH:mm");
                    temp["estat"] = reader["estat"]->ToString();
                    llista->Add(temp);
                }
            }
            finally {
                conn->Close();
            }

            return llista;
        }

        String^ CercadoraTemporada::ObtenirIdTemporadaEnCurs(String^ idLliga) {
            PassarellaTemporada::ActualitzarEstats(connectionString);

            String^ idTemporada = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idTemporada FROM Temporada WHERE idLliga = @idLliga AND estat = 'EnCurs'";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr) {
                    idTemporada = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idTemporada;

        }

        DataTable^ CercadoraTemporada::ObtenirTemporadesLliga(String^ idLliga) {
            PassarellaTemporada::ActualitzarEstats(connectionString);
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idTemporada, dataInici, dataFi FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return dt;
        }

        String^ CercadoraTemporada::ObtenirIdTemporadaRellevant(String^ idLliga) {
            PassarellaTemporada::ActualitzarEstats(connectionString);
            String^ idTemporada = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query =
                    "SELECT idTemporada FROM Temporada "
                    "WHERE idLliga = @idLliga "
                    "ORDER BY CASE "
                    "WHEN estat = 'EnCurs' THEN 0 "
                    "WHEN estat <> 'Finalitzat' THEN 1 "
                    "ELSE 2 END, dataInici DESC, dataFi DESC "
                    "LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    idTemporada = result->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idTemporada;
        }

        DataTable^ CercadoraTemporada::ObtenirTemporadesLligaEstadistiques(String^ idLliga) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT idTemporada, CONCAT('Temporada ', DATE_FORMAT(dataInici, '%Y'), '-', DATE_FORMAT(dataFi, '%Y')) AS NomTemporada "
                    "FROM Temporada WHERE idLliga = @idLliga ORDER BY dataInici DESC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

        Dictionary<String^, String^>^ CercadoraTemporada::ObtenirTemporadaPerId(String^ idTemporada) {
            Dictionary<String^, String^>^ temporada = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idTemporada, dataInici, dataFi, estat FROM Temporada WHERE idTemporada = @idTemporada LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    temporada = gcnew Dictionary<String^, String^>();
                    temporada["idTemporada"] = reader["idTemporada"]->ToString();
                    temporada["dataInici"] = Convert::ToDateTime(reader["dataInici"]).ToString("yyyy-MM-dd HH:mm:ss");
                    temporada["dataFi"] = Convert::ToDateTime(reader["dataFi"]).ToString("yyyy-MM-dd HH:mm:ss");
                    temporada["estat"] = reader["estat"]->ToString();
                }
                reader->Close();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return temporada;
        }

    }
}
