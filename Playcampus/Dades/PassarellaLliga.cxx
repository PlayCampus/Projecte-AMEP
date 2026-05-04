#include "pch.h"
#include "PassarellaLliga.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaLliga::PassarellaLliga(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaLliga::PassarellaLliga(String^ connStr, String^ idLliga, String^ nom, Playcampus::Domini::Disciplina disciplina, String^ descripcio, String^ contrasenya, String^ idAdministrador) {
            connectionString = connStr;
            this->idLliga = idLliga;
            this->nom = nom;
            this->disciplina = disciplina;
            this->descripcio = descripcio;
            this->contrasenya = contrasenya;
            this->idAdministrador = idAdministrador;
        }

        String^ PassarellaLliga::GetIdLliga() { return idLliga; }
        String^ PassarellaLliga::GetNom() { return nom; }
        Playcampus::Domini::Disciplina PassarellaLliga::GetDisciplina() { return disciplina; }
        String^ PassarellaLliga::GetDescripcio() { return descripcio; }
        String^ PassarellaLliga::GetContrasenya() { return contrasenya; }
        String^ PassarellaLliga::GetIdAdministrador() { return idAdministrador; }

        void PassarellaLliga::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idLliga)) {
                    idLliga = Guid::NewGuid().ToString();
                }

                String^ query = "INSERT INTO Lliga (idLliga, nom, disciplina, descripcio, contrasenya, idAdministrador) VALUES (@idLliga, @nom, @disciplina, @descripcio, @contrasenya, @idAdministrador)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idLliga", idLliga);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@disciplina", disciplina.ToString());
                cmd->Parameters->AddWithValue("@descripcio", descripcio);

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

                String^ query = "SELECT COUNT(*) FROM Lliga WHERE idAdministrador = @idAdmin";
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

        bool PassarellaLliga::EsAdministradorLliga(System::String^ nomLliga, System::String^ correuAdmin)
        {
            bool esAdmin = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();

                // Fem un JOIN amb Usuari per poder comparar el correu electrònic amb l'idAdministrador guardat a Lliga
                String^ query = "SELECT COUNT(*) FROM Lliga L INNER JOIN Usuari U ON L.idAdministrador = U.identificador WHERE L.nom = @nom AND U.correu_electronic = @correuAdmin";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomLliga);
                cmd->Parameters->AddWithValue("@correuAdmin", correuAdmin);

                int count = Convert::ToInt32(cmd->ExecuteScalar());
                esAdmin = (count > 0);
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                }
            }

            return esAdmin;
        }

        String^ PassarellaLliga::ObtenirLligaActivaAdmin(String^ idAdmin) {
            MySql::Data::MySqlClient::MySqlConnection^ conn = gcnew MySql::Data::MySqlClient::MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE idAdministrador = @idAdmin LIMIT 1";
                MySql::Data::MySqlClient::MySqlCommand^ cmd = gcnew MySql::Data::MySqlClient::MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idAdmin", idAdmin);

                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr) {
                    return result->ToString();
                }
                return nullptr;
            }
            finally {
                conn->Close();
            }
        }

       
        String^ PassarellaLliga::ObtenirIdLligaPerNom(String^ nomLliga) {
            MySql::Data::MySqlClient::MySqlConnection^ conn = gcnew MySql::Data::MySqlClient::MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idLliga FROM Lliga WHERE nom = @nom LIMIT 1";
                MySql::Data::MySqlClient::MySqlCommand^ cmd = gcnew MySql::Data::MySqlClient::MySqlCommand(query, conn);
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
    }
}
