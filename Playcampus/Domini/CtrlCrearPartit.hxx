#pragma once
#include "Partit.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlCrearPartit {
        private:
            String^ connectionString;
        public:
            CtrlCrearPartit();
            void CrearPartit(String^ idPartit, DateTime dataHora, String^ ubicacio, String^ estat, int golsLocal, int golsVisitant, String^ idJornada, String^ tipusUsuari);
        };
    }
}