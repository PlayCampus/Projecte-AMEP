#include "pch.h"
#include "PassarellaEquipTemporada.hxx"

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {

        // Constructor 1
        PassarellaEquipTemporada::PassarellaEquipTemporada(String^ connStr) {
            this->connectionString = connStr;
            this->partitsJugats = 0;
            this->victories = 0;
            this->derrotes = 0;
            this->empats = 0;
            this->punts = 0;
            this->golsAFavor = 0;
            this->golsEnContra = 0;
            this->diferenciaGols = 0;
            this->posicioClassificacio = 0;
        }

        // Constructor 2 
        PassarellaEquipTemporada::PassarellaEquipTemporada(String^ connStr, String^ idEquip, String^ idTemporada) {
            this->connectionString = connStr;
            this->idEquip = idEquip;
            this->idTemporada = idTemporada;
            this->partitsJugats = 0;
            this->victories = 0;
            this->derrotes = 0;
            this->empats = 0;
            this->punts = 0;
            this->golsAFavor = 0;
            this->golsEnContra = 0;
            this->diferenciaGols = 0;
            this->posicioClassificacio = 0;

        }

        PassarellaEquipTemporada::PassarellaEquipTemporada(String^ connStr, String^ idEquip, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio, String^ idTemporada) {
            this->connectionString = connStr;
            this->idEquip = idEquip;
            this->idTemporada = idTemporada;
            this->partitsJugats = partitsJugats;
            this->victories = victories;
            this->derrotes = derrotes;
            this->empats = empats;
            this->punts = punts;
            this->golsAFavor = golsAFavor;
            this->golsEnContra = golsEnContra;
            this->diferenciaGols = diferenciaGols;
            this->posicioClassificacio = posicioClassificacio;
        }

        // ------------------ GETTERS ------------------

        String^ PassarellaEquipTemporada::GetIdEquip() { return idEquip; }
        String^ PassarellaEquipTemporada::GetIdTemporada() { return idTemporada; }
        unsigned int PassarellaEquipTemporada::GetPartitsJugats() { return partitsJugats; }
        unsigned int PassarellaEquipTemporada::GetVictories() { return victories; }
        unsigned int PassarellaEquipTemporada::GetDerrotes() { return derrotes; }
        unsigned int PassarellaEquipTemporada::GetEmpats() { return empats; }
        unsigned int PassarellaEquipTemporada::GetPunts() { return punts; }
        unsigned int PassarellaEquipTemporada::GetGolsAFavor() { return golsAFavor; }
        unsigned int PassarellaEquipTemporada::GetGolsEnContra() { return golsEnContra; }
        int PassarellaEquipTemporada::GetDiferenciaGols() { return diferenciaGols; }
        int PassarellaEquipTemporada::GetPosicioClassificacio() { return posicioClassificacio; }

        // ------------------ SETTERS ------------------

        void PassarellaEquipTemporada::SetIdTemporada(String^ nouIdTemporada) { this->idTemporada = nouIdTemporada; }
        void PassarellaEquipTemporada::SetPartitsJugats(unsigned int partits) { this->partitsJugats = partits; }
        void PassarellaEquipTemporada::SetVictories(unsigned int victories) { this->victories = victories; }
        void PassarellaEquipTemporada::SetDerrotes(unsigned int derrotes) { this->derrotes = derrotes; }
        void PassarellaEquipTemporada::SetEmpats(unsigned int empats) { this->empats = empats; }
        void PassarellaEquipTemporada::SetPunts(unsigned int punts) { this->punts = punts; }
        void PassarellaEquipTemporada::SetGolsAFavor(unsigned int golsAFavor) { this->golsAFavor = golsAFavor; }
        void PassarellaEquipTemporada::SetGolsEnContra(unsigned int golsEnContra) { this->golsEnContra = golsEnContra; }
        void PassarellaEquipTemporada::SetDiferenciaGols(int diferencia) { this->diferenciaGols = diferencia; }
        void PassarellaEquipTemporada::SetPosicioClassificacio(int posicio) { this->posicioClassificacio = posicio; }

        // ------------------ OPERACIONES BD ------------------

        void PassarellaEquipTemporada::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "INSERT INTO EquipTemporada (idEquip, idTemporada, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio) "
                                "VALUES (@idEquip, @idTemporada, @partitsJugats, @victories, @derrotes, @empats, @punts, @golsAFavor, @golsEnContra, @diferenciaGols, @posicioClassificacio)";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                cmd->Parameters->AddWithValue("@partitsJugats", partitsJugats);
                cmd->Parameters->AddWithValue("@victories", victories);
                cmd->Parameters->AddWithValue("@derrotes", derrotes);
                cmd->Parameters->AddWithValue("@empats", empats);
                cmd->Parameters->AddWithValue("@punts", punts);
                cmd->Parameters->AddWithValue("@golsAFavor", golsAFavor);
                cmd->Parameters->AddWithValue("@golsEnContra", golsEnContra);
                cmd->Parameters->AddWithValue("@diferenciaGols", diferenciaGols);
                cmd->Parameters->AddWithValue("@posicioClassificacio", posicioClassificacio);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        void PassarellaEquipTemporada::Modifica() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "UPDATE EquipTemporada SET partitsJugats=@pj, victories=@v, derrotes=@d, empats=@e, punts=@p, "
                                "golsAFavor=@gf, golsEnContra=@gc, diferenciaGols=@dg, posicioClassificacio=@pc "
                                "WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);

                cmd->Parameters->AddWithValue("@pj", partitsJugats);
                cmd->Parameters->AddWithValue("@v", victories);
                cmd->Parameters->AddWithValue("@d", derrotes);
                cmd->Parameters->AddWithValue("@e", empats);
                cmd->Parameters->AddWithValue("@p", punts);
                cmd->Parameters->AddWithValue("@gf", golsAFavor);
                cmd->Parameters->AddWithValue("@gc", golsEnContra);
                cmd->Parameters->AddWithValue("@dg", diferenciaGols);
                cmd->Parameters->AddWithValue("@pc", posicioClassificacio);

                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        void PassarellaEquipTemporada::Esborra() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                // Eliminem usant la clau primària composta (Equipo + Temporada)
                String^ query = "DELETE FROM EquipTemporada WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);
                
                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
        }

        PassarellaEquipTemporada^ PassarellaEquipTemporada::Llegeix(String^ connStr, String^ idEquip, String^ idTemporada) {
            PassarellaEquipTemporada^ et = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connStr);
            try {
                conn->Open();
                String^ query = "SELECT partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio "
                                "FROM EquipTemporada WHERE idEquip = @idEquip AND idTemporada = @idTemporada";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                
                cmd->Parameters->AddWithValue("@idEquip", idEquip);
                cmd->Parameters->AddWithValue("@idTemporada", idTemporada);

                MySqlDataReader^ reader = cmd->ExecuteReader();
                if (reader->Read()) {
                    unsigned int pj = Convert::ToUInt32(reader["partitsJugats"]);
                    unsigned int v = Convert::ToUInt32(reader["victories"]);
                    unsigned int d = Convert::ToUInt32(reader["derrotes"]);
                    unsigned int e = Convert::ToUInt32(reader["empats"]);
                    unsigned int p = Convert::ToUInt32(reader["punts"]);
                    unsigned int gf = Convert::ToUInt32(reader["golsAFavor"]);
                    unsigned int gc = Convert::ToUInt32(reader["golsEnContra"]);
                    int dg = Convert::ToInt32(reader["diferenciaGols"]);
                    int pc = Convert::ToInt32(reader["posicioClassificacio"]);

                    et = gcnew PassarellaEquipTemporada(connStr, idEquip, pj, v, d, e, p, gf, gc, dg, pc, idTemporada);
                }
                reader->Close();
            }
            finally {
                if (conn != nullptr) { conn->Close(); delete conn; }
            }
            return et;
        }

    }
}
