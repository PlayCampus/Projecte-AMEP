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
            // PRE: correuAdmin identifica l'administrador actual.
            // POST: retorna només temporades no finalitzades ni retirades.
            Playcampus::Dades::CercadoraTemporada^ cercaT = gcnew Playcampus::Dades::CercadoraTemporada(connectionString);
            List<Dictionary<String^, String^>^>^ totes = cercaT->ObtenirTemporadesAdmin(correuAdmin);
            List<Dictionary<String^, String^>^>^ disponibles = gcnew List<Dictionary<String^, String^>^>();

            if (totes != nullptr) {
                for (int i = 0; i < totes->Count; i++) {
                    Dictionary<String^, String^>^ temp = totes[i];
                    String^ estat = L"";
                    if (temp != nullptr && temp->ContainsKey("estat") && temp["estat"] != nullptr) {
                        estat = temp["estat"]->ToLower();
                    }
                    if (estat != L"finalitzat" && estat != L"retirada") {
                        disponibles->Add(temp);
                    }
                }
            }

            return disponibles;
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
