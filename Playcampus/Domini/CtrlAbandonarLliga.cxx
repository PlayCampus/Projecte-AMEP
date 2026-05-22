#include "pch.h"
#include "CtrlAbandonarLliga.hxx"
#include "../Dades/ConnexioBD.hxx"
#include "../Dades/PassarellaEquip.hxx"
#include <stdexcept>

using namespace System;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
	namespace Domini {

		CtrlAbandonarLliga::CtrlAbandonarLliga() {
			connectionString = Playcampus::Dades::ConnexioBD::ObtenirConnectionString();
		}

		String^ CtrlAbandonarLliga::AbandonarLliga(String^ correuCapita) {
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			String^ missatgeExit = "";
			try {
				conn->Open();

				// 1. Obtenir l'idEquip associat al Capita a traves del correu
				String^ queryCap = "SELECT C.idEquip FROM Capita C JOIN Usuari U ON C.identificador = U.identificador WHERE U.correu_electronic = @correu";
				MySqlCommand^ cmdCap = gcnew MySqlCommand(queryCap, conn);
				cmdCap->Parameters->AddWithValue("@correu", correuCapita);
				Object^ idEquipObj = cmdCap->ExecuteScalar();

				if (idEquipObj == nullptr || idEquipObj == DBNull::Value || String::IsNullOrWhiteSpace(idEquipObj->ToString())) {
					throw gcnew Exception("Aquest capita no te un equip actiu.");
				}
				String^ idEquipRecuperat = idEquipObj->ToString()->Trim();

				// 2. Obtenir l'equip actual
				Playcampus::Dades::PassarellaEquip^ equipDB = Playcampus::Dades::PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
				if (equipDB == nullptr) {
					throw gcnew Exception("Equip no trobat a la base de dades. (" + idEquipRecuperat + ")");
				}

				String^ nomEquip = equipDB->GetNom();

				// 3. Desvinacular l'equip de la temporada (establecer idTemporada a NULL)
				equipDB->SetIdTemporada(nullptr);

				// 4. Reiniciar totes les estadistiques
				equipDB->SetPartitsJugats(0);
				equipDB->SetVictories(0);
				equipDB->SetDerrotes(0);
				equipDB->SetEmpats(0);
				equipDB->SetPunts(0);
				equipDB->SetGolsAFavor(0);
				equipDB->SetGolsEnContra(0);
				equipDB->SetDiferenciaGols(0);
				equipDB->SetPosicioClassificacio(0);

				// 5. Guardar els canvis
				equipDB->Modifica();

				// 6. Comprovar que la modificacio s'ha guardat realment a la BD
				Playcampus::Dades::PassarellaEquip^ equipComprovat = Playcampus::Dades::PassarellaEquip::Llegeix(connectionString, idEquipRecuperat);
				if (equipComprovat == nullptr || equipComprovat->GetIdTemporada() != nullptr) {
					throw gcnew Exception("La base de dades no ha confirmat l'abandó de la lliga.");
				}

				if (equipComprovat->GetPunts() != 0 || equipComprovat->GetVictories() != 0) {
					throw gcnew Exception("La base de dades no ha confirmat la reinicialitzacio de les estadistiques.");
				}

				missatgeExit = "L'equip " + nomEquip + " ha abandonat la lliga. Les estadistiques han sigut reiniciades.";
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
					delete conn;
				}
			}
			return missatgeExit;
		}
	}
}
