#include "pch.h"
#include "CtrlCrearJornada.hxx"
#include "../Dades/ConnexioBD.hxx"

using namespace Playcampus::Domini;
using namespace System;

CtrlCrearJornada::CtrlCrearJornada() {}

bool CtrlCrearJornada::ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin) {
    String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
    Playcampus::Dades::PassarellaLliga^ passLliga = gcnew Playcampus::Dades::PassarellaLliga(connStr);

    return passLliga->EsAdministradorLliga(nomLliga, correuAdmin);
}



void CtrlCrearJornada::CrearJornada(String^ idTemporada,int numero, DateTime dataInici, DateTime dataFi, String^ estat) {
    // 1. Obtener string de conexión
    String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();

    // 2. Generar el ID de la Jornada
    String^ idJornada = "J-" + Guid::NewGuid().ToString()->Substring(0, 8);

    // 3. Crear la pasarela enviando todos los atributos según el modelo correcto
    Playcampus::Dades::PassarellaJornada^ passJornada = gcnew Playcampus::Dades::PassarellaJornada(
        connStr,
        idJornada,
        idTemporada,
        numero,
        dataInici,
        dataFi,
        estat
    );

    // 4. Insertar en la BD utilizando el estado de la pasarela
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
