
#include "pch.h"
#include "CercadoraEquip.hxx"

using namespace MySql::Data::MySqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Dades {

        CercadoraEquip::CercadoraEquip(String^ connStr) {
            connectionString = connStr;
        }
        

        String^ CercadoraEquip::ObtenirIdEquipPerNom(String^ nomEquip) {
            String^ idEquip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Equip WHERE nom COLLATE utf8mb4_bin = @nom LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomEquip);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idEquip = resultat->ToString();
                }
            }
            finally {
                conn->Close();
            }
            return idEquip;
        }

        String^ CercadoraEquip::ObtenirIdEquipCapita(String^ correuCapita) {
            String^ idEquip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT C.idEquip FROM Capita C "
                    "INNER JOIN Usuari U ON C.identificador = U.identificador "
                    "WHERE U.correu_electronic = @correu LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@correu", correuCapita);
                Object^ resultat = cmd->ExecuteScalar();
                if (resultat != nullptr && resultat != DBNull::Value) {
                    idEquip = resultat->ToString()->Trim();
                }
            }
            finally {
                conn->Close();
            }
            return idEquip;
        }

        bool CercadoraEquip::ExisteixEquipPerId(String^ idEquip) {
            bool existeix = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                existeix = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return existeix;
        }

        bool CercadoraEquip::ExisteixEquipPerNom(String^ nomEquip) {
            bool existeix = false;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT COUNT(*) FROM Equip WHERE nom = @nomEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomEquip", nomEquip);
                existeix = Convert::ToInt32(cmd->ExecuteScalar()) > 0;
            }
            finally {
                conn->Close();
            }
            return existeix;
        }

        List<Dictionary<String^, String^>^>^ CercadoraEquip::ObtenirJugadorsEquip(String^ idEquip) {
            List<Dictionary<String^, String^>^>^ jugadors = gcnew List<Dictionary<String^, String^>^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT J.idJugador, U.nom, J.dorsal, J.posicio "
                    "FROM Jugador J "
                    "INNER JOIN Usuari U ON J.idJugador = U.identificador "
                    "WHERE J.idEquip = @idEquip "
                    "ORDER BY J.dorsal ASC, U.nom ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    Dictionary<String^, String^>^ jugador = gcnew Dictionary<String^, String^>();
                    jugador["idJugador"] = reader["idJugador"]->ToString();
                    jugador["nom"] = reader["nom"]->ToString();
                    jugador["dorsal"] = reader->IsDBNull(reader->GetOrdinal("dorsal")) ? "" : reader["dorsal"]->ToString();
                    jugador["posicio"] = reader->IsDBNull(reader->GetOrdinal("posicio")) ? "" : reader["posicio"]->ToString();
                    jugadors->Add(jugador);
                }
                reader->Close();
            }
            finally {
                conn->Close();
            }
            return jugadors;
        }

        DataTable^ CercadoraEquip::ObtenirPlantillaEquip(String^ idEquip) {
            DataTable^ dt = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query =
                    "SELECT j.idJugador AS IdJugador, u.nom AS Nom, j.dorsal AS Dorsal, j.posicio AS `Posició` "
                    "FROM Jugador j "
                    "INNER JOIN Usuari u ON j.idJugador = u.identificador "
                    "WHERE j.idEquip = @idEquip "
                    "ORDER BY j.dorsal ASC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(dt);
            }
            finally {
                conn->Close();
            }
            return dt;
        }

       

        static DataTable^ ExecutarConsultaEquipLocal(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            DataTable^ resultat = gcnew DataTable();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for (int i = 0; i < parametres->Length; i++) {
                        cmd->Parameters->Add(parametres[i]);
                    }
                }
                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                adapter->Fill(resultat);
            }
            finally {
                conn->Close();
            }
            return resultat;
        }

        static Object^ ExecutarEscalarEquipLocal(String^ connectionString, String^ consulta, cli::array<MySqlParameter^>^ parametres) {
            Object^ resultat = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                MySqlCommand^ cmd = gcnew MySqlCommand(consulta, conn);
                if (parametres != nullptr) {
                    for (int i = 0; i < parametres->Length; i++) {
                        cmd->Parameters->Add(parametres[i]);
                    }
                }
                resultat = cmd->ExecuteScalar();
            }
            finally {
                conn->Close();
            }
            return resultat;
        }

        static bool EquipTeColumnaLocal(String^ connectionString, String^ nomColumna) {
            String^ consulta =
                "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS "
                "WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Equip' AND COLUMN_NAME = @nomColumna";
            cli::array<MySqlParameter^>^ parametres = gcnew cli::array<MySqlParameter^>(1);
            parametres[0] = gcnew MySqlParameter("@nomColumna", nomColumna);
            Object^ resultat = ExecutarEscalarEquipLocal(connectionString, consulta, parametres);
            return resultat != nullptr && resultat != DBNull::Value && Convert::ToInt32(resultat) > 0;
        }


    }
}
