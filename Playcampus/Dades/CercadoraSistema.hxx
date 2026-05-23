#pragma once
#include <string>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
    namespace Dades {
        public ref class CercadoraSistema {
        private:
            String^ connectionString;

        public:
            CercadoraSistema(String^ connStr);

            String^ ObtenirIdEquipCapitaPerCorreu(String^ correu);
            String^ ObtenirIdEquipCapitaPerIdentificador(String^ identificador);
            bool ExisteixEquip(String^ idEquip);
            bool JugadorPertanyAEquip(String^ idJugador, String^ idEquip);
            bool PartitDisponiblePerEquip(String^ idPartit, String^ idEquip);
            bool AssignacioJugadorPartitExisteix(String^ idPartit, String^ idJugador);
            String^ ObtenirNomUsuariPerIdentificador(String^ identificador);
            String^ ObtenirIdEquipPerNomExacte(String^ nomEquip);
            List<String^>^ ObtenirNomsEquipsPerLliga(String^ nomLliga);

            List<Dictionary<String^, String^>^>^ ObtenirPartitsDisponiblesEquip(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsEquipPerAssignacio(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirPlantillaPerEquip(String^ idEquip);

            List<Dictionary<String^, String^>^>^ ObtenirPartitsCapita(String^ correuCapita);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsDeLEquip(String^ idEquip);
            List<Dictionary<String^, String^>^>^ ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip);
            Dictionary<String^, String^>^ ObtenirAvisPendent(String^ correuJugador);

            String^ ObtenirNomLligaAdmin(String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerLliga(String^ nomLliga);
            Dictionary<String^, String^>^ ObtenirDetallPartit(String^ idPartit);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin);
            Dictionary<String^, String^>^ ObtenirEquipsPartit(String^ idPartit);
            String^ ObtenirPosicioJugador(String^ idJugador);
            Dictionary<String^, String^>^ ObtenirEstadisticaIndividual(String^ idPartit, String^ idJugador);

            String^ ObtenirIdUsuariPerCorreuString(String^ correu);
            int ObtenirIdUsuariPerCorreuInt(String^ correu);
            String^ ObtenirTipusUsuariPerCorreu(String^ correu);
            bool CapitaTeEquip(String^ correu);
            bool EquipEstaEnLliga(String^ correu);

            String^ ObtenirIdLligaPerNom(String^ nomLliga);
            String^ ObtenirNomLligaPerId(String^ idLliga);
            String^ ObtenirContrasenyaLligaPerNom(String^ nomLliga);
            String^ ObtenirIdLligaSeguida(int idUsuari);
            String^ ObtenirIdTemporadaRellevant(String^ idLliga);
            String^ ObtenirDisciplinaLliga(String^ idLliga);

            DataTable^ ObtenirProgramacioPartits();
            DataTable^ ObtenirEstatLligues();
            DataTable^ ObtenirEstadistiquesEquipsGenerals();
            DataTable^ ObtenirCalendariCompletLligaPerId(String^ idLliga);
            DataTable^ ObtenirUltimsFitxatges(int limit);
            DataTable^ ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin);
            String^ ObtenirNomLligaAdministrador(String^ correuAdmin);
            DataTable^ ObtenirTelefonsAdministradorPerCapita(String^ correuCapita);
            DataTable^ ObtenirTelefonsContactePerJugador(String^ correuJugador);
            DataTable^ ObtenirTelefonsCapitansPerAdministrador(String^ correuAdministrador);

            DataTable^ ObtenirClassificacioLliga(String^ idLliga);
            DataTable^ ObtenirProximsPartits(String^ idLliga, int limit);
            DataTable^ ObtenirUltimsResultats(String^ idLliga, int limit);

            bool ExisteixEquipPerNom(String^ nomEquip);
            DataTable^ ObtenirLliguesEquip(String^ nomEquip);
            DataTable^ ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga);
            DataTable^ ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada);

            DataTable^ ObtenirEstadistiquesJugador(String^ idJugador);
            DataTable^ ObtenirTotesEstadistiquesJugadors();
            DataTable^ ObtenirEstadistiquesPartit(String^ idPartit);
            DataTable^ ObtenirDetallsPartitEstadistiques(String^ idPartit);

            String^ ObtenirIdLligaAdminPerCorreu(String^ correuAdmin);
            String^ ObtenirIdLligaCapitaPerCorreu(String^ correuCapita);
            DataTable^ ObtenirTemporadesLligaEstadistiques(String^ idLliga);
            DataTable^ ObtenirClassificacioLligaEstadistiques(String^ idLliga);
        };
    }
}
