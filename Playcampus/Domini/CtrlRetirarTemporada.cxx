#include "pch.h"
#include "CtrlRetirarTemporada.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraTemporada.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/PassarellaJornada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/PassarellaCapita.hxx"

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
                throw gcnew Exception("Aquest administrador no t  cap lliga assignada.");
            }

            // 3. Obtenir l'ID de la temporada en curs abans de retirar-la
            Playcampus::Dades::CercadoraTemporada^ cercTemporada = gcnew Playcampus::Dades::CercadoraTemporada(connectionString);
            String^ idTemporada = cercTemporada->ObtenirIdTemporadaEnCurs(idLliga);

            if (String::IsNullOrEmpty(idTemporada)) {
                // No hi ha temporada "En Curs", no cal fer res m s.
                return;
            }

            // 4. Fer servir PassarellaTemporada per utilitzar m tode UPDATE per retirar la temporada (EnCurs) d'aquesta lliga
            Playcampus::Dades::PassarellaTemporada^ passTemp = gcnew Playcampus::Dades::PassarellaTemporada(connectionString);
            passTemp->RetirarTemporada(idLliga);
            passTemp->InicialitzarEquipsTemporadaSeguent(idLliga, idTemporada);

            /* con la nueva implementaci n de EquipTemporada no hace falta hacer esto
             5. Obtenir tots els equips de la temporada retirada
            Playcampus::Dades::CercadoraEquip^ cercEquip = gcnew Playcampus::Dades::CercadoraEquip(connectionString);
            List<String^>^ idsEquips = cercEquip->ObtenirIdsEquipsPerTemporada(idTemporada);


             6. Per a cada equip, desassignar el capit
            Playcampus::Dades::PassarellaCapita^ passCapita = gcnew Playcampus::Dades::PassarellaCapita(connectionString);
            for each (String ^ idEquip in idsEquips) {
                passCapita->DesassignarEquip(idEquip);
            }
            */

            // 7. Retirar totes les jornades de la temporada
            Playcampus::Dades::PassarellaJornada^ passJornada = gcnew Playcampus::Dades::PassarellaJornada(connectionString);

            passJornada->RetirarJornadesTemporada(idTemporada);

        }

    }
}