#pragma once
#include "Form1.h"
#include "Domini/CtrlVeureEstadistiquesJugadors.hxx"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Formulario para visualizar las estadísticas de todos los jugadores
	/// </summary>
	public ref class EstadistiquesJugadorsForm : public System::Windows::Forms::Form
	{
	public:
		EstadistiquesJugadorsForm();

	protected:
		~EstadistiquesJugadorsForm();

	private:
		System::ComponentModel::Container^ components;

		// Controles
		System::Windows::Forms::Label^ lblTitle;
		System::Windows::Forms::DataGridView^ dgvEstadistiques;
		System::Windows::Forms::Button^ btnTornar;

		void InitializeComponent();
		void DesignForm();
		void CarregarEstadistiques();
		System::Void btnTornar_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
