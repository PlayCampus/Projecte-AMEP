#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class ConvocatoriaForm : public PlayCampusLegacyForm
	{
	public:
		ConvocatoriaForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaConvocatoriaInicial();
		}
	};
}
