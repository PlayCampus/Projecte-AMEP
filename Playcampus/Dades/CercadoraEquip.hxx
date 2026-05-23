#pragma once
#include <string>
#include "PassarellaEquip.hxx"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;

namespace Playcampus {
	namespace Dades {
		public ref class CercadoraEquip {
		private:
			String^ connectionString;

		public:
			CercadoraEquip(String^ connStr);

			// Búsquedes que retornen PassarellaEquip
			PassarellaEquip^ LlegeixCapitaPerCorreu(String^ correu);
			PassarellaEquip^ LlegeixCapitaPerIdentificador(String^ identificador);
			PassarellaEquip^ LlegeixPerNomExacte(String^ nomEquip);

			// Búsquedes que retornen booleà
			bool ExisteixEquip(String^ idEquip);
			bool JugadorPertanyAEquip(String^ idJugador, String^ idEquip);
			bool CapitaTeEquip(String^ correu);
			bool EquipEstaEnLliga(String^ correu);
			bool ExisteixEquipPerNom(String^ nomEquip);

			// Consultes i utilitats
			List<String^>^ ObtenirIdsEquipsPerTemporada(String^ idTemporada);
			List<String^>^ ObtenirNomsEquipsPerLliga(String^ nomLliga);
			List<Dictionary<String^, String^>^>^ ObtenirPartitsDisponiblesEquip(String^ idEquip);
			List<Dictionary<String^, String^>^>^ ObtenirJugadorsEquipPerAssignacio(String^ idEquip);
			List<Dictionary<String^, String^>^>^ ObtenirPlantillaPerEquip(String^ idEquip);
			DataTable^ ObtenirLliguesEquip(String^ nomEquip);
			DataTable^ ObtenirTemporadesEquipLliga(String^ nomEquip, String^ idLliga);
			DataTable^ ObtenirEstadistiquesEquip(String^ nomEquip, String^ idLliga, String^ idTemporada);
			DataTable^ ObtenirEquipsDeLaLligaAdministrador(String^ correuAdmin);

		};
	}
}
