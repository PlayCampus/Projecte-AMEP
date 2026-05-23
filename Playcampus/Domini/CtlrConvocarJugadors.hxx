#pragma once
#include <string>
using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        public ref class CtlrConvocarJugadors {
        private:
            String^ connectionString;
        public:
            CtlrConvocarJugadors();
            Dictionary<String^, String^>^ ObtenirAvisPendent(String^ correuJugador);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsCapita(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirConvocatoriaPartit(String^ idPartit);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDeLEquip(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip);
            void ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat);
            void ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix);
        };
    }
}
