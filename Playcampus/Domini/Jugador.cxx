#include "pch.h"
#include "Jugador.hxx"

namespace Playcampus {
    namespace Domini {
        Jugador::Jugador(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ posicio, int dorsal, int edat, DateTime antiguitat, DateTime dataNaixement) 
            : Usuari(identificador, nom, contrasenya, data_registre, correu_electronic) {
            this->posicio = posicio;
            this->dorsal = dorsal;
            this->edat = edat;
            this->antiguitat = antiguitat;
            this->dataNaixement = dataNaixement;
            this->minutsJugats = 0;
            this->partitsJugats = 0;
            this->anotacions = 0;
            this->assistencies = 0;
            this->faltesLleus = 0;
            this->faltesGreus = 0;
        }

        String^ Jugador::GetPosicio() { return posicio; }
        void Jugador::SetPosicio(String^ posicio) { this->posicio = posicio; }

        int Jugador::GetDorsal() { return dorsal; }
        void Jugador::SetDorsal(int dorsal) { this->dorsal = dorsal; }

        int Jugador::GetEdat() { return edat; }
        void Jugador::SetEdat(int edat) { this->edat = edat; }

        DateTime Jugador::GetAntiguitat() { return antiguitat; }
        void Jugador::SetAntiguitat(DateTime antiguitat) { this->antiguitat = antiguitat; }

        DateTime Jugador::GetDataNaixement() { return dataNaixement; }
        void Jugador::SetDataNaixement(DateTime dataNaixement) { this->dataNaixement = dataNaixement; }

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
            // RIT27: dorsal > 0 i dorsal <= 99
            return dorsal > 0 && dorsal <= 99;
        }

        bool Jugador::ValidarEdat() {
            // RIT9
            return edat >= 16 && edat <= 99;
        }

        bool Jugador::ValidarAntiguitat() {
            // RIT10
            return antiguitat <= DateTime::Now;
        }

        bool Jugador::ValidarDataNaixement() {
            // RIT29: dataNaixement ha de ser anterior a la data actual
            return dataNaixement < DateTime::Now;
        }

        bool Jugador::ValidarEstadistiques() {
            // RIT30: partitsJugats, anotacions, assistencies, faltesLleus, faltesGreus i minutsJugats >= 0
            return partitsJugats >= 0 && 
                   anotacions >= 0 && 
                   assistencies >= 0 && 
                   faltesLleus >= 0 && 
                   faltesGreus >= 0 && 
                   minutsJugats >= 0;
        }
    }
}
