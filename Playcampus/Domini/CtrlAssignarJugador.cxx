#include "pch.h"
#include "CtrlAssignarJugador.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraEquip.hxx"
#include "../Dades/CercadoraJugador.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/PassarellaPartit.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtrlAssignarJugador::CtrlAssignarJugador() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        void CtrlAssignarJugador::ValidarUsuariCapita(String^ correuCapita) {
            CercadoraUsuari^ cercadoraUsuari = gcnew CercadoraUsuari(connectionString);
            PassarellaUsuari^ usuariCapita = cercadoraUsuari->LlegeixPerCorreu(correuCapita);

            if (usuariCapita == nullptr) {
                throw gcnew Exception("L'usuari capità no existeix.");
            }

            if (usuariCapita->GetTipus() != "Capita") {
                throw gcnew Exception("Només els capitans poden assignar jugadors a partits.");
            }
        }

        String^ CtrlAssignarJugador::ObtenirIdEquipCapita(String^ correuCapita) {
            ValidarUsuariCapita(correuCapita);

            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            String^ idEquip = cercadoraEquip->ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idEquip)) {
                throw gcnew Exception("El capità no té cap equip registrat.");
            }

            return idEquip;
        }

        List<Dictionary<String^, String^>^>^ CtrlAssignarJugador::ObtenirPartitsDisponibles(String^ correuCapita) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);
            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            return cercadoraPartit->ObtenirPartitsDisponiblesPerEquip(idEquip);
        }

        List<Dictionary<String^, String^>^>^ CtrlAssignarJugador::ObtenirJugadorsEquip(String^ correuCapita) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);
            CercadoraEquip^ cercadoraEquip = gcnew CercadoraEquip(connectionString);
            return cercadoraEquip->ObtenirJugadorsEquip(idEquip);
        }

        String^ CtrlAssignarJugador::AssignarJugador(String^ correuCapita, String^ idPartit, String^ idJugador) {
            String^ idEquip = ObtenirIdEquipCapita(correuCapita);

            if (String::IsNullOrWhiteSpace(idPartit)) {
                throw gcnew Exception("Cal seleccionar un partit.");
            }

            if (String::IsNullOrWhiteSpace(idJugador)) {
                throw gcnew Exception("Cal seleccionar un jugador.");
            }

            CercadoraPartit^ cercadoraPartit = gcnew CercadoraPartit(connectionString);
            CercadoraJugador^ cercadoraJugador = gcnew CercadoraJugador(connectionString);

            if (!cercadoraPartit->PartitDisponiblePerEquip(idPartit, idEquip)) {
                throw gcnew Exception("El partit seleccionat no està disponible per a l'equip del capità o ja està finalitzat.");
            }

            if (!cercadoraJugador->JugadorPertanyAEquip(idJugador, idEquip)) {
                throw gcnew Exception("El jugador seleccionat no pertany a l'equip del capità.");
            }

            if (cercadoraPartit->AssignacioJugadorPartitExisteix(idPartit, idJugador)) {
                throw gcnew Exception("Aquest jugador ja està assignat a aquest partit.");
            }

            PassarellaPartit^ passarellaPartit = gcnew PassarellaPartit(connectionString);
            passarellaPartit->AssignarJugadorAPartit(idPartit, idJugador);

            return "Jugador assignat correctament al partit.";
        }
    }
}
