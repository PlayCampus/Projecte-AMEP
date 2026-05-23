#include "pch.h"
#include "CtrlEditarPartit.hxx"
#include "EtiquetesEditarPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlEditarPartit::CtrlEditarPartit() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        bool CtrlEditarPartit::ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin) {
            PassarellaUsuari^ usuari = (gcnew CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuAdmin);
            bool valid = false;

            if (usuari != nullptr) {
                PassarellaLliga^ passLliga = gcnew PassarellaLliga(connectionString);
                valid = passLliga->EsAdministradorLliga(nomLliga, correuAdmin);
            }

            return valid;
        }

        String^ CtrlEditarPartit::ObtenirNomLligaAdmin(String^ correuAdmin) {
            String^ nomLliga = nullptr;

            if (!String::IsNullOrWhiteSpace(correuAdmin)) {
                CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
                nomLliga = cercadora->ObtenirNomLligaAdmin(correuAdmin);
            }

            return nomLliga;
        }

        List<Dictionary<String^, String^>^>^ CtrlEditarPartit::ObtenirPartitsPerLliga(String^ nomLliga, String^ correuAdmin) {
            if (!ValidarAdministradorLliga(nomLliga, correuAdmin)) {
                throw gcnew UnauthorizedAccessException("No tens permisos per editar partits d'aquesta lliga.");
            }

            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirPartitsPerLliga(nomLliga);
        }

        Dictionary<String^, String^>^ CtrlEditarPartit::ObtenirDetallPartit(String^ idPartit, String^ correuAdmin) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            Dictionary<String^, String^>^ detall = cercadora->ObtenirDetallPartit(idPartit);

            if (detall == nullptr) {
                throw gcnew Exception("No s'ha trobat el partit seleccionat.");
            }

            String^ correuAdministradorPartit = detall["correuAdmin"];
            if (!correuAdministradorPartit->Equals(correuAdmin, StringComparison::OrdinalIgnoreCase)) {
                throw gcnew UnauthorizedAccessException("No tens permisos per editar aquest partit.");
            }

            detall->Remove("correuAdmin");
            detall["stats"] = "";

            return detall;
        }

        List<Dictionary<String^, String^>^>^ CtrlEditarPartit::ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirJugadorsPartit(idPartit, correuAdmin);
        }

        void CtrlEditarPartit::ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ correuAdmin, Nullable<DateTime> novaDataPartit) {
            Dictionary<String^, String^>^ detall = ObtenirDetallPartit(idPartit, correuAdmin);
            String^ disciplina = detall["disciplina"];
            String^ estatAnterior = detall["estat"];

            if (String::IsNullOrWhiteSpace(nouEstat)) {
                throw gcnew ArgumentException("L'estat del partit és obligatori.");
            }

            Dictionary<String^, String^>^ etiquetes = EtiquetesEditarPartit::ObtenirEtiquetesEditarPartit(disciplina);
            if (resultatLocal < 0) {
                String^ campLocal = etiquetes["marcadorLocal"]->Replace(":", "")->Trim();
                throw gcnew ArgumentException("El camp '" + campLocal + "' no pot ser negatiu.");
            }
            if (resultatVisitant < 0) {
                String^ campVisitant = etiquetes["marcadorVisitant"]->Replace(":", "")->Trim();
                throw gcnew ArgumentException("El camp '" + campVisitant + "' no pot ser negatiu.");
            }

            int golsLocalAnterior = 0;
            int golsVisitantAnterior = 0;
            if (detall->ContainsKey("golsLocal") && !String::IsNullOrEmpty(detall["golsLocal"])) {
                golsLocalAnterior = Int32::Parse(detall["golsLocal"]);
            }
            if (detall->ContainsKey("golsVisitant") && !String::IsNullOrEmpty(detall["golsVisitant"])) {
                golsVisitantAnterior = Int32::Parse(detall["golsVisitant"]);
            }

            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->ActualitzarPartitIStats(idPartit, nouEstat, resultatLocal, resultatVisitant, statsJson, disciplina, estatAnterior, golsLocalAnterior, golsVisitantAnterior, novaDataPartit);
        }
    }
}
