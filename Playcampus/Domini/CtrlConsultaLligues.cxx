#include "pch.h"
#include "CtrlConsultaLligues.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlConsultaLligues::CtrlConsultaLligues() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlConsultaLligues::ObtenirDisciplinaLliga(String^ idLliga) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirDisciplinaLliga(idLliga);
        }

        DataTable^ CtrlConsultaLligues::ObtenirEstatLligues() {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEstatLligues();
        }

        DataTable^ CtrlConsultaLligues::ObtenirEstadistiquesEquips() {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEstadistiquesEquips();
        }

        DataTable^ CtrlConsultaLligues::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEquipsDeLaLligaAdministrador(correuAdmin);
        }

        String^ CtrlConsultaLligues::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirNomLligaAdministrador(correuAdmin);
        }

        void CtrlConsultaLligues::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            PassarellaEquip^ passarellaEquip = gcnew PassarellaEquip(connectionString);
            passarellaEquip->TreureDeLaLligaSiAdmin(idEquip, correuAdmin);
        }
    }
}
