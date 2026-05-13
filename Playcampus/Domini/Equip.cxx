#include "pch.h"
#include "Equip.hxx"

namespace Playcampus {
    namespace Domini {
        Equip::Equip(String^ nom, DateTime dataFundacio, Disciplina esport) {
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

        String^ Equip::GetNom() { return nom; }
        void Equip::SetNom(String^ nom) { this->nom = nom; }

        DateTime Equip::GetDataFundacio() { return dataFundacio; }
        void Equip::SetDataFundacio(DateTime dataFundacio) { this->dataFundacio = dataFundacio; }

        Disciplina Equip::GetEsport() { return esport; }
        void Equip::SetEsport(Disciplina esport) { this->esport = esport; }

        unsigned int Equip::GetPartitsJugats() { return partitsJugats; }
        void Equip::SetPartitsJugats(unsigned int partitsJugats) { this->partitsJugats = partitsJugats; }

        unsigned int Equip::GetVictories() { return victories; }
        void Equip::SetVictories(unsigned int victories) { this->victories = victories; }

        unsigned int Equip::GetDerrotes() { return derrotes; }
        void Equip::SetDerrotes(unsigned int derrotes) { this->derrotes = derrotes; }

        unsigned int Equip::GetEmpats() { return empats; }
        void Equip::SetEmpats(unsigned int empats) { this->empats = empats; }

        unsigned int Equip::GetPunts() { return punts; }
        void Equip::SetPunts(unsigned int punts) { this->punts = punts; }

        unsigned int Equip::GetGolsAFavor() { return golsAFavor; }
        void Equip::SetGolsAFavor(unsigned int golsAFavor) { this->golsAFavor = golsAFavor; }

        unsigned int Equip::GetGolsEnContra() { return golsEnContra; }
        void Equip::SetGolsEnContra(unsigned int golsEnContra) { this->golsEnContra = golsEnContra; }

        int Equip::GetDiferenciaGols() { return diferenciaGols; }
        void Equip::SetDiferenciaGols(int diferenciaGols) { this->diferenciaGols = diferenciaGols; }

        int Equip::GetPosicioClassificacio() { return posicioClassificacio; }
        void Equip::SetPosicioClassificacio(int posicioClassificacio) { this->posicioClassificacio = posicioClassificacio; }

        bool Equip::ValidarDataFundacio() {
            // RIT19
            return dataFundacio <= DateTime::Now;
        }
    }
}
