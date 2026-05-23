#include "pch.h"
#include "CercadoraUsuari.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        static DataTable^ ExecutaConsultaUsuaris(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            DataTable^ resultat = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for each (MySqlParameter^ p in parametres) {
                        cmd->Parameters->Add(p);
                    }
                }

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(resultat);
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }

            return resultat;
        }

        static Object^ ExecutaEscalarUsuaris(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            Object^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for each (MySqlParameter^ p in parametres) {
                        cmd->Parameters->Add(p);
                    }
                }

                resultat = cmd->ExecuteScalar();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }

            return resultat;
        }

        static bool EquipTeColumna(String^ connectionString, String^ nomColumna) {
            bool existeix = false;
            String^ consulta =
                "SELECT COUNT(*) "
                "FROM INFORMATION_SCHEMA.COLUMNS "
                "WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Equip' AND COLUMN_NAME = @nomColumna";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomColumna", nomColumna);

            Object^ resultat = ExecutaEscalarUsuaris(connectionString, consulta, parametres);
            if (resultat != nullptr && resultat != DBNull::Value) {
                existeix = Convert::ToInt32(resultat) > 0;
            }

            return existeix;
        }

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

        DataTable^ CercadoraUsuari::ObtenirTelefonsAdministradorPerCapita(String^ correuCapita) {
            bool equipTeIdTemporada = EquipTeColumna(connectionString, "idTemporada");
            String^ relacioLliga = equipTeIdTemporada
                ? "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                : "INNER JOIN Lliga L ON L.idLliga = E.idLliga ";

            String^ consulta =
                "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                "COALESCE(A.telefonContacte, '') AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                "FROM Usuari UC "
                "INNER JOIN Capita C ON C.identificador = UC.identificador "
                "INNER JOIN Equip E ON E.idEquip = C.idEquip ";
            consulta += relacioLliga;
            consulta +=
                "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                "WHERE UC.correu_electronic = @correuUsuari "
                "ORDER BY L.nom ASC, UA.nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuUsuari", correuCapita);

            return ExecutaConsultaUsuaris(connectionString, consulta, parametres);
        }

        DataTable^ CercadoraUsuari::ObtenirTelefonsContactePerJugador(String^ correuJugador) {
            bool equipTeIdTemporada = EquipTeColumna(connectionString, "idTemporada");
            String^ relacioLliga = equipTeIdTemporada
                ? "INNER JOIN Temporada T ON T.idTemporada = E.idTemporada INNER JOIN Lliga L ON L.idLliga = T.idLliga "
                : "INNER JOIN Lliga L ON L.idLliga = E.idLliga ";

            String^ consulta =
                "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                "COALESCE(C.telefonContacte, '') AS Telefon, E.nom AS Equip, '' AS Lliga "
                "FROM Usuari UJ "
                "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                "INNER JOIN Equip E ON E.idEquip = J.idEquip "
                "INNER JOIN Capita C ON C.idEquip = E.idEquip "
                "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                "WHERE UJ.correu_electronic = @correuUsuari "
                "UNION "
                "SELECT 'Administrador' AS Rol, UA.nom AS Nom, UA.correu_electronic AS Correu, "
                "COALESCE(A.telefonContacte, '') AS Telefon, E.nom AS Equip, L.nom AS Lliga "
                "FROM Usuari UJ "
                "INNER JOIN Jugador J ON J.idJugador = UJ.identificador "
                "INNER JOIN Equip E ON E.idEquip = J.idEquip ";
            consulta += relacioLliga;
            consulta +=
                "INNER JOIN Administrador A ON A.identificador = L.idAdministrador "
                "INNER JOIN Usuari UA ON UA.identificador = A.identificador "
                "WHERE UJ.correu_electronic = @correuUsuari "
                "ORDER BY Rol ASC, Nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuUsuari", correuJugador);

            return ExecutaConsultaUsuaris(connectionString, consulta, parametres);
        }

        DataTable^ CercadoraUsuari::ObtenirTelefonsCapitansPerAdministrador(String^ correuAdministrador) {
            bool equipTeIdTemporada = EquipTeColumna(connectionString, "idTemporada");
            String^ relacioLliga = equipTeIdTemporada
                ? "INNER JOIN Lliga L ON L.idAdministrador = ALogin.identificador INNER JOIN Temporada T ON T.idLliga = L.idLliga INNER JOIN Equip E ON E.idTemporada = T.idTemporada "
                : "INNER JOIN Lliga L ON L.idAdministrador = ALogin.identificador INNER JOIN Equip E ON E.idLliga = L.idLliga ";

            String^ consulta =
                "SELECT 'Capita' AS Rol, UC.nom AS Nom, UC.correu_electronic AS Correu, "
                "COALESCE(C.telefonContacte, '') AS Telefon, COALESCE(E.nom, '') AS Equip, "
                "COALESCE(L.nom, '') AS Lliga "
                "FROM Usuari UA "
                "INNER JOIN Administrador ALogin ON ALogin.identificador = UA.identificador ";
            consulta += relacioLliga;
            consulta +=
                "INNER JOIN Capita C ON C.idEquip = E.idEquip "
                "INNER JOIN Usuari UC ON UC.identificador = C.identificador "
                "WHERE UA.correu_electronic = @correuUsuari "
                "ORDER BY L.nom ASC, E.nom ASC, UC.nom ASC";

            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@correuUsuari", correuAdministrador);

            return ExecutaConsultaUsuaris(connectionString, consulta, parametres);
        }

    }
}
