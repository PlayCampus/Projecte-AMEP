#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class ConsultarForm : public PlayCampusLegacyForm
	{
	public:
		ConsultarForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaConsultarInicial();
		}
	};
}
