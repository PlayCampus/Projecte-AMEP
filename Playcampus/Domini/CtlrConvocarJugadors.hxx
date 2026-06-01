#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {

        public ref class CtlrConvocarJugadors {
        private:
            String^ connectionString;

        public:
            // Constructor
            CtlrConvocarJugadors();
            System::Collections::Generic::Dictionary<System::String^, System::String^>^ ObtenirAvisPendent(System::String^ correuJugador);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsCapita(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirConvocatoriaPartit(String^ idPartit);
            // Obtiene los partidos donde participa el equipo (local o visitante)
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDeLEquip(String^ idEquip);

            // Obtiene la lista de jugadores y si estn convocados/confirmados para un partido
            List<Dictionary<String^, String^>^>^ ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip);

            // El capitn marca si convoca o no a un jugador
            void ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat);
        
            // El jugador confirma si asistir o no
            void ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix);

        };

    }
}