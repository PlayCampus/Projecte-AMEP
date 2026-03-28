#pragma once
#include <string>
#include "Disciplina.hxx"
#include "Lliga.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlCrearLliga {
        private:
            String^ connectionString;
        public:
            CtrlCrearLliga();
            void CrearLliga(String^ idLliga, String^ nom, Disciplina disciplina, String^ descripcio, String^ estat, String^ contrasenya, String^ tipusUsuari);
            bool ExisteixLliga(String^ nomLliga);
        };
    }
}
