#include "pch.h"
#include "CtrlEstadistiquesPartit.hxx"
#include "../Dades/CercadoraLliga.hxx"
#include "../Dades/CercadoraTemporada.hxx"
#include "../Dades/CercadoraPartit.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "CtrlVeureEstadistiquesJugadors.hxx" 

using namespace System;
using namespace System::Data;

namespace Playcampus {
	namespace Domini {

		CtrlEstadistiquesPartit::CtrlEstadistiquesPartit() {}

		DataTable^ CtrlEstadistiquesPartit::ObtenirTotesLligues() {
			String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
			Playcampus::Dades::CercadoraLliga^ cercadora = gcnew Playcampus::Dades::CercadoraLliga(connStr);
			return cercadora->ObtenirTotesLligues();
		}

		DataTable^ CtrlEstadistiquesPartit::ObtenirTemporadesLliga(String^ idLliga) {
			String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
			Playcampus::Dades::CercadoraTemporada^ cercadora = gcnew Playcampus::Dades::CercadoraTemporada(connStr);
			return cercadora->ObtenirTemporadesLliga(idLliga);
		}

		DataTable^ CtrlEstadistiquesPartit::ObtenirPartitsFinalitzats(String^ idTemporada) {
			String^ connStr = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
			Playcampus::Dades::CercadoraPartit^ cercadora = gcnew Playcampus::Dades::CercadoraPartit(connStr);
			return cercadora->ObtenirPartitsFinalitzatsPerTemporada(idTemporada);
		}

		DataTable^ CtrlEstadistiquesPartit::ObtenirDetallsPartit(String^ idPartit) {
			Playcampus::Domini::CtrlVeureEstadistiquesJugadors^ cercadora = gcnew Playcampus::Domini::CtrlVeureEstadistiquesJugadors();
			return cercadora->ObtenirDetallsPartit(idPartit);
		}

		DataTable^ CtrlEstadistiquesPartit::ObtenirEstadistiquesPartit(String^ idPartit) {
			Playcampus::Domini::CtrlVeureEstadistiquesJugadors^ cercadora = gcnew Playcampus::Domini::CtrlVeureEstadistiquesJugadors();
			return cercadora->ObtenirEstadistiquesPartit(idPartit);
		}
	}
}
