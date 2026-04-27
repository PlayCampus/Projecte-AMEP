#include "pch.h"
#include "CtrlConvocatoria.hxx"
#include "../Dades/PassarellaConvocatoria.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        CtrlConvocatoria::CtrlConvocatoria(String^ connStr) {
            this->connectionString = connStr;
        }

        void CtrlConvocatoria::CrearConvocatoria(String^ idPartit, String^ idEquip) {
            Playcampus::Dades::PassarellaConvocatoria^ passarella = gcnew Playcampus::Dades::PassarellaConvocatoria(connectionString);
            passarella->CrearConvocatoria(idPartit, idEquip);
        }

        void CtrlConvocatoria::AfegirJugadorConvocatoria(String^ idConvocatoria, String^ nomJugador) {
            Playcampus::Dades::PassarellaConvocatoria^ passarella = gcnew Playcampus::Dades::PassarellaConvocatoria(connectionString);
            passarella->AfegirJugadorConvocatoria(idConvocatoria, nomJugador);
        }

        void CtrlConvocatoria::ActualitzarDisponibilitatJugador(String^ idConvocatoria, String^ nomJugador, bool assistira) {
            Playcampus::Dades::PassarellaConvocatoria^ passarella = gcnew Playcampus::Dades::PassarellaConvocatoria(connectionString);
            passarella->ActualitzarDisponibilitatJugador(idConvocatoria, nomJugador, assistira);
        }
    }
}
