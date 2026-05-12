#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
	namespace Domini {
		public ref class CtrlEstadistiquesPartit {
		public:
			CtrlEstadistiquesPartit();

			// Mètodes de cerca en cascada cridant a les Cercadores
			DataTable^ ObtenirTotesLligues();
			DataTable^ ObtenirTemporadesLliga(String^ idLliga);
			DataTable^ ObtenirPartitsFinalitzats(String^ idTemporada);

			// Mètodes de dades del partit cridant a les Cercadores
			DataTable^ ObtenirDetallsPartit(String^ idPartit);
			DataTable^ ObtenirEstadistiquesPartit(String^ idPartit);
		};
	}
}