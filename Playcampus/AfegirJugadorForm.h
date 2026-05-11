#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class AfegirJugadorForm : public PlayCampusLegacyForm
	{
	public:
		AfegirJugadorForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaAfegirJugadorInicial();
		}
	};
}
