#include "pch.h"
#include "CtrlEditarPartit.hxx"
#include "EtiquetesEditarPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/PassarellaPartit.hxx"

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
            if (usuari == nullptr) return false;

            PassarellaLliga^ passLliga = gcnew PassarellaLliga(connectionString);
            return passLliga->EsAdministradorLliga(nomLliga, correuAdmin);
        }

        String^ CtrlEditarPartit::ObtenirNomLligaAdmin(String^ correuAdmin) {
            if (String::IsNullOrWhiteSpace(correuAdmin)) {
                return nullptr;
            }
            CercadoraLliga^ cercadoraLliga = gcnew CercadoraLliga(connectionString);
            return cercadoraLliga->ObtenirNomLligaAdministrador(correuAdmin);
        }

        List<Dictionary<String^, String^>^>^ CtrlEditarPartit::ObtenirPartitsPerLliga(String^ nomLliga, String^ correuAdmin) {
            if (!ValidarAdministradorLliga(nomLliga, correuAdmin)) {
                throw gcnew UnauthorizedAccessException("No tens permisos per editar partits d'aquesta lliga.");
            }

            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirPartitsPerLliga(nomLliga);
        }

        Dictionary<String^, String^>^ CtrlEditarPartit::ObtenirDetallPartit(String^ idPartit, String^ correuAdmin) {
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirDetallPartit(idPartit, correuAdmin);
        }

        List<Dictionary<String^, String^>^>^ CtrlEditarPartit::ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin) {
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirJugadorsPartit(idPartit, correuAdmin);
        }

        void CtrlEditarPartit::ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ correuAdmin, Nullable<DateTime> novaDataPartit) {
            PassarellaPartit^ passarellaPartit = gcnew PassarellaPartit(connectionString);
            passarellaPartit->ActualitzarPartitIStats(idPartit, nouEstat, resultatLocal, resultatVisitant, statsJson, correuAdmin, novaDataPartit);
        }
    }
}
