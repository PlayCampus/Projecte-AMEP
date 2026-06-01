#include "pch.h"
#include "CtrlEsborrarPartit.hxx"

// Incloem les dependències de la capa de Dades només aquí
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaPartit.hxx"
#include "../Dades/CercadoraTemporada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/CercadoraPartit.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {

        CtrlEsborrarPartit::CtrlEsborrarPartit() {
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        // Delegació a CercadoraTemporada
        List<Dictionary<String^, String^>^>^ CtrlEsborrarPartit::ObtenirTemporadesAdmin(String^ correuAdmin) {
            // Pre: correuAdmin identifica l'administrador actual.
            // Post: retorna només temporades no finalitzades perquè no es puguin esborrar partits de temporades tancades.
            Playcampus::Dades::CercadoraTemporada^ cercaT = gcnew Playcampus::Dades::CercadoraTemporada(connectionString);
            List<Dictionary<String^, String^>^>^ totes = cercaT->ObtenirTemporadesAdmin(correuAdmin);
            List<Dictionary<String^, String^>^>^ disponibles = gcnew List<Dictionary<String^, String^>^>();

            for (int i = 0; i < totes->Count; i++) {
                Dictionary<String^, String^>^ temp = totes[i];
                String^ estat = L"";
                if (temp->ContainsKey("estat") && temp["estat"] != nullptr) {
                    estat = temp["estat"]->ToLower();
                }
                if (estat != L"finalitzat" && estat != L"retirada") {
                    disponibles->Add(temp);
                }
            }

            return disponibles;
        }

        // Delegació a CercadoraJornada
        List<Dictionary<String^, String^>^>^ CtrlEsborrarPartit::ObtenirJornadesPerTemporada(String^ idTemporada) {
            Playcampus::Dades::CercadoraJornada^ cercaJ = gcnew Playcampus::Dades::CercadoraJornada(connectionString);
            return cercaJ->ObtenirDictJornadesPerTemporada(idTemporada); // O "ObtenirDictJornadesPerTemporada" depenent de com ho tens a la capçelera
        }

        // Delegació a CercadoraPartit
        List<Dictionary<String^, String^>^>^ CtrlEsborrarPartit::ObtenirPartitsPerJornada(String^ idJornada) {
            Playcampus::Dades::CercadoraPartit^ cercaP = gcnew Playcampus::Dades::CercadoraPartit(connectionString);
            return cercaP->ObtenirPartitsPerJornada(idJornada);
        }

        // Interacció amb PassarellaPartit
        void CtrlEsborrarPartit::EsborrarPartit(String^ idPartit) {
            Playcampus::Dades::PassarellaPartit^ passPartit = gcnew Playcampus::Dades::PassarellaPartit(connectionString);
            passPartit->EsborrarPartit(idPartit);
        }
    }
}
