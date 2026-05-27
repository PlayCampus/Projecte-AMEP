#pragma once
#include "../Dades/PassarellaJornada.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaTemporada.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlCrearJornada {
        public:
            CtrlCrearJornada();

            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);

            List<Dictionary<String^, String^>^>^ ObtenirTemporadesLliga(String^ nomLliga);

            // Crea la jornada llamando a la pasarela
            void CrearJornada(String^ idTemporada,int numero, DateTime dataInici, DateTime dataFi, String^ estat);
        };
    }
}