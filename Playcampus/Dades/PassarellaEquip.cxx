#include "pch.h"
#include "PassarellaEquip.hxx"

using namespace System::Collections::Generic;
using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        PassarellaEquip::PassarellaEquip(String^ connStr) {
            connectionString = connStr;
        }

        PassarellaEquip::PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport) {
            connectionString = connStr;
            this->idEquip = idEquip;
            this->nom = nom;
            this->dataFundacio = dataFundacio;
            this->esport = esport;
        }

        String^ PassarellaEquip::GetIdEquip() { return idEquip; }
        String^ PassarellaEquip::GetNom() { return nom; }
        DateTime PassarellaEquip::GetDataFundacio() { return dataFundacio; }
        String^ PassarellaEquip::GetEsport() { return esport; }

        void PassarellaEquip::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO Equip (idEquip, nom, dataFundacio, esport) VALUES (@id, @nom, @data, @esport)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@id", idEquip);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@data", dataFundacio);
                cmd->Parameters->AddWithValue("@esport", esport);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }

        void PassarellaEquip::Modifica() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE Equip SET nom = @nom, dataFundacio = @data, esport = @esport WHERE idEquip = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@data", dataFundacio);
                cmd->Parameters->AddWithValue("@esport", esport);
                cmd->Parameters->AddWithValue("@id", idEquip);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }

        void PassarellaEquip::Esborra() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "DELETE FROM Equip WHERE idEquip = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idEquip);
                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }

        PassarellaEquip^ PassarellaEquip::Llegeix(String^ connStr, String^ idEq) {
            PassarellaEquip^ equip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ query = "SELECT idEquip, nom, dataFundacio, esport FROM Equip WHERE idEquip = @id";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idEq);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    String^ nom = reader["nom"]->ToString();
                    DateTime dataFundacio = Convert::ToDateTime(reader["dataFundacio"]);
                    String^ esport = reader["esport"]->ToString();

                    equip = gcnew PassarellaEquip(connStr, idEq, nom, dataFundacio, esport);
                }
                reader->Close();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return equip;
        }

        List<String^>^ PassarellaEquip::ObtenirNomsEquipsPerTemporada(String^ idTemporada) {
            List<String^>^ llista = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Usamos INNER JOIN con la tabla EquipTemporada para encontrar los que juegan esa temporada
                String^ query = "SELECT e.nom FROM Equip e "
                    "INNER JOIN EquipTemporada et ON e.idEquip = et.idEquip "
                    "WHERE et.idTemporada = @id";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@id", idTemporada);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    llista->Add(reader["nom"]->ToString());
                }
                reader->Close();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return llista;
        }

        void PassarellaEquip::TreureDeLaLligaSiAdmin(String^ idEquip, String^ correuAdmin) {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Eliminamos su inscripción de EquipTemporada comprobando que el admin coincide
                String^ query = "DELETE FROM EquipTemporada "
                    "WHERE idEquip = @idEquip AND idTemporada IN ("
                    "   SELECT t.idTemporada FROM Temporada t "
                    "   INNER JOIN Lliga ll ON t.idLliga = ll.idLliga "
                    "   INNER JOIN Usuari u ON ll.idAdministrador = u.identificador "
                    "   WHERE u.correu_electronic = @admin"
                    ")";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@admin", correuAdmin);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
        }

        
    }
}

