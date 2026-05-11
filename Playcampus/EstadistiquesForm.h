#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class EstadistiquesForm : public PlayCampusLegacyForm
	{
	public:
		EstadistiquesForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaEstadistiquesInicial();
		}
	};
}
