#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace CoreValidators {

	inline bool ValidateCrearPartit(const std::string& eqLocal, const std::string& eqVis, const std::string& ubicacio) {
		if (eqLocal.empty() || eqVis.empty() || ubicacio.empty()) return false;
		if (eqLocal == eqVis) return false;
		return true;
	}

	inline bool ValidateUsuariAuth(const std::string& correu, const std::string& pass) {
		if (correu.empty() || pass.empty()) return false;
		if (correu.find('@') == std::string::npos || correu.find('.') == std::string::npos) return false;
		if (pass.length() < 8) return false;
		return true;
	}

	inline bool ValidateCrearEquip(const std::string& nomEquip, const std::string& esport) {
		if (nomEquip.empty()) return false;
		std::vector<std::string> esportsValids = { "Futbol", "Basquet", "Voleibol" };
		return std::find(esportsValids.begin(), esportsValids.end(), esport) != esportsValids.end();
	}

	inline bool ValidateCrearLliga(const std::string& nomLliga, const std::string& disciplina, const std::string& contrasenya) {
		if (nomLliga.empty() || contrasenya.length() < 6) return false;
		std::vector<std::string> disciplinesValides = { "Futbol", "Basquet", "Voleibol" };
		return std::find(disciplinesValides.begin(), disciplinesValides.end(), disciplina) != disciplinesValides.end();
	}

	inline bool ValidateCrearTemporada(int diasDuracio, const std::string& nomLliga) {
		if (nomLliga.empty()) return false;
		if (diasDuracio < 30 || diasDuracio > 365) return false;
		return true;
	}

	inline bool ValidateAfegirJugador(const std::string& correuJug, int dorsal, const std::string& posicio, const std::string& correuCapita) {
		if (correuJug.empty() || posicio.empty() || correuCapita.empty()) return false;
		if (correuJug.find('@') == std::string::npos) return false;
		if (dorsal < 1 || dorsal > 99) return false;
		return true;
	}

	inline bool ValidateTipusUsuari(const std::string& tipus) {
		std::vector<std::string> valids = { "Administrador", "Capita", "Jugador" };
		return std::find(valids.begin(), valids.end(), tipus) != valids.end();
	}

	inline bool ValidateIdentificadorUnic(const std::string& check_id, const std::vector<std::string>& existing_ids) {
		return std::find(existing_ids.begin(), existing_ids.end(), check_id) == existing_ids.end();
	}

	inline int ValidateCalculPunts(int victories, int empats, int derrotes) {
		return (victories * 3) + (empats * 1);
	}
}
