#include "pch.h"
#include "EtiquetesEditarPartit.hxx"

using namespace System;
using namespace System::Collections::Generic;

namespace Playcampus {
    namespace Domini {
        Dictionary<String^, String^>^ EtiquetesEditarPartit::ObtenirEtiquetesEditarPartit(String^ disciplina) {
            String^ disciplinaNormalitzada = NormalitzarDisciplina(disciplina);
            Dictionary<String^, String^>^ etiquetes = gcnew Dictionary<String^, String^>();

            etiquetes["disciplinaOriginal"] = String::IsNullOrWhiteSpace(disciplina) ? L"No especificada" : disciplina;
            etiquetes["disciplinaNormalitzada"] = disciplinaNormalitzada;

            if (disciplinaNormalitzada == L"futbol") {
                etiquetes["titol"] = L"Editar Partit i Estadístiques - Futbol";
                etiquetes["marcadorLocal"] = L"Gols local:";
                etiquetes["marcadorVisitant"] = L"Gols visitant:";
                etiquetes["nomMarcadorPlural"] = L"gols";
                etiquetes["estadistica1"] = L"Gols";
                etiquetes["estadistica2"] = L"Assistències";
                etiquetes["estadistica3"] = L"Targetes grogues";
                etiquetes["estadistica4"] = L"Targetes vermelles";
            }
            else if (disciplinaNormalitzada == L"basquet") {
                etiquetes["titol"] = L"Editar Partit i Estadístiques - Bàsquet";
                etiquetes["marcadorLocal"] = L"Punts equip local:";
                etiquetes["marcadorVisitant"] = L"Punts equip visitant:";
                etiquetes["nomMarcadorPlural"] = L"punts";
                etiquetes["estadistica1"] = L"Punts";
                etiquetes["estadistica2"] = L"Assistències";
                etiquetes["estadistica3"] = L"Faltes lleus";
                etiquetes["estadistica4"] = L"Faltes greus/tècniques";
            }
            else if (disciplinaNormalitzada == L"volei") {
                etiquetes["titol"] = L"Editar Partit i Estadístiques - Vòlei";
                etiquetes["marcadorLocal"] = L"Punts equip local:";
                etiquetes["marcadorVisitant"] = L"Punts equip visitant:";
                etiquetes["nomMarcadorPlural"] = L"punts";
                etiquetes["estadistica1"] = L"Punts";
                etiquetes["estadistica2"] = L"Sets guanyats";
                etiquetes["estadistica3"] = L"Faltes de servei";
                etiquetes["estadistica4"] = L"Errors";
            }
            else {
                etiquetes["titol"] = L"Editar Partit i Estadístiques";
                etiquetes["marcadorLocal"] = L"Punts local:";
                etiquetes["marcadorVisitant"] = L"Punts visitant:";
                etiquetes["nomMarcadorPlural"] = L"punts";
                etiquetes["estadistica1"] = L"Anotacions";
                etiquetes["estadistica2"] = L"Assistències";
                etiquetes["estadistica3"] = L"Sancions lleus";
                etiquetes["estadistica4"] = L"Sancions greus";
            }

            return etiquetes;
        }

        String^ EtiquetesEditarPartit::NormalitzarDisciplina(String^ disciplina) {
            String^ resultat = L"generic";

            if (!String::IsNullOrWhiteSpace(disciplina)) {
                String^ d = disciplina->Trim()->ToLowerInvariant();
                if (d->Contains(L"fut") || d->Contains(L"football") || d->Contains(L"soccer")) {
                    resultat = L"futbol";
                }
                else if (d->Contains(L"basq") || d->Contains(L"bàsq") || d->Contains(L"basket")) {
                    resultat = L"basquet";
                }
                else if (d->Contains(L"vol") || d->Contains(L"vòl") || d->Contains(L"volei") || d->Contains(L"vòlei") || d->Contains(L"voleibol") || d->Contains(L"volleyball")) {
                    resultat = L"volei";
                }
            }

            return resultat;
        }
    }
}
