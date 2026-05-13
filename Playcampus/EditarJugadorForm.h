#pragma once
#include "Form1.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// Formulario para editar los datos de un jugador
	/// </summary>
public ref class EditarJugadorForm : public System::Windows::Forms::Form
	{
	public:
		EditarJugadorForm(String^ idJugador, String^ nom, int dorsal, String^ posicio);

		// Propiedades para obtener los valores editados
		property String^ JugadorId { String^ get() { return jugadorId; } }
		property String^ JugadorNom { String^ get() { return jugadorNom; } }
		property int JugadorDorsal { int get() { return jugadorDorsal; } }
		property String^ JugadorPosicio { String^ get() { return jugadorPosicio; } }
		property String^ CorreuCapita { String^ get() { return correuCapita; } void set(String^ value) { correuCapita = value; } }

	private:
		System::ComponentModel::Container^ components;

		// Datos del jugador
		String^ jugadorId;
		String^ jugadorNom;
		int jugadorDorsal;
		String^ jugadorPosicio;
		String^ correuCapita;

		// Controles
		System::Windows::Forms::Label^ lblTitle;
		System::Windows::Forms::Label^ lblNom;
		System::Windows::Forms::TextBox^ txtNom;
		System::Windows::Forms::Label^ lblDorsal;
		System::Windows::Forms::TextBox^ txtDorsal;
		System::Windows::Forms::Label^ lblPosicio;
		System::Windows::Forms::TextBox^ txtPosicio;
		System::Windows::Forms::Button^ btnGuardar;
		System::Windows::Forms::Button^ btnCancelar;

		void InitializeComponent();
		void DesignForm();
		System::Void btnGuardar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCancelar_Click(System::Object^ sender, System::EventArgs^ e);

	protected:
		~EditarJugadorForm() {
			if (components) {
				delete components;
			}
		}
	};
}
