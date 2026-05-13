#include "pch.h"
#include "Lliga.hxx"

namespace Playcampus {
    namespace Domini {
        Lliga::Lliga(String^ idLliga, String^ nom, Playcampus::Domini::Disciplina disciplina, String^ descripcio, String^ contrasenya) {
            this->idLliga = idLliga;
            this->nom = nom;
            this->disciplina = disciplina;
            this->descripcio = descripcio;
            this->contrasenya = contrasenya;
        }

        String^ Lliga::GetIdLliga() {
            return idLliga;
        }

        void Lliga::SetIdLliga(String^ idLliga) {
            this->idLliga = idLliga;
        }

        String^ Lliga::GetNom() {
            return nom;
        }

        void Lliga::SetNom(String^ nom) {
            this->nom = nom;
        }

        Disciplina Lliga::GetDisciplina() {
            return disciplina;
        }

        void Lliga::SetDisciplina(Disciplina disciplina) {
            this->disciplina = disciplina;
        }

        String^ Lliga::GetDescripcio() {
            return descripcio;
        }

        void Lliga::SetDescripcio(String^ descripcio) {
            this->descripcio = descripcio;
        }

        String^ Lliga::GetContrasenya() {
            return contrasenya;
        }

        void Lliga::SetContrasenya(String^ contrasenya) {
            this->contrasenya = contrasenya;
        }

        bool Lliga::EsPotActivar(int quantitatEquips) {
            // RIT39: una lliga no pot estar en estat "activa" si no tÃ© equips registrats
            return quantitatEquips > 0;
        }

        bool Lliga::PotTenirJornades(int quantitatEquips) {
            // RIT16: una lliga nomÃ©s pot tenir jornades i partits si tÃ© com a mÃ­nim dos equips participants.
            return quantitatEquips >= 2;
        }
    }
}
