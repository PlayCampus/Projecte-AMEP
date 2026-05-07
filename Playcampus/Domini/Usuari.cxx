#include "pch.h"
#include "Usuari.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        Usuari::Usuari(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic) {
            this->identificador = identificador;
            this->nom = nom;
            this->contrasenya = contrasenya;
            this->data_registre = data_registre;
            this->correu_electronic = correu_electronic;
        }

        String^ Usuari::GetIdentificador() { return identificador; }
        String^ Usuari::GetNom() { return nom; }
        String^ Usuari::GetContrasenya() { return contrasenya; }
        DateTime Usuari::GetDataRegistre() { return data_registre; }
        String^ Usuari::GetCorreuElectronic() { return correu_electronic; }

        void Usuari::MostrarInformacio() {
            Console::WriteLine("Usuari: " + nom);
        }
    }
}
