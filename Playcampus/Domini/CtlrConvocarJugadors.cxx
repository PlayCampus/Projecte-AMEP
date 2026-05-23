#include "pch.h"
#include "CtlrConvocarJugadors.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaSistema.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtlrConvocarJugadors::CtlrConvocarJugadors() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirPartitsCapita(String^ correuCapita) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirPartitsCapita(correuCapita);
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirConvocatoriaPartit(String^ idPartit) {
            return ObtenirPartitsDeLEquip(idPartit);
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirPartitsDeLEquip(String^ idEquip) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirPartitsDeLEquip(idEquip);
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirEstatConvocatoria(idPartit, idEquip);
        }

        void CtlrConvocarJugadors::ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat) {
            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->ActualitzarConvocatoria(idPartit, idJugador, convocat);
        }

        void CtlrConvocarJugadors::ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix) {
            PassarellaSistema^ passarella = gcnew PassarellaSistema(connectionString);
            passarella->ConfirmarAssistencia(idPartit, idJugador, assisteix);
        }

        Dictionary<String^, String^>^ CtlrConvocarJugadors::ObtenirAvisPendent(String^ correuJugador) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirAvisPendent(correuJugador);
        }
    }
}
