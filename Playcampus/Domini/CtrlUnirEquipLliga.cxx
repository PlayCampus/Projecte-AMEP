#include "pch.h"
#include "CtrlUnirEquipLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraSistema.hxx"
#include "../Dades/PassarellaEquip.hxx"

using namespace System;
using namespace Playcampus::Dades;

namespace Playcampus {
    namespace Domini {
        CtrlUnirEquipLliga::CtrlUnirEquipLliga() {
            connectionString = ConnexioBD::ObtenirConnectionString();
        }

        String^ CtrlUnirEquipLliga::ComprovarSiLligaExisteix(String^ nomLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            return cercadora->ObtenirIdLligaPerNom(nomLliga);
        }

        bool CtrlUnirEquipLliga::ValidarContrasenyaLliga(String^ nomLliga, String^ pass) {
            bool valida = false;
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            String^ contrasenya = cercadora->ObtenirContrasenyaLligaPerNom(nomLliga);
            if (contrasenya != nullptr && contrasenya == pass) {
                valida = true;
            }
            return valida;
        }

        String^ CtrlUnirEquipLliga::VincularEquip(String^ correuCapita, String^ nomLliga) {
            CercadoraSistema^ cercadora = gcnew CercadoraSistema(connectionString);
            String^ idLliga = cercadora->ObtenirIdLligaPerNom(nomLliga);
            if (String::IsNullOrWhiteSpace(idLliga)) {
                throw gcnew Exception("La lliga indicada no existeix.");
            }

            String^ idEquipRecuperat = cercadora->ObtenirIdEquipCapitaPerCorreu(correuCapita);
            if (String::IsNullOrWhiteSpace(idEquipRecuperat)) {
                throw gcnew Exception("Aquest capità no té cap equip registrat.");
            }

            PassarellaEquip^ equipDB = PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
            if (equipDB == nullptr) {
                throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
            }

            String^ idTemporada = cercadora->ObtenirIdTemporadaRellevant(idLliga);
            if (String::IsNullOrWhiteSpace(idTemporada)) {
                throw gcnew Exception("La lliga no té cap temporada disponible.");
            }

            equipDB->SetIdTemporada(idTemporada);
            equipDB->Modifica();
            return "Equip unit correctament a la lliga.";
        }
    }
}
