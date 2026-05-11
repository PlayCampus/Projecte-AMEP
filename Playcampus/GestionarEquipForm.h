#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class GestionarEquipForm : public PlayCampusLegacyForm
	{
	public:
		GestionarEquipForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaGestionarEquipInicial();
		}
	};
}
