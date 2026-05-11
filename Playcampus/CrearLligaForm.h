#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class CrearLligaForm : public PlayCampusLegacyForm
	{
	public:
		CrearLligaForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaCrearLligaInicial();
		}
	};
}
