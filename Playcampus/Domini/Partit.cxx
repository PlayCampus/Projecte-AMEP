#include "pch.h"
#include "Partit.hxx"

namespace Playcampus {
    namespace Domini {
        Partit::Partit(String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant) {
            this->idPartit = idPartit;
            this->dataHora = dataHora;
            this->ubicacio = ubicacio;
            this->estat = estat;
            this->golsLocal = golsLocal;
            this->golsVisitant = golsVisitant;
        }

        String^ Partit::GetIdPartit() { return idPartit; }
        void Partit::SetIdPartit(String^ idPartit) { this->idPartit = idPartit; }

        DateTime Partit::GetDataHora() { return dataHora; }
        void Partit::SetDataHora(DateTime dataHora) { this->dataHora = dataHora; }

        String^ Partit::GetUbicacio() { return ubicacio; }
        void Partit::SetUbicacio(String^ ubicacio) { this->ubicacio = ubicacio; }

        String^ Partit::GetEstat() { return estat; }
        void Partit::SetEstat(String^ estat) { this->estat = estat; }

        int Partit::GetGolsLocal() { return golsLocal; }
        void Partit::SetGolsLocal(int golsLocal) { this->golsLocal = golsLocal; }

        int Partit::GetGolsVisitant() { return golsVisitant; }
        void Partit::SetGolsVisitant(int golsVisitant) { this->golsVisitant = golsVisitant; }
    }
}
