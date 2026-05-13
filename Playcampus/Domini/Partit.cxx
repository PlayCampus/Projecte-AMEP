#include "pch.h"
#include "Partit.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        Partit::Partit(String^ identificador, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada) {
            this->identificador = identificador;
            this->dataHora = dataHora;
            this->ubicacio = ubicacio;
            this->estat = estat;
            this->golsLocal = golsLocal;
            this->golsVisitant = golsVisitant;
            this->idJornada = idJornada;
        }


        String^ Partit::GetIdentificador() { return identificador; }
        DateTime Partit::GetDataHora() { return dataHora; }
        String^ Partit::GetUbicacio() { return ubicacio; }
        String^ Partit::GetEstat() { return estat; }
        int Partit::GetGolsLocal() { return golsLocal; }
        int Partit::GetGolsVisitant() { return golsVisitant; }
        String^ Partit::GetIdJornada() { return idJornada; }

        void Partit::SetEstat(String^ nouEstat) { estat = nouEstat; }
        void Partit::SetResultat(int golsLocal, int golsVisitant) {
            this->golsLocal = golsLocal;
            this->golsVisitant = golsVisitant;
        }

        void Partit::MostrarInformacio() {
            Console::WriteLine("Partit: " + identificador + " - " + ubicacio);
        }
    }
}
