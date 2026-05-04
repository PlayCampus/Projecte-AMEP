#pragma once
#include <string>
#include "Disciplina.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Lliga {
        private:
            String^ idLliga;
            String^ nom;
            Disciplina disciplina;
            String^ descripcio;
            String^ contrasenya; // Afegit com a requisit

        public:
            Lliga(String^ idLliga, String^ nom, Disciplina disciplina, String^ descripcio, String^ contrasenya);

            String^ GetIdLliga();
            void SetIdLliga(String^ idLliga);

            String^ GetNom();
            void SetNom(String^ nom);

            Disciplina GetDisciplina();
            void SetDisciplina(Disciplina disciplina);

            String^ GetDescripcio();
            void SetDescripcio(String^ descripcio);

            String^ GetContrasenya();
            void SetContrasenya(String^ contrasenya);

            // Validacions per a les RIT de Lliga:
            // RIT39: una lliga no pot estar en estat "activa" si no té equips registrats.
            bool EsPotActivar(int quantitatEquips);

            // RIT16: una lliga només pot tenir jornades i partits si té com a mínim dos equips participants.
            bool PotTenirJornades(int quantitatEquips);
        };
    }
}
