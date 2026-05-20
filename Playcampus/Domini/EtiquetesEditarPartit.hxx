#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        public ref class EtiquetesEditarPartit {
        public:
            // Pre: disciplina pot ser nullptr, buida o contenir el nom de l'esport de la lliga.
            // Post: retorna un diccionari amb textos visibles i noms interns coherents amb l'esport.
            static Dictionary<String^, String^>^ ObtenirEtiquetesEditarPartit(String^ disciplina);

        private:
            // Pre: disciplina pot ser nullptr, buida o contenir accents/majúscules.
            // Post: retorna futbol, basquet, volei o generic segons el text rebut.
            static String^ NormalitzarDisciplina(String^ disciplina);
        };
    }
}
