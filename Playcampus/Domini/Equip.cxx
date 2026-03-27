#include "pch.h"
#include "Equip.hxx"

namespace Playcampus {
    namespace Domini {
        Equip::Equip(String^ nom, DateTime dataFundacio, Disciplina esport) {
            this->nom = nom;
            this->dataFundacio = dataFundacio;
            this->esport = esport;
        }

        String^ Equip::GetNom() { return nom; }
        void Equip::SetNom(String^ nom) { this->nom = nom; }

        DateTime Equip::GetDataFundacio() { return dataFundacio; }
        void Equip::SetDataFundacio(DateTime dataFundacio) { this->dataFundacio = dataFundacio; }

        Disciplina Equip::GetEsport() { return esport; }
        void Equip::SetEsport(Disciplina esport) { this->esport = esport; }

        bool Equip::ValidarDataFundacio() {
            // RIT19
            return dataFundacio <= DateTime::Now;
        }
    }
}
