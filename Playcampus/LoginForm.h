#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class LoginForm : public PlayCampusLegacyForm
	{
	public:
		LoginForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaLoginInicial();
		}
	};
}
