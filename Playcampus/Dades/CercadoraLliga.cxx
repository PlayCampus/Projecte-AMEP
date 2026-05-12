#include "pch.h"
#include "CercadoraLliga.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        CercadoraLliga::CercadoraLliga(String^ connStr) {
            connectionString = connStr;
        }


        String^ CercadoraLliga::ObtenirLligaActivaAdmin(String^ idAdmin) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE idAdministrador = @idAdmin LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idAdmin", idAdmin);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    return result->ToString();
                }
                return nullptr;
            }
            finally {
                conn->Close();
            }
        }

        String^ CercadoraLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nom LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomLliga);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr && result != DBNull::Value) {
                    return result->ToString();
                }
                return nullptr;
            }
            finally {
                conn->Close();
            }
        }

        DataTable^ CercadoraLliga::ObtenirTotesLligues() {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT identificador AS idLliga, nom FROM Lliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
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