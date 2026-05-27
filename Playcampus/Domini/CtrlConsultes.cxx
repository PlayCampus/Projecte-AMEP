#include "pch.h"
#include "CtrlConsultes.hxx"
#include "CtrlConsultaPartits.hxx"
#include "CtrlConsultaLligues.hxx"
#include "CtrlConsultaFitxatges.hxx"
#include "CtrlConsultaTelefons.hxx"

using namespace System;
using namespace System::Data;

namespace Playcampus {
    namespace Domini {

        CtrlConsultes::CtrlConsultes() {
        }

        DataTable^ CtrlConsultes::ObtenirProgramacioPartits() {
            CtrlConsultaPartits^ ctrl = gcnew CtrlConsultaPartits();
            return ctrl->ObtenirProgramacioPartits();
        }

        DataTable^ CtrlConsultes::ObtenirEstatLligues() {
            CtrlConsultaLligues^ ctrl = gcnew CtrlConsultaLligues();
            return ctrl->ObtenirEstatLligues();
        }

        DataTable^ CtrlConsultes::ObtenirEstadistiquesEquips() {
            CtrlConsultaLligues^ ctrl = gcnew CtrlConsultaLligues();
            return ctrl->ObtenirEstadistiquesEquips();
        }

        DataTable^ CtrlConsultes::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            CtrlConsultaPartits^ ctrl = gcnew CtrlConsultaPartits();
            return ctrl->ObtenirCalendariCompletLligaPerId(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirUltimsFitxatges(int limit) {
            CtrlConsultaFitxatges^ ctrl = gcnew CtrlConsultaFitxatges();
            return ctrl->ObtenirUltimsFitxatges(limit);
        }

        DataTable^ CtrlConsultes::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            CtrlConsultaLligues^ ctrl = gcnew CtrlConsultaLligues();
            return ctrl->ObtenirEquipsDeLaLligaAdministrador(correuAdmin);
        }

        String^ CtrlConsultes::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            CtrlConsultaLligues^ ctrl = gcnew CtrlConsultaLligues();
            return ctrl->ObtenirNomLligaAdministrador(correuAdmin);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsContacte(String^ correuUsuari) {
            CtrlConsultaTelefons^ ctrl = gcnew CtrlConsultaTelefons();
            return ctrl->ObtenirTelefonsContacte(correuUsuari);
        }

        void CtrlConsultes::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            CtrlConsultaLligues^ ctrl = gcnew CtrlConsultaLligues();
            ctrl->TreureEquipDeLaLliga(idEquip, correuAdmin);
        }
    }
}
