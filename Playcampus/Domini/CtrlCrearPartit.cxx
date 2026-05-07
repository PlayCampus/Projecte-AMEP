#include "pch.h"
#include "CtrlCrearPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaPartit.hxx"
#include "../Dades/PassarellaLliga.hxx"
#include "../Dades/PassarellaUsuari.hxx"
#include "../Dades/CercadoraUsuari.hxx"
#include "../Dades/PassarellaTemporada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/PassarellaJornada.hxx"
#include "../Dades/PassarellaEquip.hxx" // Necesario para buscar los equipos
#include <stdexcept>

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Domini {
        CtrlCrearPartit::CtrlCrearPartit() {
            // Seguint la mateixa convenció que CtrlEnregistrarEquip
            connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
        }

        void CtrlCrearPartit::CrearPartit(DateTime dataHora, String^ ubicacio, String^ nomEquipLocal, String^ nomEquipVisitant, String^ idJornada, String^ tipusUsuari) {

            // 1. Validar que l'usuari és Administrador
            if (String::IsNullOrEmpty(tipusUsuari) || tipusUsuari->ToLower() != "administrador") {
                throw gcnew UnauthorizedAccessException("Només els administradors poden crear un partit.");
            }

            // 2. No es poden enfrontar el mateix equip
            if (nomEquipLocal->Equals(nomEquipVisitant, StringComparison::OrdinalIgnoreCase)) {
                throw gcnew ArgumentException("Un equip no pot jugar contra ell mateix.");
            }

            try {
                // 3. Buscar els IDs d'Equip a la BD
                String^ idEquipLocal = ObtenirIdEquip(nomEquipLocal);
                String^ idEquipVisitant = ObtenirIdEquip(nomEquipVisitant);

                if (String::IsNullOrEmpty(idEquipLocal)) {
                    throw gcnew Exception("L'equip local '" + nomEquipLocal + "' no existeix.");
                }
                if (String::IsNullOrEmpty(idEquipVisitant)) {
                    throw gcnew Exception("L'equip visitant '" + nomEquipVisitant + "' no existeix.");
                }
                if (String::IsNullOrEmpty(idJornada)) {
                    throw gcnew Exception("La jornada no s'ha trobat o no és vàlida.");
                }

                // 4. Crear el partit (L'Estat inicial serà 'Pendent')
                String^ estat = "Pendent";
                
                Playcampus::Dades::PassarellaPartit^ partit = gcnew Playcampus::Dades::PassarellaPartit(
                    connectionString, 
                    nullptr, // ID es genera a dins si és null
                    dataHora, 
                    ubicacio, 
                    estat, 
                    0, 0, // Gols a 0
                    idJornada, 
                    idEquipLocal, 
                    idEquipVisitant
                );

                partit->InsereixPartit();
            }
            catch (Exception^ ex) {
                throw gcnew Exception("Error al inserir el partit: " + ex->Message);
            }
        }

        String^ CtrlCrearPartit::ObtenirIdEquip(String^ nomEquip) {
            String^ idRetorn = nullptr;
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT idEquip FROM Equip WHERE nom = @nom LIMIT 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nom", nomEquip);
                Object^ result = cmd->ExecuteScalar();
                if (result != nullptr) {
                    idRetorn = result->ToString();
                }
            }
            finally {
                delete conn;
            }
            return idRetorn;
        }

        // Validar Admin 
        bool CtrlCrearPartit::ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin) {
            Playcampus::Dades::PassarellaUsuari^ usuari = (gcnew Playcampus::Dades::CercadoraUsuari(connectionString))->LlegeixPerCorreu( correuAdmin);
            if (usuari == nullptr) return false;

            Playcampus::Dades::PassarellaLliga^ passLliga = gcnew Playcampus::Dades::PassarellaLliga(connectionString);

            // CORRECCIÓN: Pasar el 'correuAdmin' en vez del identificador
            return passLliga->EsAdministradorLliga(nomLliga, correuAdmin);
        }

        // Obtenir Temporades 
        List<Dictionary<String^, String^>^>^ CtrlCrearPartit::ObtenirTemporadesLliga(String^ nomLliga) {
            Playcampus::Dades::PassarellaTemporada^ passTemp = gcnew Playcampus::Dades::PassarellaTemporada(connectionString);
            return passTemp->ObtenirDictTemporadesPerLliga(nomLliga);
        }

        //  Obtenir Jornades
        List<Dictionary<String^, String^>^>^ CtrlCrearPartit::ObtenirJornadesTemporada(String^ idTemporada) {
            Playcampus::Dades::CercadoraJornada^ cercJor = gcnew Playcampus::Dades::CercadoraJornada(connectionString);
            return cercJor->ObtenirDictJornadesPerTemporada(idTemporada);
        }

        // Obtenir Equips de la Lliga per nom
        List<String^>^ CtrlCrearPartit::ObtenirNomsEquipsPerLliga(String^ nomLliga) {
            List<String^>^ equips = gcnew List<String^>();
            MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
            try {
                conn->Open();
                String^ query = "SELECT e.nom FROM Equip e INNER JOIN Temporada t ON e.idTemporada = t.idTemporada INNER JOIN Lliga l ON t.idLliga = l.idLliga WHERE l.nom = @nomLliga";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@nomLliga", nomLliga);
                MySqlDataReader^ reader = cmd->ExecuteReader();
                while (reader->Read()) {
                    equips->Add(reader->GetString("nom"));
                }
                reader->Close();
            }
            finally { conn->Close(); }
            return equips;
        }
    }
    
}

