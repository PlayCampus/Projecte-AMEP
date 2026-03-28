#include "pch.h"
#include "Jugador.hxx"

namespace Playcampus {
    namespace Domini {
        Jugador::Jugador(String^ nom, String^ posicio, int dorsal, int edat, DateTime antiguitat) {
            this->nom = nom;
            this->posicio = posicio;
            this->dorsal = dorsal;
            this->edat = edat;
            this->antiguitat = antiguitat;
            this->minutsJugats = 0;
            this->partitsJugats = 0;
            this->anotacions = 0;
            this->assistencies = 0;
            this->faltesLleus = 0;
            this->faltesGreus = 0;
        }

        String^ Jugador::GetNom() { return nom; }
        void Jugador::SetNom(String^ nom) { this->nom = nom; }

        String^ Jugador::GetPosicio() { return posicio; }
        void Jugador::SetPosicio(String^ posicio) { this->posicio = posicio; }

        int Jugador::GetDorsal() { return dorsal; }
        void Jugador::SetDorsal(int dorsal) { this->dorsal = dorsal; }

        int Jugador::GetEdat() { return edat; }
        void Jugador::SetEdat(int edat) { this->edat = edat; }

        DateTime Jugador::GetAntiguitat() { return antiguitat; }
        void Jugador::SetAntiguitat(DateTime antiguitat) { this->antiguitat = antiguitat; }

        int Jugador::GetAnotacions() { return anotacions; }
        void Jugador::SetAnotacions(int anotacions) { this->anotacions = anotacions; }

        int Jugador::GetAssistencies() { return assistencies; }
        void Jugador::SetAssistencies(int assistencies) { this->assistencies = assistencies; }

        int Jugador::GetFaltesLleus() { return faltesLleus; }
        void Jugador::SetFaltesLleus(int faltesLleus) { this->faltesLleus = faltesLleus; }

        int Jugador::GetFaltesGreus() { return faltesGreus; }
        void Jugador::SetFaltesGreus(int faltesGreus) { this->faltesGreus = faltesGreus; }

        int Jugador::GetMinutsJugats() { return minutsJugats; }
        void Jugador::SetMinutsJugats(int minutsJugats) { this->minutsJugats = minutsJugats; }

        int Jugador::GetPartitsJugats() { return partitsJugats; }
        void Jugador::SetPartitsJugats(int partitsJugats) { this->partitsJugats = partitsJugats; }

        bool Jugador::ValidarDorsal() {
            // RIT8
            return dorsal <= 99;
        }

        bool Jugador::ValidarEdat() {
            // RIT9
            return edat >= 16 && edat <= 99;
        }

        bool Jugador::ValidarAntiguitat() {
            // RIT10
            return antiguitat <= DateTime::Now;
        }

        bool Jugador::ValidarNom() {
            // RIT22
            return !String::IsNullOrEmpty(nom);
        }
    }
}
