#include "pch.h"
#include "PassarellaUsuari.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaUsuari::PassarellaUsuari(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaUsuari::PassarellaUsuari(String^ connStr, String^ id, String^ n, String^ pwd, DateTime d, String^ correu, String^ t) {
            connectionString = connStr;
            identificador = id;
            nom = n;
            contrasenya = pwd;
            dataRegistre = d;
            correuElectronic = correu;
            tipus = t;
        }

        String^ PassarellaUsuari::GetIdentificador() { return identificador; }
        String^ PassarellaUsuari::GetNom() { return nom; }
        String^ PassarellaUsuari::GetContrasenya() { return contrasenya; }
        DateTime PassarellaUsuari::GetDataRegistre() { return dataRegistre; }
        String^ PassarellaUsuari::GetCorreuElectronic() { return correuElectronic; }
        String^ PassarellaUsuari::GetTipus() { return tipus; }

        void PassarellaUsuari::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO Usuari (identificador, nom, contrasenya, data_registre, correu_electronic, Tipus) VALUES (@id, @nom, @pwd, @data, @correu, @tipus)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", identificador);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@pwd", contrasenya);
                cmd->Parameters->AddWithValue("@data", dataRegistre);
                cmd->Parameters->AddWithValue("@correu", correuElectronic);
                cmd->Parameters->AddWithValue("@tipus", tipus);
                cmd->ExecuteNonQuery();
                
                if (tipus == "Estudiant") {
                    String^ queryEstud = "INSERT INTO Estudiant (identificador, carrera) VALUES (@id, '')";
                    MySqlCommand^ cmdEst = gcnew MySqlCommand(queryEstud, conn);
                    cmdEst->Parameters->AddWithValue("@id", identificador);
                    cmdEst->ExecuteNonQuery();
                }
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
        }

        void PassarellaUsuari::Modifica() { }
        void PassarellaUsuari::Esborra() { }

        PassarellaUsuari^ PassarellaUsuari::LlegeixPerCorreu(String^ connStr, String^ correu) {
            PassarellaUsuari^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ query = "SELECT identificador, nom, contrasenya, data_registre, correu_electronic, Tipus FROM Usuari WHERE correu_electronic = @correu";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                
                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    String^ id = reader->GetString("identificador");
                    String^ nom = reader->GetString("nom");
                    String^ pwd = reader->GetString("contrasenya");
                    DateTime data = reader->GetDateTime("data_registre");
                    String^ corr = reader->GetString("correu_electronic");
                    String^ tipus = reader->GetString("Tipus");
                    resultat = gcnew PassarellaUsuari(connStr, id, nom, pwd, data, corr, tipus);
                }
                reader->Close();
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                conn->Close();
            }
            return resultat;
        }
    }
}
