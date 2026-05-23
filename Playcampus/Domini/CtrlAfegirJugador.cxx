#include "pch.h"
#include "CtrlAfegirJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/PassarellaJugador.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include "../Dades/CercadoraSistema.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlAfegirJugador::CtrlAfegirJugador() {
        }

        String^ CtrlAfegirJugador::AfegirJugador(String^ correuEstudiant, int dorsal, String^ posicio, String^ correuCapita) {
            // Obtenir connexiÃ³ a la BD
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            // Cercar l'usuari estudiant
            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connStr);
            PassarellaUsuari^ usuariEstudiant = cercadora->LlegeixPerCorreu(correuEstudiant);

            if (usuariEstudiant == nullptr) {
                throw gcnew Exception("L'usuari estudiant no existeix.");
            }

            // Permetem tornar a inscriure un usuari que ja Ã©s de tipus Jugador perÃ² no estÃ  vinculat a cap equip
            // (p.ex. desprÃ©s d'haver estat expulsat). En aquest cas, es crearÃ  un nou registre a la taula Jugador.
            if (usuariEstudiant->GetTipus() != "Estudiant" && usuariEstudiant->GetTipus() != "Jugador") {
                throw gcnew Exception("L'usuari no és de tipus Estudiant ni Jugador.");
            }

            // Cercar el capta per obtenir l'idEquip
            PassarellaUsuari^ usuariCapita = cercadora->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew Exception("L'usuari capta no existeix.");
            }

            if (usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("L'usuari no és de tipus Capita.");
            }

            CercadoraSistema^ cercadoraSistema = gcnew CercadoraSistema(connStr);
            String^ idEquip = cercadoraSistema->ObtenirIdEquipCapitaPerIdentificador(usuariCapita->GetIdentificador());
            if (!String::IsNullOrWhiteSpace(idEquip)) {
                idEquip = idEquip->Trim();
            }

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capta no té equip assignat.");
            }

            if (!cercadoraSistema->ExisteixEquip(idEquip)) {
                throw gcnew Exception("L'equip associat al capità  no existeix o no és vàlid.");
            }

            // Verificar que el dorsal no existeix en l'equip
            CercadoraJugador^ cerJugador = gcnew CercadoraJugador(connStr);
            if (cerJugador->ExisteixDorsalEnEquip(dorsal, idEquip)) {
                throw gcnew Exception("El dorsal " + dorsal.ToString() + " ja existeix en aquest equip.");
            }

            // Crear el jugador nou
            PassarellaJugador^ jugador = gcnew PassarellaJugador(connStr, dorsal, posicio, DateTime::Now);
            jugador->SetIdEquip(idEquip);

            // Inserir jugador (passant idJugador que Ã©s el identificador de l'Usuari)
            jugador->Insereix(usuariEstudiant->GetIdentificador());

            // Actualitzar tipus d'usuari de Estudiant a Jugador (si ja era Jugador, no cal)
            if (usuariEstudiant->GetTipus() != "Jugador") {
                usuariEstudiant->ActualitzaTipus("Jugador");
            }

            return "Jugador afegit correctament!";
        }
    }
}
