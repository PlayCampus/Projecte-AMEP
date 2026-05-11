#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class EditarPartitForm : public PlayCampusLegacyForm
	{
	public:
		EditarPartitForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaEditarPartitInicial();
		}
	};
}
