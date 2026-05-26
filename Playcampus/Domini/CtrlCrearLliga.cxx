#include "pch.h"
#include "CtrlCrearLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlCrearLliga::CtrlCrearLliga() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlCrearLliga::CrearLliga(String^ idLliga, String^ nom, Disciplina disciplina, String^ descripcio, String^ contrasenya, String^ tipusUsuari, String^ correuUsuari) {
            // RIT5: el nom d'una lliga no pot ser buit.
            if (String::IsNullOrWhiteSpace(nom)) {
                throw gcnew ArgumentException("El nom de la lliga no pot ser buit.");
            }

            // Verificar que l'usuari Ã©s un administrador
            if (tipusUsuari->ToLower() != "administrador") {
                throw gcnew UnauthorizedAccessException("Només els administradors poden crear una lliga.");
            }

            // AquÃ­ es crearia la Lliga. Actualment es crea l'objecte de domini.
            Lliga^ novaLliga = gcnew Lliga(idLliga, nom, disciplina, descripcio, contrasenya);

            String^ idAdmin = nullptr;
            if (!String::IsNullOrEmpty(correuUsuari)) {
                Playcampus::Dades::PassarellaUsuari^ adminUser = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuUsuari);
                if (adminUser != nullptr && adminUser->GetIdentificador() != nullptr) {
                    idAdmin = adminUser->GetIdentificador()->Trim(); // Utilitzem Trim() per assegurar que no hi hagi espais en blanc que trenquin la clau
                }
            }

            // Guardar a la base de dades utilitzant la passarella
            try {
                Playcampus::Dades::PassarellaLliga^ pl = gcnew Playcampus::Dades::PassarellaLliga(connectionString, idLliga, nom, disciplina, descripcio, contrasenya, idAdmin);
                pl->Insereix();
            }
            catch (Exception^ ex) {
                // Afegim l'idAdmin a l'excepciÃ³ per veure exactament quin s'estÃ  enviant a MySql 
                String^ errorPrefix = "L'ID de l'admin enviat és: '" + (idAdmin == nullptr ? "NULL" : idAdmin) + "'. ";
                throw gcnew Exception(errorPrefix + ex->Message);
            }
        }
        bool CtrlCrearLliga::ExisteixLliga(String^ nomLliga) {
            Playcampus::Dades::PassarellaLliga^ p = gcnew Playcampus::Dades::PassarellaLliga(connectionString);
            return p->ExisteixPerNom(nomLliga);
        }

        bool CtrlCrearLliga::TeLligaActiva(String^ correuUsuari) {
            String^ idAdmin = nullptr;
            if (!String::IsNullOrEmpty(correuUsuari)) {
                Playcampus::Dades::PassarellaUsuari^ adminUser = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuUsuari);
                if (adminUser != nullptr && adminUser->GetIdentificador() != nullptr) {
                    idAdmin = adminUser->GetIdentificador()->Trim();
                }
            }

            if (idAdmin == nullptr) return false;

            Playcampus::Dades::PassarellaLliga^ pl = gcnew Playcampus::Dades::PassarellaLliga(connectionString);
            return pl->TeLligaActivaAdmin(idAdmin);
        }
    }
}
