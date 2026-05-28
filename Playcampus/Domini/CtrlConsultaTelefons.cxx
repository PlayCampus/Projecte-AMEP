#include "pch.h"
#include "CtrlConsultaTelefons.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraUsuari.hxx"

using namespace System;
using namespace System::Data;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlConsultaTelefons::CtrlConsultaTelefons() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlConsultaTelefons::ObtenirTipusUsuariPerCorreu(String^ correuUsuari) {
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connectionString);
            return cercadora->ObtenirTipusUsuariPerCorreu(correuUsuari);
        }

        DataTable^ CtrlConsultaTelefons::ObtenirTelefonsPerCapita(String^ correuUsuari) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirTelefonsAdministradorPerCapita(correuUsuari);
        }

        DataTable^ CtrlConsultaTelefons::ObtenirTelefonsPerJugador(String^ correuUsuari) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirTelefonsContactePerJugador(correuUsuari);
        }

        DataTable^ CtrlConsultaTelefons::ObtenirTelefonsPerAdministrador(String^ correuUsuari) {
            CercadoraLliga^ cercadora = gcnew CercadoraLliga(connectionString);
            return cercadora->ObtenirTelefonsCapitansPerAdministrador(correuUsuari);
        }

        DataTable^ CtrlConsultaTelefons::ObtenirTelefonsContacte(String^ correuUsuari) {
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

            throw gcnew UnauthorizedAccessException("Aquest usuari no te permisos per consultar telefons de contacte.");
        }
    }
}
