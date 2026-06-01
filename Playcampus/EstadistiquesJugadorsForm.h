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
		System::Windows::Forms::Label^ lblCerca;
		System::Windows::Forms::TextBox^ txtCercaJugador;
		System::Windows::Forms::Button^ btnCercar;
		System::Windows::Forms::Button^ btnNetejar;
		System::Windows::Forms::Label^ lblResultatCerca;
		System::Windows::Forms::DataGridView^ dgvEstadistiques;
		System::Windows::Forms::Button^ btnTornar;

		// PRE: cert.
		// POST: inicialitza els controls del formulari.
		void InitializeComponent();
		// PRE: els controls estan inicialitzats.
		// POST: aplica el disseny addicional del formulari.
		void DesignForm();
		// PRE: cert.
		// POST: carrega totes les estadistiques dels jugadors.
		void CarregarEstadistiques();
		// PRE: textCerca conte el filtre escrit per l'usuari.
		// POST: carrega a la taula les estadistiques filtrades.
		void CarregarEstadistiquesFiltrades(System::String^ textCerca);
		// PRE: la taula pot tenir dades carregades.
		// POST: ajusta les capcaleres i l'estil de les columnes.
		void ConfigurarColumnes();
		System::Void btnCercar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnNetejar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void txtCercaJugador_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		System::Void btnTornar_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
