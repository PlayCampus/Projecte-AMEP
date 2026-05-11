#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

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

            // Obtiene la lista de jugadores y si están convocados/confirmados para un partido
            List<Dictionary<String^, String^>^>^ ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip);

            // El capitán marca si convoca o no a un jugador
            void ActualitzarConvocatoria(String^ idPartit, String^ idJugador, bool convocat);
        
            // El jugador confirma si asistirá o no
            void ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix);

        };

    }
}