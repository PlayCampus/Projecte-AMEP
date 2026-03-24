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
            // Lògica per revisar el seu historial de participació
        }

        void Estudiant::VisualitzarCalendariGeneral(String^ idLliga) {
            // Consultar partits previstos de la competició
        }

        void Estudiant::SeguirResultatsTempsReal() {
            // Obté els resultats actualitzats en viu dels partits
        }

        void Estudiant::ConsultarClassificacioLliga(String^ idLliga) {
            // Veure la taula classificatòria de la lliga
        }
    }
}
