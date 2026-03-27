#pragma once
#include <string>
#include "Disciplina.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Equip {
        private:
            String^ nom;
            DateTime dataFundacio;
            Disciplina esport;

        public:
            Equip(String^ nom, DateTime dataFundacio, Disciplina esport);

            String^ GetNom();
            void SetNom(String^ nom);

            DateTime GetDataFundacio();
            void SetDataFundacio(DateTime dataFundacio);

            Disciplina GetEsport();
            void SetEsport(Disciplina esport);

            // Validacions relacionades
            bool ValidarDataFundacio();
        };
    }
}
