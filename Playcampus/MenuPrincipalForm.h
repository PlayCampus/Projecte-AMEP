#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class MenuPrincipalForm : public PlayCampusLegacyForm
	{
	public:
		MenuPrincipalForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaMenuPrincipalInicial();
		}
	};
}
