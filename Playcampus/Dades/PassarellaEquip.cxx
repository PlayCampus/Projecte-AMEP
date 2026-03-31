#include "pch.h"
#include "PassarellaEquip.hxx"

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
        }

        PassarellaEquip::PassarellaEquip(String^ connStr, String^ idEquip, String^ nom, DateTime dataFundacio, String^ esport, unsigned int partitsJugats, unsigned int victories, unsigned int derrotes, unsigned int empats, unsigned int punts, unsigned int golsAFavor, unsigned int golsEnContra, int diferenciaGols, int posicioClassificacio) {
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

        void PassarellaEquip::Insereix() {
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();

                if (String::IsNullOrEmpty(idEquip)) {
                    idEquip = Guid::NewGuid().ToString();
                }

                String^ query = "INSERT INTO Equip (idEquip, nom, dataFundacio, esport, partitsJugats, victories, derrotes, empats, punts, golsAFavor, golsEnContra, diferenciaGols, posicioClassificacio) VALUES (@idEquip, @nom, @dataFundacio, @esport, @partitsJugats, @victories, @derrotes, @empats, @punts, @golsAFavor, @golsEnContra, @diferenciaGols, @posicioClassificacio)";
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

                cmd->ExecuteNonQuery();
            }
            finally {
                if (conn != nullptr) {
                    delete conn;
                }
            }
        }
    }
}
