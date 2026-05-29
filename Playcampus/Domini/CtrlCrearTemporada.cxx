#include "pch.h"
#include "CtrlCrearTemporada.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {

        CtrlCrearTemporada::CtrlCrearTemporada() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlCrearTemporada::ObtenirNomLligaAdministrador(String^ correuAdmin) {
            Playcampus::Dades::CercadoraLliga^ cercadora = gcnew Playcampus::Dades::CercadoraLliga(connectionString);
            return cercadora->ObtenirNomLligaAdministrador(correuAdmin);
        }

        void CtrlCrearTemporada::CrearTemporada(DateTime dataInici, DateTime dataFi, String^ correuAdmin) {
            // RIT9: La dataInici ha de ser anterior a la dataFi
            if (dataInici >= dataFi) {
                throw gcnew ArgumentException("La data d'inici ha de ser anterior a la data final.");
            }

            String^ idAdmin = nullptr;
            String^ nomLliga = ObtenirNomLligaAdministrador(correuAdmin);

            if (String::IsNullOrEmpty(nomLliga)) {
                throw gcnew Exception("L'usuari no \u00E9s administrador de cap lliga.");
            }

            // 1. Busquem l'ID de l'administrador mitjançant el seu correu
            if (!String::IsNullOrEmpty(correuAdmin)) {
                Playcampus::Dades::PassarellaUsuari^ adminUser = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuAdmin);
                if (adminUser != nullptr && adminUser->GetIdentificador() != nullptr) {
                    idAdmin = adminUser->GetIdentificador()->Trim();
                }
            }

            if (idAdmin == nullptr) {
                throw gcnew Exception("No s'ha pogut trobar l'administrador.");
            }

            // 2. Busquem la Lliga mitjançant el seu nom proporcionat per l'usuari
            Playcampus::Dades::CercadoraLliga^ cercadoraLliga = gcnew Playcampus::Dades::CercadoraLliga(connectionString);
            String^ idLliga = cercadoraLliga->ObtenirIdLligaPerNom(nomLliga);


            if (idLliga == nullptr) {
                throw gcnew Exception("No s'ha trobat cap lliga amb aquest nom.");
            }

            Playcampus::Dades::PassarellaTemporada::ActualitzarEstats(connectionString);

            //  validar aquí si aquesta lliga pertany al administrador si ho desitges
            if (cercadoraLliga->ObtenirLligaActivaAdmin(idAdmin) != idLliga) { throw gcnew Exception("Aquesta Lliga pertany a un altre Administrador"); }

            // RIT12: Dues temporades d'una mateixa lliga no es poden solapar en dates
            List<Dictionary<String^, String^>^>^ temporadesExistents = ObtenirTemporadesPerLliga(nomLliga);
            for each(Dictionary<String^, String^> ^ t in temporadesExistents) {
                DateTime tInici = Convert::ToDateTime(t["dataInici"]);
                DateTime tFi = Convert::ToDateTime(t["dataFi"]);
                String^ estatTemporada = t->ContainsKey("estat") ? t["estat"] : nullptr;
                bool temporadaTancada = estatTemporada != nullptr &&
                    (estatTemporada->Equals("Finalitzat", StringComparison::OrdinalIgnoreCase) ||
                        estatTemporada->Equals("Finalitzada", StringComparison::OrdinalIgnoreCase) ||
                        estatTemporada->Equals("Retirat", StringComparison::OrdinalIgnoreCase) ||
                        estatTemporada->Equals("Retirada", StringComparison::OrdinalIgnoreCase));

                // Les temporades tancades o retirades es mantenen com a historial i no bloquegen una nova temporada.
                if (!temporadaTancada && dataInici <= tFi && dataFi >= tInici) {
                    throw gcnew Exception("Les dates es solapen amb una temporada existent d'aquesta lliga.");
                }
            }

            // 3. Creem un identificador per la nova temporada
            String^ idTemporada = "T-" + Guid::NewGuid().ToString()->Substring(0, 8);
            String^ estat = "Pròxim"; // Estat per defecte

            // 4. Utilitzem la PassarellaTemporada per insertar el registre a la base de dades
            Playcampus::Dades::PassarellaTemporada^ pTemporada = gcnew Playcampus::Dades::PassarellaTemporada(
                connectionString,
                idTemporada,
                idLliga,
                dataInici,
                dataFi,
                estat
            );

            pTemporada->Insereix();
            pTemporada->InicialitzarEquipsNovaTemporada(idLliga, idTemporada);
        }
        List<Dictionary<String^, String^>^>^ CtrlCrearTemporada::ObtenirTemporadesPerLliga(String^ nomLliga) {
            String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
            Playcampus::Dades::PassarellaTemporada^ passTemp = gcnew Playcampus::Dades::PassarellaTemporada(connStr);


            return passTemp->ObtenirDictTemporadesPerLliga(nomLliga);
        }
    }
}
