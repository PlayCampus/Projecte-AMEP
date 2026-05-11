#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	public ref class AssignarJugadorPartitForm : public PlayCampusLegacyForm
	{
	public:
		AssignarJugadorPartitForm(void) : PlayCampusLegacyForm()
		{
			this->MostrarPantallaAssignarJugadorPartitInicial();
		}
	};
}
