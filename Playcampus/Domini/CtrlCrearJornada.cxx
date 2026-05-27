#include "pch.h"
#include "CtrlCrearJornada.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/CercadoraTemporada.hxx"
#include "../Dades/CercadoraJornada.hxx"
#include "../Dades/CercadoraLliga.hxx"

using namespace Playcampus::Domini;
using namespace System;

CtrlCrearJornada::CtrlCrearJornada() {}

String^ CtrlCrearJornada::ObtenirNomLligaAdministrador(String^ correuAdmin) {
    String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
    Playcampus::Dades::CercadoraLliga^ cercadora = gcnew Playcampus::Dades::CercadoraLliga(connStr);
    return cercadora->ObtenirNomLligaAdministrador(correuAdmin);
}


void CtrlCrearJornada::CrearJornada(String^ idTemporada,int numero, DateTime dataInici, DateTime dataFi, String^ estat) {
            // RIT14 (j : Jornada): el número d’una jornada ha de ser més gran que 0.
            if (numero <= 0) {
                throw gcnew ArgumentException("El número de jornada ha de ser més gran que 0.");
            }

            // RIT15 (j : Jornada): la dataInici d’una jornada ha de ser anterior a la dataFi.
            if (dataInici >= dataFi) {
                throw gcnew ArgumentException("La data d'inici de la jornada ha de ser anterior a la data final.");
            }

            // 1. Obtener string de conexión
            String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();

            // RIT16 (j : Jornada, t : Temporada): les dates d’una jornada han d’estar dins de l’interval de dates de la temporada a la qual pertany.
            Playcampus::Dades::CercadoraTemporada^ cercadoraTemp = gcnew Playcampus::Dades::CercadoraTemporada(connStr);
            Dictionary<String^, String^>^ temporadaInfo = cercadoraTemp->ObtenirTemporadaPerId(idTemporada);
            if (temporadaInfo != nullptr) {
                DateTime tempInici = Convert::ToDateTime(temporadaInfo["dataInici"]);
                DateTime tempFi = Convert::ToDateTime(temporadaInfo["dataFi"]);
                if (dataInici < tempInici || dataFi > tempFi) {
                    throw gcnew ArgumentException("Les dates de la jornada han d'estar dins de l'interval de la temporada (" + 
                        tempInici.ToString("dd/MM/yyyy") + " - " + tempFi.ToString("dd/MM/yyyy") + ").");
                }
            }

            Playcampus::Dades::CercadoraJornada^ cercadoraJornada = gcnew Playcampus::Dades::CercadoraJornada(connStr);
            List<Dictionary<String^, String^>^>^ jornades = cercadoraJornada->ObtenirDictJornadesPerTemporada(idTemporada);
            
            for each(Dictionary<String^, String^>^ j in jornades) {
                // RIT17 (j1, j2 : Jornada, t : Temporada): dins d’una mateixa temporada no poden existir dues jornades amb el mateix número.
                if (Convert::ToInt32(j["numero"]) == numero) {
                    throw gcnew ArgumentException("Ja existeix una jornada amb aquest número en la temporada.");
                }
                
                // RIT18 (j1, j2 : Jornada, t : Temporada): dues jornades d’una mateixa temporada no es poden solapar en dates.
                DateTime jInici = Convert::ToDateTime(j["dataInici"]);
                DateTime jFi = Convert::ToDateTime(j["dataFi"]);
                
                if (dataInici < jFi && dataFi > jInici) {
                    throw gcnew ArgumentException("Les dates de la jornada es solapen amb una altra jornada existent.");
                }
            }

            // 2. Generar el ID de la Jornada
            String^ idJornada = "J-" + Guid::NewGuid().ToString()->Substring(0, 8);

            // 3. Crear la pasarela enviant tots els atributs segons el model correcte
            Playcampus::Dades::PassarellaJornada^ passJornada = gcnew Playcampus::Dades::PassarellaJornada(
                connStr,
                idJornada,
                idTemporada,
                numero,
                dataInici,
                dataFi,
                estat
            );

            // 4. Insertar en la BD utilitzant el estat de la pasarela
            passJornada->Insereix();
        }

        List<Dictionary<String^, String^>^>^ CtrlCrearJornada::ObtenirTemporadesLliga(String^ nomLliga) {
    // 1. Obtener la cadena de conexión
    String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();

    // 2. Instanciar pasarela temporada con la cadena de conexión usando su nuevo constructor
    Playcampus::Dades::PassarellaTemporada^ passTemporada = gcnew Playcampus::Dades::PassarellaTemporada(connStr);

    // 3. Llamar a la pasarela y devolver el resultado
    return passTemporada->ObtenirDictTemporadesPerLliga(nomLliga);
}
