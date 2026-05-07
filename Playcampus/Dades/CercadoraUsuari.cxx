#include "pch.h"
#include "CercadoraUsuari.hxx"

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        CercadoraUsuari::CercadoraUsuari(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaUsuari^ CercadoraUsuari::LlegeixPerCorreu(String^ correu) {
            PassarellaUsuari^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT identificador, nom, contrasenya, data_registre, correu_electronic, Tipus FROM Usuari WHERE correu_electronic = @correu";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    String^ id = reader["identificador"]->ToString();
                    String^ nom = reader->GetString("nom");
                    String^ pwd = reader->GetString("contrasenya");
                    DateTime data = reader->GetDateTime("data_registre");
                    String^ corr = reader->GetString("correu_electronic");
                    String^ tipus = reader->GetString("Tipus");
                    resultat = gcnew PassarellaUsuari(connectionString, id, nom, pwd, data, corr, tipus);
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

        PassarellaUsuari^ CercadoraUsuari::LlegeixPerNomUsuari(String^ nomUsuari) {
            PassarellaUsuari^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT identificador, nom, contrasenya, data_registre, correu_electronic, Tipus FROM Usuari WHERE nom = @nom";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomUsuari);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    String^ id = reader["identificador"]->ToString();
                    String^ nom = reader->GetString("nom");
                    String^ pwd = reader->GetString("contrasenya");
                    DateTime data = reader->GetDateTime("data_registre");
                    String^ corr = reader->GetString("correu_electronic");
                    String^ tipus = reader->GetString("Tipus");
                    resultat = gcnew PassarellaUsuari(connectionString, id, nom, pwd, data, corr, tipus);
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
