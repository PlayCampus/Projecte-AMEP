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

        PassarellaUsuari::PassarellaUsuari(String^ connStr, String^ n, String^ pwd, DateTime d, String^ correu, String^ t) {
            connectionString = connStr;
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
        String^ PassarellaUsuari::GetTelefon() { return telefon; }
        void PassarellaUsuari::SetTelefon(String^ tel) { telefon = tel; }

        void PassarellaUsuari::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "INSERT INTO Usuari (nom, contrasenya, data_registre, correu_electronic, Tipus) VALUES (@nom, @pwd, @data, @correu, @tipus)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@pwd", contrasenya);
                cmd->Parameters->AddWithValue("@data", dataRegistre);
                cmd->Parameters->AddWithValue("@correu", correuElectronic);
                cmd->Parameters->AddWithValue("@tipus", tipus);
                cmd->ExecuteNonQuery();

                long long lastId = cmd->LastInsertedId;
                identificador = lastId.ToString();

                if (tipus == "Estudiant") {
                    String^ queryEstud = "INSERT INTO Estudiant (identificador, carrera) VALUES (@id, '')";
                    MySqlCommand^ cmdEst = gcnew MySqlCommand(queryEstud, conn);
                    cmdEst->Parameters->AddWithValue("@id", lastId);
                    cmdEst->ExecuteNonQuery();
                }
                else if (tipus == "Administrador") {
                    String^ queryAdmin = "INSERT INTO Administrador (identificador, telefonContacte) VALUES (@id, @tel)";
                    MySqlCommand^ cmdAdm = gcnew MySqlCommand(queryAdmin, conn);
                    cmdAdm->Parameters->AddWithValue("@id", lastId);
                    cmdAdm->Parameters->AddWithValue("@tel", (telefon != nullptr) ? telefon : "");
                    cmdAdm->ExecuteNonQuery();
                }
                else if (tipus == "Capita") {
                    String^ queryCapita = "INSERT INTO Capita (identificador, telefonContacte, idEquip, validatPerAdmin) VALUES (@id, @tel, NULL, false)";
                    MySqlCommand^ cmdCap = gcnew MySqlCommand(queryCapita, conn);
                    cmdCap->Parameters->AddWithValue("@id", lastId);
                    cmdCap->Parameters->AddWithValue("@tel", (telefon != nullptr) ? telefon : "");
                    cmdCap->ExecuteNonQuery();
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

        void PassarellaUsuari::ActualitzaTipus(String^ nouTipus) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                String^ query = "UPDATE Usuari SET Tipus = @tipus WHERE identificador = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@tipus", nouTipus);
                cmd->Parameters->AddWithValue("@id", identificador);
                cmd->ExecuteNonQuery();

                tipus = nouTipus;
            }
            catch (Exception^ ex) {
                throw ex;
            }
            finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }
    }
}
