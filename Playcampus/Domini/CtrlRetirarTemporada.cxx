#include "pch.h"
#include "CtrlRetirarTemporada.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include <stdexcept>

using namespace System;

namespace Playcampus {
    namespace Domini {

        CtrlRetirarTemporada::CtrlRetirarTemporada() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlRetirarTemporada::RetirarTemporada(String^ correuAdmin) {

            // 1. Obtenir l'usuari (Administrador) per extreure el seu identificador
            Playcampus::Dades::PassarellaUsuari^ usuari = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu(correuAdmin);

            if (usuari == nullptr) {
                throw gcnew Exception("L'usuari administrador no existeix.");
            }

            String^ idAdmin = usuari->GetIdentificador();

            // 2. Obtenir l'ID de la lliga de l'administrador utilitzant la Cercadora
            Playcampus::Dades::CercadoraLliga^ cercLliga = gcnew Playcampus::Dades::CercadoraLliga(connectionString);
            String^ idLliga = cercLliga->ObtenirLligaActivaAdmin(idAdmin);

            if (String::IsNullOrEmpty(idLliga)) {
                throw gcnew Exception("Aquest administrador no té cap lliga assignada.");
            }

            // 3. Fer servir PassarellaTemporada per utilitzar mètode UPDATE per retirar la temporada (EnCurs) d'aquesta lliga
            Playcampus::Dades::PassarellaTemporada^ passTemp = gcnew Playcampus::Dades::PassarellaTemporada(connectionString);
            passTemp->RetirarTemporada(idLliga);
        }

    }
}