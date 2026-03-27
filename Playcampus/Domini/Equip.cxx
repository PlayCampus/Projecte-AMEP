#include "pch.h"
#include "Equip.hxx"

namespace Playcampus {
    namespace Domini {
        Equip::Equip(String^ nom, int quantitatJugadors, DateTime dataFundacio, Disciplina esport) {
            this->nom = nom;
            this->quantitatJugadors = quantitatJugadors;
            this->dataFundacio = dataFundacio;
            this->esport = esport;
        }

        String^ Equip::GetNom() { return nom; }
        void Equip::SetNom(String^ nom) { this->nom = nom; }

        int Equip::GetQuantitatJugadors() { return quantitatJugadors; }
        void Equip::SetQuantitatJugadors(int quantitatJugadors) { this->quantitatJugadors = quantitatJugadors; }

        DateTime Equip::GetDataFundacio() { return dataFundacio; }
        void Equip::SetDataFundacio(DateTime dataFundacio) { this->dataFundacio = dataFundacio; }

        Disciplina Equip::GetEsport() { return esport; }
        void Equip::SetEsport(Disciplina esport) { this->esport = esport; }

        bool Equip::ValidarQuantitatJugadors() {
            if (quantitatJugadors <= 1) return false;
            // RIT11
            if (esport == Disciplina::Futbol && quantitatJugadors >= 25) return false;
            if (esport == Disciplina::Basquet && quantitatJugadors >= 15) return false;
            if (esport == Disciplina::Voley && quantitatJugadors >= 20) return false;
            return true;
        }

        bool Equip::ValidarDataFundacio() {
            // RIT19
            return dataFundacio <= DateTime::Now;
        }
    }
}
