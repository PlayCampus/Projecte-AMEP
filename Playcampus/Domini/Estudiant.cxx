#include "pch.h"
#include "Estudiant.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        Estudiant::Estudiant(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ carrera) 
            : Usuari(identificador, nom, contrasenya, data_registre, correu_electronic) {
            this->carrera = carrera;
        }

        String^ Estudiant::GetCarrera() { return carrera; }

        void Estudiant::ConsultarHistorialPersonal() {
            // LÃ²gica per revisar el seu historial de participaciÃ³
        }

        void Estudiant::VisualitzarCalendariGeneral(String^ idLliga) {
            // Consultar partits previstos de la competiciÃ³
        }

        void Estudiant::SeguirResultatsTempsReal() {
            // ObtÃ© els resultats actualitzats en viu dels partits
        }

        void Estudiant::ConsultarClassificacioLliga(String^ idLliga) {
            // Veure la taula classificatÃ²ria de la lliga
        }
    }
}
