#pragma once
#include "Usuari.hxx"
#include <vector>

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Estudiant : public Usuari {
        private:
            String^ carrera;
            // Llista d'equips o historial de participació on ha estat
            
        public:
            Estudiant(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ carrera);

            String^ GetCarrera();

            void ConsultarHistorialPersonal();

            void VisualitzarCalendariGeneral(String^ idLliga);

            void SeguirResultatsTempsReal();

            void ConsultarClassificacioLliga(String^ idLliga);
        };
    }
}
