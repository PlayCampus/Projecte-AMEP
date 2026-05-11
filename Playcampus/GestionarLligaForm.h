#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class GestionarLligaForm : public PlayCampusLegacyForm
	{
	public:
		GestionarLligaForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaGestionarLligaInicial();
		}
	};
}
