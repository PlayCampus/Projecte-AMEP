#include "pch.h"
#include "CtrlAssignarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlAssignarJugador::CtrlAssignarJugador() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlAssignarJugador::ValidarUsuariCapita(String^ correuCapita) {
            if (String::IsNullOrWhiteSpace(correuCapita)) {
                throw gcnew UnauthorizedAccessException("No hi ha cap usuari connectat.");
            }

            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuari = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            if (usuari == nullptr) {
                throw gcnew UnauthorizedAccessException("L'usuari connectat no existeix.");
            }

            if (String::IsNullOrWhiteSpace(usuari->GetTipus()) || usuari->GetTipus()->ToLower() != "capita") {
                throw gcnew UnauthorizedAccessException("Només els capitans poden assignar jugadors a partits.");
            }
        }

        String^ CtrlAssignarJugador::ObtenirIdEquipCapita(String^ correuCapita) {
            ValidarUsuariCapita(correuCapita);
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);
            CercadoraSistema^ cercadoraSistema = gcnew CercadoraSistema(connectionString);
            String^ idEquip = cercadoraSistema->ObtenirIdEquipCapitaPerIdentificador(usuariCapita->GetIdentificador());
            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té cap equip registrat.");
            }
            return idEquip;
        }

        bool CtrlAssignarJugador::PartitDisponiblePerEquip(String^ idPartit, String^ idEquip) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->PartitDisponiblePerEquip(idPartit, idEquip);
        }

        bool CtrlAssignarJugador::JugadorPertanyAEquip(String^ idJugador, String^ idEquip) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->JugadorPertanyAEquip(idJugador, idEquip);
        }

        bool CtrlAssignarJugador::AssignacioJaExisteix(String^ idPartit, String^ idJugador) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->AssignacioJugadorPartitExisteix(idPartit, idJugador);
        }

        List<Dictionary<String^, String^>^>^ CtrlAssignarJugador::ObtenirPartitsDisponibles(String^ correuCapita) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirPartitsDisponiblesEquip(idEquip);
        }

        List<Dictionary<String^, String^>^>^ CtrlAssignarJugador::ObtenirJugadorsEquip(String^ correuCapita) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirJugadorsEquipPerAssignacio(idEquip);
        }

        String^ CtrlAssignarJugador::AssignarJugador(String^ correuCapita, String^ idPartit, String^ idJugador) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);

            if (!PartitDisponiblePerEquip(idPartit, idEquip)) {
                throw gcnew Exception("El partit seleccionat no pertany al teu equip o ja està finalitzat.");
            }

            if (!JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception("El jugador seleccionat no pertany al teu equip.");
            }

            if (AssignacioJaExisteix(idPartit, idJugador)) {
                throw gcnew Exception("Aquest jugador ja està assignat a aquest partit.");
            }

            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->InserirAssignacioJugadorPartit(idPartit, idJugador);
            return "Jugador assignat correctament al partit.";
        }
    }
}
