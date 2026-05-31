#pragma once
#include <string>

using namespace System;
using namespace System::Data;

namespace Playcampus {
	namespace Domini {
		public ref class CtrlVeureEstadistiquesJugadors {
		private:
			String^ connectionString;

		public:
			CtrlVeureEstadistiquesJugadors();

			// PRE: idJugador identifica un jugador existent o pendent de comprovar.
			// POST: retorna les estadistiques generals del jugador indicat.
			DataTable^ ObtenirEstadistiquesJugador(String^ idJugador);

			// PRE: cert.
			// POST: retorna les estadistiques generals de tots els jugadors.
			DataTable^ ObtenirTotesEstadistiquesJugadors();

			// PRE: textCerca conte el text escrit al cercador.
			// POST: retorna les estadistiques dels jugadors que coincideixen amb el text.
			DataTable^ CercarEstadistiquesJugadors(String^ textCerca);

			// PRE: idPartit identifica un partit existent o pendent de comprovar.
			// POST: retorna les estadistiques individuals registrades per al partit indicat.
			DataTable^ ObtenirEstadistiquesPartit(String^ idPartit);

			// PRE: idPartit identifica un partit existent o pendent de comprovar.
			// POST: retorna els detalls del partit indicat.
			DataTable^ ObtenirDetallsPartit(String^ idPartit);
		};
	}
}