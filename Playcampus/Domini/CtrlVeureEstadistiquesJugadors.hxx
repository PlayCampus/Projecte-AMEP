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

			// Obtiene las estadísticas generales almacenadas en la tabla Jugador para un jugador
			DataTable^ ObtenirEstadistiquesJugador(String^ idJugador);

			// Obtiene las estadísticas individuales registradas para un partido concreto
			DataTable^ ObtenirEstadistiquesPartit(String^ idPartit);


			DataTable^ ObtenirDetallsPartit(String^ idPartit);
		};
	}
}