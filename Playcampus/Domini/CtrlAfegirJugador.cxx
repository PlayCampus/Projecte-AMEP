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

        String^ CtrlAfegirJugador::AfegirJugador(String^ correuEstudiant, int dorsal, String^ posicio, String^ correuCapita, DateTime dataNaixement) {
            String^ connStr = ConnexioBD::ObtenirConnectionString();

            // RIT27: Validar que dorsal > 0 i dorsal <= 99
            if (dorsal <= 0 || dorsal > 99) {
                throw gcnew Exception("El dorsal ha de ser més gran que 0 i menor o igual que 99.");
            }

            // RIT29: Validar que la dataNaixement sigui anterior a la data actual
            if (dataNaixement >= DateTime::Now) {
                throw gcnew Exception("La data de naixement ha de ser anterior a la data actual.");
            }

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

            PassarellaJugador^ jugador = gcnew PassarellaJugador(connStr, dorsal, posicio, dataNaixement);
            jugador->SetIdEquip(idEquip);
            jugador->Insereix(usuariEstudiant->GetIdentificador());

            if (usuariEstudiant->GetTipus() != "Jugador") {
                usuariEstudiant->ActualitzaTipus("Jugador");
            }

            return "Jugador afegit correctament!";
        }
    }
}
