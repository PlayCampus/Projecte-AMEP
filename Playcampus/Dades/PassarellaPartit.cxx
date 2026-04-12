#include "pch.h"
#include "PassarellaPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaPartit::PassarellaPartit(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaPartit::PassarellaPartit(String^ connStr, String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada, String^ idEquipLocal, String^ idEquipVisitant) {
            connectionString = connStr;
            this->idPartit = idPartit;
            this->dataHora = dataHora;
            this->ubicacio = ubicacio;
            this->estat = estat;
            this->golsLocal = golsLocal;
            this->golsVisitant = golsVisitant;
            this->idJornada = idJornada;
            this->idEquipLocal = idEquipLocal;
            this->idEquipVisitant = idEquipVisitant;
        }

        String^ PassarellaPartit::GetIdPartit() { return idPartit; }
        DateTime PassarellaPartit::GetDataHora() { return dataHora; }
        String^ PassarellaPartit::GetUbicacio() { return ubicacio; }
        String^ PassarellaPartit::GetEstat() { return estat; }
        int PassarellaPartit::GetGolsLocal() { return golsLocal; }
        int PassarellaPartit::GetGolsVisitant() { return golsVisitant; }
        String^ PassarellaPartit::GetIdJornada() { return idJornada; }
        String^ PassarellaPartit::GetIdEquipLocal() { return idEquipLocal; }
        String^ PassarellaPartit::GetIdEquipVisitant() { return idEquipVisitant; }

        void PassarellaPartit::InsereixPartit() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idPartit)) {
                    idPartit = Guid::NewGuid().ToString();
                }

                String^ query = "INSERT INTO Partit (idPartit, dataHora, ubicacio, estat, golsLocal, golsVisitant, idJornada, idEquipLocal, idEquipVisitant) VALUES (@idPartit, @dataHora, @ubicacio, @estat, @golsLocal, @golsVisitant, @idJornada, @idEquipLocal, @idEquipVisitant)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idPartit", idPartit);
                cmd->Parameters->AddWithValue("@dataHora", dataHora);
                cmd->Parameters->AddWithValue("@ubicacio", ubicacio);
                cmd->Parameters->AddWithValue("@estat", estat);
                cmd->Parameters->AddWithValue("@golsLocal", golsLocal);
                cmd->Parameters->AddWithValue("@golsVisitant", golsVisitant);
                cmd->Parameters->AddWithValue("@idJornada", idJornada);
                cmd->Parameters->AddWithValue("@idEquipLocal", idEquipLocal);
                cmd->Parameters->AddWithValue("@idEquipVisitant", idEquipVisitant);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }
        
        DataTable^ PassarellaPartit::ObtenirPartits() {
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

        // Nuevo helper: busca la jornada por número y por id de liga
        int PassarellaPartit::buscarIdJornadaPorNumeroYLiga(int numero, int idLliga) {
            // Ejemplo con SQLite (ajustar nombres de variables/objeto DB)
            sqlite3_stmt* stmt = nullptr;
            const char* sql = "SELECT id FROM Jornada WHERE numero = ? AND liga_id = ? LIMIT 1;";
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                // manejar error según políticas del proyecto
                return -1;
            }
            sqlite3_bind_int(stmt, 1, numero);
            sqlite3_bind_int(stmt, 2, idLliga);
            int id = -1;
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                id = sqlite3_column_int(stmt, 0);
            }
            sqlite3_finalize(stmt);
            return id;
        }
    }
}