#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class RegistreUsuariForm : public PlayCampusLegacyForm
	{
	public:
		RegistreUsuariForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaRegistreInicial();
		}
	};
}
