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

        void CtrlCrearTemporada::CrearTemporada(DateTime dataInici, DateTime dataFi, String^ correuAdmin, String^ nomLliga) {
            // RIT9: La dataInici ha de ser anterior a la dataFi
            if (dataInici >= dataFi) {
                throw gcnew ArgumentException("La data d'inici ha de ser anterior a la data final.");
            }

            String^ idAdmin = nullptr;

            // 1. Busquem l'ID de l'administrador mitjançant el seu correu
            if (!String::IsNullOrEmpty(correuAdmin)) {
                Playcampus::Dades::PassarellaUsuari^ adminUser = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu( correuAdmin);
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

            //  validar aquí si aquesta lliga pertany al administrador si ho desitges
            if (cercadoraLliga->ObtenirLligaActivaAdmin(idAdmin) != idLliga) { throw gcnew Exception("Aquesta Lliga pertany a un altre Administrador"); }

            // RIT12: Dues temporades d'una mateixa lliga no es poden solapar en dates
            List<Dictionary<String^, String^>^>^ temporadesExistents = ObtenirTemporadesPerLliga(nomLliga);
            for each (Dictionary<String^, String^>^ t in temporadesExistents) {
                DateTime tInici = Convert::ToDateTime(t["dataInici"]);
                DateTime tFi = Convert::ToDateTime(t["dataFi"]);

                // Si la nova temporada comença abans que acabi l'existent, i acaba després que comenci l'existent, hi ha solapament
                if (dataInici <= tFi && dataFi >= tInici) {
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
        }
        List<Dictionary<String^, String^>^>^ CtrlCrearTemporada::ObtenirTemporadesPerLliga(String^ nomLliga) {
            String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
            Playcampus::Dades::PassarellaTemporada^ passTemp = gcnew Playcampus::Dades::PassarellaTemporada(connStr);

            
            return passTemp->ObtenirDictTemporadesPerLliga(nomLliga);
        }
    }
}
