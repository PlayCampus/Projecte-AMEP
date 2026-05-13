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
            void CrearLliga(String^ idLliga, String^ nom, Disciplina disciplina, String^ descripcio, String^ contrasenya, String^ tipusUsuari, String^ correuUsuari);
            bool ExisteixLliga(String^ nomLliga);
            bool TeLligaActiva(String^ correuUsuari);
        };
    }
}
