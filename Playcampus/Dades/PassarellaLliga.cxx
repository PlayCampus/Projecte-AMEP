#include "pch.h"
#include "PassarellaLliga.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaLliga::PassarellaLliga(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaLliga::PassarellaLliga(String^ connStr, String^ idLliga, String^ nom, Playcampus::Domini::Disciplina disciplina, String^ descripcio, String^ estat, String^ contrasenya, String^ idAdministrador) {
            connectionString = connStr;
            this->idLliga = idLliga;
            this->nom = nom;
            this->disciplina = disciplina;
            this->descripcio = descripcio;
            this->estat = estat;
            this->contrasenya = contrasenya;
            this->idAdministrador = idAdministrador;
        }

        String^ PassarellaLliga::GetIdLliga() { return idLliga; }
        String^ PassarellaLliga::GetNom() { return nom; }
        Playcampus::Domini::Disciplina PassarellaLliga::GetDisciplina() { return disciplina; }
        String^ PassarellaLliga::GetDescripcio() { return descripcio; }
        String^ PassarellaLliga::GetEstat() { return estat; }
        String^ PassarellaLliga::GetContrasenya() { return contrasenya; }
        String^ PassarellaLliga::GetIdAdministrador() { return idAdministrador; }

        void PassarellaLliga::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idLliga)) {
                    idLliga = Guid::NewGuid().ToString();
                }

                String^ query = "INSERT INTO Lliga (idLliga, nom, disciplina, descripcio, estat, contrasenya, idAdministrador) VALUES (@idLliga, @nom, @disciplina, @descripcio, @estat, @contrasenya, @idAdministrador)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                
                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@disciplina", disciplina.ToString());
                cmd->Parameters->AddWithValue("@descripcio", descripcio);
                cmd->Parameters->AddWithValue("@estat", estat);

                if (String::IsNullOrEmpty(contrasenya)) {
                    cmd->Parameters->AddWithValue("@contrasenya", DBNull::Value);
                } else {
                    cmd->Parameters->AddWithValue("@contrasenya", contrasenya);
                }

                if (String::IsNullOrEmpty(idAdministrador)) {
                    cmd->Parameters->AddWithValue("@idAdministrador", DBNull::Value);
                } else {
                    cmd->Parameters->AddWithValue("@idAdministrador", idAdministrador);
                }

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }
        bool PassarellaLliga::ExisteixPerNom(String^ nomLliga) {
            bool existeix = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();

                String^ query = "SELECT COUNT(*) FROM Lliga WHERE nom = @nom";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomLliga);

                int count = Convert::ToInt32(cmd->ExecuteScalar());
                existeix = (count > 0);
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }

            return existeix;
        }

        bool PassarellaLliga::TeLligaActivaAdmin(String^ idAdmin) {
            bool teActiva = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();

                String^ query = "SELECT COUNT(*) FROM Lliga WHERE idAdministrador = @idAdmin AND estat = 'en_curs'";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idAdmin", idAdmin);

                int count = Convert::ToInt32(cmd->ExecuteScalar());
                teActiva = (count > 0);
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }

            return teActiva;
        }
    }
}
