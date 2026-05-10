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
            this->partitsJugats = 0;
            this->victories = 0;
            this->derrotes = 0;
            this->empats = 0;
            this->punts = 0;
            this->golsAFavor = 0;
            this->golsEnContra = 0;
            this->diferenciaGols = 0;
            this->posicioClassificacio = 0;
            this->idTemporada = nullptr;
        }

        PassarellaEquip::PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio, String^ idTemporada) {
            connectionString = connStr;
            this->idEquip = idEquip;
            this->nom = nom;
            this->dataFundacio = dataFundacio;
            this->esport = esport;
            this->partitsJugats = partitsJugats;
            this->victories = victories;
            this->derrotes = derrotes;
            this->empats = empats;
            this->punts = punts;
            this->golsAFavor = golsAFavor;
            this->golsEnContra = golsEnContra;
            this->diferenciaGols = diferenciaGols;
            this->posicioClassificacio = posicioClassificacio;
            this->idTemporada = idTemporada;
        }

        String^ PassarellaEquip::GetIdEquip() { return idEquip; }
        String^ PassarellaEquip::GetNom() { return nom; }
        DateTime PassarellaEquip::GetDataFundacio() { return dataFundacio; }
        String^ PassarellaEquip::GetEsport() { return esport; }

        unsigned int PassarellaEquip::GetPartitsJugats() { return partitsJugats; }
        unsigned int PassarellaEquip::GetVictories() { return victories; }
        unsigned int PassarellaEquip::GetDerrotes() { return derrotes; }
        unsigned int PassarellaEquip::GetEmpats() { return empats; }
        unsigned int PassarellaEquip::GetPunts() { return punts; }
        unsigned int PassarellaEquip::GetGolsAFavor() { return golsAFavor; }
        unsigned int PassarellaEquip::GetGolsEnContra() { return golsEnContra; }
        int PassarellaEquip::GetDiferenciaGols() { return diferenciaGols; }
        int PassarellaEquip::GetPosicioClassificacio() { return posicioClassificacio; }
        String^ PassarellaEquip::GetIdTemporada() { return idTemporada; }

        void PassarellaEquip::SetIdTemporada(String^ nouIdTemporada) { idTemporada = nouIdTemporada; }

        void PassarellaEquip::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idEquip)) {
                    idEquip = Guid::NewGuid().ToString();
                }

                String^ query = "INSERT INTO Equip (idEquip, nom, dataFundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio, idTemporada) VALUES (@idEquip, @nom, @dataFundacio, @esport, @partitsJugats, @victories, @derrotes, @empats, @punts, @golsAFavor, @golsEnContra, @diferenciaGols, @posicioClassificacio, @idTemporada)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@dataFundacio", dataFundacio);
                cmd->Parameters->AddWithValue("@esport", esport);
                cmd->Parameters->AddWithValue("@partitsJugats", partitsJugats);
                cmd->Parameters->AddWithValue("@victories", victories);
                cmd->Parameters->AddWithValue("@derrotes", derrotes);
                cmd->Parameters->AddWithValue("@empats", empats);
                cmd->Parameters->AddWithValue("@punts", punts);
                cmd->Parameters->AddWithValue("@golsAFavor", golsAFavor);
                cmd->Parameters->AddWithValue("@golsEnContra", golsEnContra);
                cmd->Parameters->AddWithValue("@diferenciaGols", diferenciaGols);
                cmd->Parameters->AddWithValue("@posicioClassificacio", posicioClassificacio);
                if (String::IsNullOrEmpty(idTemporada)) {
                    cmd->Parameters->AddWithValue("@idTemporada", DBNull::Value);
                } else {
                    cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                }

                int filesAfectades = cmd->ExecuteNonQuery();
                if (filesAfectades != 1) {
                    throw gcnew Exception("No s'ha inserit cap equip a la base de dades.");
                }

                String^ queryVerificacio = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip";
                MySqlCommand^ cmdVerificacio = gcnew MySqlCommand(queryVerificacio, conn);
                cmdVerificacio->Parameters->AddWithValue("@idEquip", idEquip);
                int filesVerificades = Convert::ToInt32(cmdVerificacio->ExecuteScalar());
                if (filesVerificades != 1) {
                    throw gcnew Exception("La base de dades no ha confirmat la inserció de l'equip.");
                }
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }

        void PassarellaEquip::Modifica() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE Equip SET nom=@nom, dataFundacio=@dataFundacio, esport=@esport, partitsJugats=@partitsJugats, victories=@victories, derrotes=@derrotes, empats=@empats, punts=@punts, golsAFavor=@golsAFavor, golsEnContra=@golsEnContra, diferenciaGols=@diferenciaGols, posicioClassificacio=@posicioClassificacio, idTemporada=@idTemporada WHERE idEquip=@idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@nom", nom);
                cmd->Parameters->AddWithValue("@dataFundacio", dataFundacio);
                cmd->Parameters->AddWithValue("@esport", esport);
                cmd->Parameters->AddWithValue("@partitsJugats", partitsJugats);
                cmd->Parameters->AddWithValue("@victories", victories);
                cmd->Parameters->AddWithValue("@derrotes", derrotes);
                cmd->Parameters->AddWithValue("@empats", empats);
                cmd->Parameters->AddWithValue("@punts", punts);
                cmd->Parameters->AddWithValue("@golsAFavor", golsAFavor);
                cmd->Parameters->AddWithValue("@golsEnContra", golsEnContra);
                cmd->Parameters->AddWithValue("@diferenciaGols", diferenciaGols);
                cmd->Parameters->AddWithValue("@posicioClassificacio", posicioClassificacio);

                if (String::IsNullOrEmpty(idTemporada)) {
                    cmd->Parameters->AddWithValue("@idTemporada", DBNull::Value);
                } else {
                    cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                }
                
                cmd->Parameters->AddWithValue("@idEquip", idEquip);

                cmd->ExecuteNonQuery();

                String^ queryVerificacio = "";
                if (String::IsNullOrEmpty(idTemporada)) {
                    queryVerificacio = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip AND idTemporada IS NULL";
                }
                else {
                    queryVerificacio = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                }

                MySqlCommand^ cmdVerificacio = gcnew MySqlCommand(queryVerificacio, conn);
                cmdVerificacio->Parameters->AddWithValue("@idEquip", idEquip);
                if (!String::IsNullOrEmpty(idTemporada)) {
                    cmdVerificacio->Parameters->AddWithValue("@idTemporada", idTemporada);
                }

                int filesVerificades = Convert::ToInt32(cmdVerificacio->ExecuteScalar());
                if (filesVerificades != 1) {
                    throw gcnew Exception("La base de dades no ha confirmat la modificació de l'equip.");
                }
            }
            finally {
                delete conn;
            }
        }

        void PassarellaEquip::Esborra() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "DELETE FROM Equip WHERE idEquip=@idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                int filesAfectades = cmd->ExecuteNonQuery();
                if (filesAfectades != 1) {
                    throw gcnew Exception("No s'ha esborrat cap equip de la base de dades.");
                }

                String^ queryVerificacio = "SELECT COUNT(*) FROM Equip WHERE idEquip = @idEquip";
                MySqlCommand^ cmdVerificacio = gcnew MySqlCommand(queryVerificacio, conn);
                cmdVerificacio->Parameters->AddWithValue("@idEquip", idEquip);
                int filesVerificades = Convert::ToInt32(cmdVerificacio->ExecuteScalar());
                if (filesVerificades != 0) {
                    throw gcnew Exception("La base de dades no ha confirmat l'esborrat de l'equip.");
                }
            }
            finally {
                delete conn;
            }
        }

        PassarellaEquip^ PassarellaEquip::Llegeix(String^ connStr, String^ idEq) {
            PassarellaEquip^ equip = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ query = "SELECT idEquip, nom, dataFundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio, idTemporada FROM Equip WHERE idEquip = @idEquip";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idEquip", idEq);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    String^ idTemporadaVal = reader->IsDBNull(reader->GetOrdinal("idTemporada")) ? nullptr : reader->GetString("idTemporada");
                    
                    equip = gcnew PassarellaEquip(
                        connStr,
                        reader->GetString("idEquip"),
                        reader->GetString("nom"),
                        reader->GetDateTime("dataFundacio"),
                        reader->GetString("esport"),
                        reader->GetUInt32("partitsJugats"),
                        reader->GetUInt32("victories"),
                        reader->GetUInt32("derrotes"),
                        reader->GetUInt32("empats"),
                        reader->GetUInt32("punts"),
                        reader->GetUInt32("golsAFavor"),
                        reader->GetUInt32("golsEnContra"),
                        reader->GetInt32("diferenciaGols"),
                        reader->GetInt32("posicioClassificacio"),
                        idTemporadaVal
                    );
                }
                reader->Close();
            }
            finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            return equip;
        }

        List<String^>^ PassarellaEquip::ObtenirNomsEquipsPerTemporada(String^ idTemporada) {
            List<String^>^ nomsEquips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

            try {
                conn->Open();
                String^ query = "SELECT nom FROM Equip WHERE idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    nomsEquips->Add(reader->GetString("nom"));
                }
                reader->Close();
            } finally {
                if(conn != nullptr) {
                    conn->Close();
                    delete conn;
                }
            }
            
            return nomsEquips;
        }

    }
}
