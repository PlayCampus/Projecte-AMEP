#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class CrearPartitForm : public PlayCampusLegacyForm
	{
	public:
		CrearPartitForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaCrearPartitInicial();
		}
	};
}
