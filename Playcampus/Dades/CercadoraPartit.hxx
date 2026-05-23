#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraPartit {
        private:
            String^ connectionString;

        public:
            CercadoraPartit(String^ connStr);

            // Búsquedes
            bool PartitDisponiblePerEquip(String^ idPartit, String^ idEquip);
            bool AssignacioJugadorPartitExisteix(String^ idPartit, String^ idJugador);

            // Consultes complexes
            DataTable^ ObtenirPartits();
            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerJornada(String^ idJornada);
            DataTable^ ObtenirPartitsFinalitzatsPerTemporada(String^ idTemporada);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsCapita(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDeLEquip(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip);
            Dictionary<String^, String^>^ ObtenirAvisPendent(String^ correuJugador);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerLliga(String^ nomLliga);
            Dictionary<String^, String^>^ ObtenirDetallPartit(String^ idPartit);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin);
            Dictionary<String^, String^>^ ObtenirEquipsPartit(String^ idPartit);
            String^ ObtenirPosicioJugador(String^ idJugador);
            Dictionary<String^, String^>^ ObtenirEstadisticaIndividual(String^ idPartit, String^ idJugador);
            DataTable^ ObtenirProgramacioPartits();
            DataTable^ ObtenirCalendariCompletLligaPerId(String^ idLliga);
            DataTable^ ObtenirEstadistiquesPartit(String^ idPartit);
            DataTable^ ObtenirDetallsPartitEstadistiques(String^ idPartit);
        };
    }
}
