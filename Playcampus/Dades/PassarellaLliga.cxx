#include "pch.h"
#include "PassarellaLliga.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaLliga::PassarellaLliga(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaLliga::PassarellaLliga(String^ connStr, String^ idLliga, String^ nom, Playcampus::Domini::Disciplina disciplina, String^ descripcio, String^ estat, String^ contrasenya) {
            connectionString = connStr;
            this->idLliga = idLliga;
            this->nom = nom;
            this->disciplina = disciplina;
            this->descripcio = descripcio;
            this->estat = estat;
            this->contrasenya = contrasenya;
        }

        String^ PassarellaLliga::GetIdLliga() { return idLliga; }
        String^ PassarellaLliga::GetNom() { return nom; }
        Playcampus::Domini::Disciplina PassarellaLliga::GetDisciplina() { return disciplina; }
        String^ PassarellaLliga::GetDescripcio() { return descripcio; }
        String^ PassarellaLliga::GetEstat() { return estat; }
        String^ PassarellaLliga::GetContrasenya() { return contrasenya; }

        void PassarellaLliga::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idLliga)) {
                    idLliga = Guid::NewGuid().ToString();
                }

                String^ query = "INSERT INTO Lliga (idLliga, nom, disciplina, descripcio, estat, contrasenya) VALUES (@idLliga, @nom, @disciplina, @descripcio, @estat, @contrasenya)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@disciplina", disciplina.ToString());
                cmd->Parameters->AddWithValue("@descripcio", descripcio);
                cmd->Parameters->AddWithValue("@estat", estat);
                cmd->Parameters->AddWithValue("@contrasenya", contrasenya);

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
