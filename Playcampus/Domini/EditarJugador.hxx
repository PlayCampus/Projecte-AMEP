#pragma once
#include <string>

using namespace System;

namespace Playcampus {
	namespace Domini {
		public ref class EditarJugador {
		private:
			String^ connectionString;

		public:
			EditarJugador();

			// Edita el dorsal i la posició d'un jugador identificat per idJugador.
			// correuCapita: correu del capità que realitza l'acció (s'ha de validar com a capità).
			// idJugador: identificador de l'usuari/jugador a modificar.
			// nouDorsal: nou número de dorsal a assignar.
			// novaPosicio: nova posició del jugador.
			String^ Editar(String^ correuCapita, String^ idJugador, int nouDorsal, String^ novaPosicio);
		};
	}
}
