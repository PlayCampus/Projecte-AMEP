#include "pch.h"
#include "CtrlConsultes.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlConsultes::CtrlConsultes() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlConsultes::ObtenirDisciplinaLliga(String^ idLliga) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirDisciplinaLliga(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirProgramacioPartits() {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirProgramacioPartits();
        }

        DataTable^ CtrlConsultes::ObtenirEstatLligues() {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEstatLligues();
        }

        DataTable^ CtrlConsultes::ObtenirEstadistiquesEquips() {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEstadistiquesEquips();
        }

        DataTable^ CtrlConsultes::ObtenirCalendariCompletLligaPerId(String^ idLliga) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirCalendariCompletLligaPerId(idLliga);
        }

        DataTable^ CtrlConsultes::ObtenirUltimsFitxatges(int limit) {
            CercadoraJugador^ cercadora = gcnew CercadoraJugador(connectionString);
            return cercadora->ObtenirUltimsFitxatges(limit);
        }

        DataTable^ CtrlConsultes::ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirEquipsDeLaLligaAdministrador(correuAdmin);
        }

        String^ CtrlConsultes::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirNomLligaAdministrador(correuAdmin);
        }

        String^ CtrlConsultes::ObtenirTipusUsuariPerCorreu(String^ correuUsuari) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            return cercadora->ObtenirTipusUsuariPerCorreu(correuUsuari);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsPerCapita(String^ correuUsuari) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirTelefonsAdministradorPerCapita(correuUsuari);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsPerJugador(String^ correuUsuari) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirTelefonsContactePerJugador(correuUsuari);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsPerAdministrador(String^ correuUsuari) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirTelefonsCapitansPerAdministrador(correuUsuari);
        }

        DataTable^ CtrlConsultes::ObtenirTelefonsContacte(String^ correuUsuari) {
            if (String::IsNullOrWhiteSpace(correuUsuari)) {
                throw gcnew ArgumentException("No s'ha pogut identificar l'usuari actual.");
            }

            String^ tipus = ObtenirTipusUsuariPerCorreu(correuUsuari);
            if (String::IsNullOrWhiteSpace(tipus)) {
                throw gcnew Exception("No s'ha trobat el tipus de l'usuari actual.");
            }

            if (tipus->Equals("Capita", StringComparison::OrdinalIgnoreCase)) {
                return ObtenirTelefonsPerCapita(correuUsuari);
            }

            if (tipus->Equals("Jugador", StringComparison::OrdinalIgnoreCase)) {
                return ObtenirTelefonsPerJugador(correuUsuari);
            }

            if (tipus->Equals("Administrador", StringComparison::OrdinalIgnoreCase)) {
                return ObtenirTelefonsPerAdministrador(correuUsuari);
            }

            throw gcnew UnauthorizedAccessException("Aquest usuari no té permisos per consultar telèfons de contacte.");
        }

        void CtrlConsultes::TreureEquipDeLaLliga(String^ idEquip, String^ correuAdmin) {
            PassarellaEquip^ passarellaEquip = gcnew PassarellaEquip(connectionString);
            passarellaEquip->TreureDeLaLligaSiAdmin(idEquip, correuAdmin);
        }
    }
}
