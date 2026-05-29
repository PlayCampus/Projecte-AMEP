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

        int CercadoraUsuari::ObtenirIdUsuariPerCorreu(String^ correu) {
            int idUsuari = -1;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT identificador FROM Usuari WHERE correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idUsuari = Convert::ToInt32(resultat);
                }
            }
            finally {
                conn->Close();
            }
            return idUsuari;
        }

        String^ CercadoraUsuari::ObtenirIdUsuariStringPerCorreu(String^ correu) {
            String^ idUsuari = nullptr;
            int id = ObtenirIdUsuariPerCorreu(correu);
            if (id >= 0) {
                idUsuari = id.ToString();
            }
            return idUsuari;
        }

        String^ CercadoraUsuari::ObtenirTipusUsuariPerCorreu(String^ correu) {
            String^ tipus = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT Tipus FROM Usuari WHERE correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    tipus = resultat->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return tipus;
        }

        bool CercadoraUsuari::CapitaTeEquip(String^ correu) {
            bool teEquip = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT COUNT(*) FROM Capita C "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu AND C.idEquip IS NOT NULL AND C.idEquip <> ''";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                teEquip = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return teEquip;
        }

        bool CercadoraUsuari::EquipEstaEnLliga(String^ correu) {
            bool estaEnLliga = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT COUNT(*) FROM Capita C "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "INNER JOIN Equip E ON C.idEquip = E.idEquip "
                    "INNER JOIN EquipTemporada ET ON E.idEquip = ET.idEquip "
                    "WHERE U.correu_electronic = @correu";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correu);
                estaEnLliga = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return estaEnLliga;
        }

    }
}
