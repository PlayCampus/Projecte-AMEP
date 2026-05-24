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

            DataTable^ ObtenirPartits();

            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerJornada(String^ idJornada);
            DataTable^ ObtenirPartitsFinalitzatsPerTemporada(String^ idTemporada);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsCapita(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDeLEquip(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip);
            Dictionary<String^, String^>^ ObtenirAvisPendent(String^ correuJugador);
            bool PartitDisponiblePerEquip(String^ idPartit, String^ idEquip);
            bool AssignacioJugadorPartitExisteix(String^ idPartit, String^ idJugador);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDisponiblesPerEquip(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerLliga(String^ nomLliga);
            Dictionary<String^, String^>^ ObtenirDetallPartit(String^ idPartit, String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin);
            DataTable^ ObtenirProgramacioPartits();
            DataTable^ ObtenirCalendariCompletLligaPerId(String^ idLliga);
            DataTable^ ObtenirUltimsResultats(String^ idLliga, String^ idTemporada, int limit);
            DataTable^ ObtenirProximsPartits(String^ idLliga, String^ idTemporada, int limit);
            DataTable^ ObtenirDetallsPartitEstadistiques(String^ idPartit);
            DataTable^ ObtenirEstadistiquesPartit(String^ idPartit);
        };
    }
}