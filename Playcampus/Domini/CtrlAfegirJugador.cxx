#include "pch.h"
#include "CtrlAfegirJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/PassarellaJugador.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/CercadoraEquip.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlAfegirJugador::CtrlAfegirJugador() {
        }

        String^ CtrlAfegirJugador::AfegirJugador(String^ correuEstudiant, int dorsal, String^ posicio, String^ correuCapita) {
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            CercadoraUsuari^ cercadora = gcnew CercadoraUsuari(connStr);
            PassarellaUsuari^ usuariEstudiant = cercadora->LlegeixPerCorreu(correuEstudiant);

            if (usuariEstudiant == nullptr) {
                throw gcnew Exception("L'usuari estudiant no existeix.");
            }

            if (usuariEstudiant->GetTipus() != "Estudiant" && usuariEstudiant->GetTipus() != "Jugador") {
                throw gcnew Exception("L'usuari no és de tipus Estudiant ni Jugador.");
            }

            PassarellaUsuari^ usuariCapita = cercadora->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew Exception("L'usuari capta no existeix.");
            }

            if (usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("L'usuari no és de tipus Capita.");
            }

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connStr);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capta no té equip assignat.");
            }

            if (!cercadoraEquip->ExisteixEquipPerId(idEquip)) {
                throw gcnew Exception("L'equip associat al capità no existeix o no és vàlid.");
            }

            CercadoraJugador^ cerJugador = gcnew CercadoraJugador(connStr);
            if (cerJugador->ExisteixDorsalEnEquip(dorsal, idEquip)) {
                throw gcnew Exception("El dorsal " + dorsal.ToString() + " ja existeix en aquest equip.");
            }

            PassarellaJugador^ jugador = gcnew PassarellaJugador(connStr, dorsal, posicio, DateTime::Now);
            jugador->SetIdEquip(idEquip);
            jugador->Insereix(usuariEstudiant->GetIdentificador());

            if (usuariEstudiant->GetTipus() != "Jugador") {
                usuariEstudiant->ActualitzaTipus("Jugador");
            }

            return "Jugador afegit correctament!";
        }
    }
}
