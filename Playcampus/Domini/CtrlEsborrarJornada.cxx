#include "pch.h"
#include "CtrlEsborrarJornada.hxx"

#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraTemporada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/PassarellaJornada.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {

        CtrlEsborrarJornada::CtrlEsborrarJornada() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        List<Dictionary<String^, String^>^>^ CtrlEsborrarJornada::ObtenirTemporadesAdmin(String^ correuAdmin) {
            Playcampus::Dades::CercadoraTemporada^ cercaT = gcnew Playcampus::Dades::CercadoraTemporada(connectionString);
            return cercaT->ObtenirTemporadesAdmin(correuAdmin);
        }

        List<Dictionary<String^, String^>^>^ CtrlEsborrarJornada::ObtenirJornadesPerTemporada(String^ idTemporada) {
            Playcampus::Dades::CercadoraJornada^ cercaJ = gcnew Playcampus::Dades::CercadoraJornada(connectionString);
            return cercaJ->ObtenirDictJornadesPerTemporada(idTemporada);
        }

        void CtrlEsborrarJornada::EsborrarJornada(String^ idJornada) {
            Playcampus::Dades::PassarellaJornada^ passJornada = gcnew Playcampus::Dades::PassarellaJornada(connectionString);
            passJornada->EsborrarJornada(idJornada);
        }
    }
}
