#include "pch.h"
#include "PassarellaPartit.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
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
    }
}