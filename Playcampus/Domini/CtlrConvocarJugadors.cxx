#include "pch.h"
#include "CtlrConvocarJugadors.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/PassarellaPartit.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {

        CtlrConvocarJugadors::CtlrConvocarJugadors() {
            this->connectionString = ConnexioBD::ObtenirConnectionString();
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirPartitsCapita(String^ correuCapita) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirPartitsCapita(correuCapita);
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirConvocatoriaPartit(String^ idPartit) {
            return ObtenirPartitsDeLEquip(idPartit);
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirPartitsDeLEquip(String^ idEquip) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirPartitsDeLEquip(idEquip);
        }

        List<Dictionary<String^, String^>^>^ CtlrConvocarJugadors::ObtenirEstatConvocatoria(String^ idPartit, String^ idEquip) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirEstatConvocatoria(idPartit, idEquip);
        }

        void CtlrConvocarJugadors::ActualitzarConvocatoria(String^ idPartit, String^ idJugador, Nullable<bool> convocat) {
            PassarellaPartit^ passarella = gcnew PassarellaPartit(connectionString);
            passarella->ActualitzarConvocatoria(idPartit, idJugador, convocat);
        }

        void CtlrConvocarJugadors::ConfirmarAssistencia(String^ idPartit, String^ idJugador, bool assisteix) {
            PassarellaPartit^ passarella = gcnew PassarellaPartit(connectionString);
            passarella->ConfirmarAssistencia(idPartit, idJugador, assisteix);
        }

        Dictionary<String^, String^>^ CtlrConvocarJugadors::ObtenirAvisPendent(String^ correuJugador) {
            CercadoraPartit^ cercadora = gcnew CercadoraPartit(connectionString);
            return cercadora->ObtenirAvisPendent(correuJugador);
        }
    }
}
