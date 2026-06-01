#pragma once
#include <string>
#include "../Domini/Disciplina.hxx"

using namespace System;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaLliga {
        private:
            String^ connectionString;
            String^ idLliga;
            String^ nom;
            Playcampus::Domini::Disciplina disciplina;
            String^ descripcio;
            String^ contrasenya;
            String^ idAdministrador;

        public:
            PassarellaLliga(String^ connStr);
            PassarellaLliga(String^ connStr, String^ idLliga, String^ nom, Playcampus::Domini::Disciplina disciplina, String^ descripcio, String^ contrasenya, String^ idAdministrador);

            String^ GetIdLliga();
            String^ GetNom();
            Playcampus::Domini::Disciplina GetDisciplina();
            String^ GetDescripcio();
            String^ GetContrasenya();
            String^ GetIdAdministrador();

            void Insereix();
            bool ExisteixPerNom(String^ nomLliga);
            bool TeLligaActivaAdmin(String^ idAdmin);
            bool EsAdministradorLliga(System::String^ nomLliga, System::String^ correuAdmin);
            void SeguirLliga(String^ idUsuari, String^ idLliga);
            void DeixarDeSeguir(String^ idUsuari);

        };
    }
}