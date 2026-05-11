#pragma once
#include "PlayCampusLegacyForm.h"

namespace CppCLRWinFormsProject {

	// Formulari principal conservador.
	// Hereta la implementació original per mantenir exactament la mateixa interfície,
	// navegació i lògica que funcionava abans de la tasca #162.
	public ref class Form1 : public PlayCampusLegacyForm
	{
	public:
		Form1(void) : PlayCampusLegacyForm()
		{
		}
	};
}
