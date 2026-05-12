#pragma once
#include "Domini/CtrlIniciSessio.hxx"
#include "Domini/CtrlTancarSessio.hxx"
#include "Domini/CtrlRegistrarUsuari.hxx"
#include "Domini/CtrlCrearLliga.hxx"
#include "Domini/CtrlEnregistrarEquip.hxx"
#include "Domini/CtrlUnirEquipLliga.hxx"
#include "Domini/CtrlCrearPartit.hxx"
#include "Domini/CtrlEditarPartit.hxx"
#include "Domini/CtrlCrearTemporada.hxx"
#include "Domini/CtrlCrearJornada.hxx"
#include "Dades/ConnexioBD.hxx"
#include "Domini/CtrlEsborrarEquip.hxx"
#include "Domini/CtrlAfegirJugador.hxx"
#include "Domini/CtrlAssignarJugador.hxx"
#include "Domini/CtrlVeurePlantilla.hxx"
#include "Domini/CtrlEliminarJugador.hxx"
#include "Domini/CtrlConsultes.hxx"
#include "Domini/CtrlEsborrarPartit.hxx"
#include "Domini/CtrlVeureEstadistiquesLliga.hxx"
#include "Domini/CtlrConvocarJugadors.hxx"
#include "Domini/Administrador.hxx"
#include "Domini/CtrlRetirarTemporada.hxx"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);

	protected:
		~Form1();

	private:
		System::ComponentModel::Container^ components;

		private:
				System::Windows::Forms::Panel^ pnlInici;
		System::Windows::Forms::Button^ btnShowLogin;
		System::Windows::Forms::Button^ btnShowRegister;
		System::Windows::Forms::PictureBox^ picLogoInici;
		System::Windows::Forms::Panel^ pnlLogin;
		System::Windows::Forms::Label^ lblLoginUsuari;
		System::Windows::Forms::Label^ lblLoginPass;
		System::Windows::Forms::TextBox^ txtLoginCorreu;
		System::Windows::Forms::TextBox^ txtLoginPass;
		System::Windows::Forms::Button^ btnLoginAct;
		System::Windows::Forms::Button^ btnLoginBack;
		System::Windows::Forms::Label^ lblLoginTitle;
		System::Windows::Forms::PictureBox^ picLogoLogin;
		System::Windows::Forms::Panel^ pnlRegister;
		System::Windows::Forms::Label^ lblRegId;
		System::Windows::Forms::Label^ lblRegNom;
		System::Windows::Forms::Label^ lblRegCorreu;
		System::Windows::Forms::Label^ lblRegPass;
		System::Windows::Forms::Label^ lblRegTipus;
		System::Windows::Forms::Label^ lblRegTelefon;
		System::Windows::Forms::TextBox^ txtRegId;
		System::Windows::Forms::TextBox^ txtRegNom;
		System::Windows::Forms::TextBox^ txtRegCorreu;
		System::Windows::Forms::TextBox^ txtRegPass;
		System::Windows::Forms::ComboBox^ cmbRegTipus;
		System::Windows::Forms::TextBox^ txtRegTelefon;
		System::Windows::Forms::Button^ btnRegAct;
		System::Windows::Forms::Button^ btnRegBack;
		System::Windows::Forms::Label^ lblRegTitle;
		System::Windows::Forms::PictureBox^ picLogoRegister;
		System::Windows::Forms::Panel^ pnlMain;
		System::Windows::Forms::Label^ lblMainTitle;
		System::Windows::Forms::Button^ btnProgPartits;
		System::Windows::Forms::Button^ btnEstatLligues;
		System::Windows::Forms::Button^ btnEstadistiques;
		System::Windows::Forms::Button^ btnConsultar;
		System::Windows::Forms::Button^ btnEnregistrarEquip;
		System::Windows::Forms::Button^ btnUnirEquipLliga;
		System::Windows::Forms::Panel^ pnlEstadistiques;
		System::Windows::Forms::Label^ lblEstTitle;
		System::Windows::Forms::Button^ btnEstEquips;
		System::Windows::Forms::Button^ btnEstTornar;
		System::Windows::Forms::PictureBox^ picLogoEst;
		System::Windows::Forms::Button^ btnLogoutMainMenu;
		System::Windows::Forms::PictureBox^ picImatge;
		System::Windows::Forms::Label^ lblNoticies;
		System::Windows::Forms::ListBox^ lstNoticies;
		System::Windows::Forms::PictureBox^ picLogoMain;
		System::Windows::Forms::Panel^ pnlConsultar;
		System::Windows::Forms::Label^ lblConsultarTitle;
		System::Windows::Forms::Button^ btnTornarConsultar;
		System::Windows::Forms::Label^ lblNomLliga;
		System::Windows::Forms::TextBox^ txtNomLliga;
		System::Windows::Forms::Button^ btnComprovarLliga;
		System::Windows::Forms::Button^ btnCrearLligaMainMenu;
		System::Windows::Forms::Panel^ pnlCrearLliga;
		System::Windows::Forms::Label^ lblCLTitle;
		System::Windows::Forms::Label^ lblCLNom;
		System::Windows::Forms::TextBox^ txtCLNom;
		System::Windows::Forms::Label^ lblCLPass;
		System::Windows::Forms::TextBox^ txtCLPass;
		System::Windows::Forms::Label^ lblCLEsport;
		System::Windows::Forms::ComboBox^ cmbCLEsport;
		System::Windows::Forms::Button^ btnCLGuarda;
		System::Windows::Forms::Button^ btnCLTornar;
		System::Windows::Forms::Panel^ pnlCrearTemporada;
		System::Windows::Forms::Label^ lblCTTitle;
		System::Windows::Forms::Label^ lblCTNomLliga;
		System::Windows::Forms::TextBox^ txtCTNomLliga;
		System::Windows::Forms::Label^ lblCTDataInici;
		System::Windows::Forms::DateTimePicker^ dtpCTDataInici;
		System::Windows::Forms::Label^ lblCTDataFi;
		System::Windows::Forms::DateTimePicker^ dtpCTDataFi;
		System::Windows::Forms::Button^ btnCTConfirmar;
		System::Windows::Forms::Button^ btnCTCancellar;
		System::Windows::Forms::Panel^ pnlCrearJornada;
		System::Windows::Forms::Label^ lblCJTitle;
		System::Windows::Forms::Label^ lblCJNomLliga;
		System::Windows::Forms::TextBox^ txtCJNomLliga;
		System::Windows::Forms::Button^ btnCJBuscarTemporades;
		System::Windows::Forms::Label^ lblCJTemporada;
		System::Windows::Forms::ComboBox^ cmbCJTemporada;
		System::Windows::Forms::Label^ lblCJDataInici;
		System::Windows::Forms::DateTimePicker^ dtpCJDataInici;
		System::Windows::Forms::Label^ lblCJDataFi;
		System::Windows::Forms::DateTimePicker^ dtpCJDataFi;
		System::Windows::Forms::Label^ lblCJNumero;
		System::Windows::Forms::TextBox^ txtCJNumero;
		System::Windows::Forms::Button^ btnCJConfirmar;
		System::Windows::Forms::Button^ btnCJCancellar;
		System::Collections::Generic::List<String^>^ cjTemporadaIds;
		System::Windows::Forms::Panel^ pnlEnregistrarEquip;
		System::Windows::Forms::Label^ lblEETitle;
		System::Windows::Forms::Label^ lblEENom;
		System::Windows::Forms::TextBox^ txtEENom;
		System::Windows::Forms::Label^ lblEEData;
		System::Windows::Forms::DateTimePicker^ dtpEEData;
		System::Windows::Forms::Label^ lblEEEscollirEsport;
		System::Windows::Forms::ComboBox^ cmbEEEscollirEsport;
		System::Windows::Forms::Button^ btnEEEnregistrar;
		System::Windows::Forms::Button^ btnEETornar;
		System::Windows::Forms::Panel^ pnlGestionarEquip;
		System::Windows::Forms::Label^ lblGETitle;
		System::Windows::Forms::DataGridView^ dgvPlantilla;
		System::Windows::Forms::Button^ btnGEEsborrarEquip;
		System::Windows::Forms::Button^ btnGEAfegirJugador;
		System::Windows::Forms::Button^ btnGEEliminarJugador;
		System::Windows::Forms::Button^ btnGEAssignarJugador;
		System::Windows::Forms::Button^ btnGEEditarJugador;
		System::Windows::Forms::Button^ btnGETornar;
		System::Windows::Forms::Panel^ pnlAfegirJugador;
		System::Windows::Forms::Label^ lblAJTitle;
		System::Windows::Forms::Label^ lblAJCorreu;
		System::Windows::Forms::TextBox^ txtAJCorreu;
		System::Windows::Forms::Label^ lblAJDorsal;
		System::Windows::Forms::TextBox^ txtAJDorsal;
		System::Windows::Forms::Label^ lblAJPosicio;
		System::Windows::Forms::TextBox^ txtAJPosicio;
		System::Windows::Forms::Button^ btnAJConfirmar;
		System::Windows::Forms::Button^ btnAJCancellar;
		System::Windows::Forms::Panel^ pnlUnirEquipLliga;
		System::Windows::Forms::Label^ lblUELTitle;
		System::Windows::Forms::Label^ lblUELNom;
		System::Windows::Forms::TextBox^ txtUELNom;
		System::Windows::Forms::Button^ btnUELComprovar;
		System::Windows::Forms::Label^ lblUELPass;
		System::Windows::Forms::TextBox^ txtUELPass;
		System::Windows::Forms::Button^ btnUELUnir;
		System::Windows::Forms::Button^ btnUELTornar;
		String^ currentUsuariTipus;
		String^ currentUsuariCorreu;
		System::Windows::Forms::Panel^ pnlGestionarLliga;
		System::Windows::Forms::Label^ lblGLTitle;
		System::Windows::Forms::Button^ btnGLAfegirPartit;
		System::Windows::Forms::Button^ btnGLEditarPartit;
		System::Windows::Forms::Button^ btnGLMostrarEquips;
		System::Windows::Forms::Button^ btnGLEsborrarEquip;
		System::Windows::Forms::Button^ btnGLCrearJornada;
		System::Windows::Forms::Button^ btnGLCrearTemporada;
		System::Windows::Forms::Button^ btnGLRetirarTemporada;
		System::Windows::Forms::Button^ btnGLTornar;
		System::Windows::Forms::PictureBox^ picLogoGL;
		System::Windows::Forms::Panel^ pnlCrearPartit;
		System::Windows::Forms::Label^ lblCPTitle;
		System::Windows::Forms::Label^ lblCPNomLliga;
		System::Windows::Forms::TextBox^ txtCPNomLliga;
		System::Windows::Forms::Button^ btnCPValidarLliga;
		System::Windows::Forms::Label^ lblCPTemporada;
		System::Windows::Forms::ComboBox^ cmbCPTemporada;
		System::Collections::Generic::List<String^>^ cpTemporadesIds;
		// Para guardar la ID de la temporada
				System::Collections::Generic::List<String^>^ cpJornadesIds;
		// Para guardar la ID de la jornada
				System::Windows::Forms::Label^ lblCPJornada;
		System::Windows::Forms::ComboBox^ cmbCPJornada;
		System::Windows::Forms::Label^ lblCPData;
		System::Windows::Forms::DateTimePicker^ dtpCPData;
		System::Windows::Forms::Label^ lblCPUbicacio;
		System::Windows::Forms::TextBox^ txtCPUbicacio;
		System::Windows::Forms::Label^ lblCPEquipLocal;
		System::Windows::Forms::ComboBox^ cmbCPEquipLocal;
		System::Windows::Forms::Label^ lblCPEquipVisitant;
		System::Windows::Forms::ComboBox^ cmbCPEquipVisitant;
		System::Windows::Forms::Button^ btnCPConfirmar;
		System::Windows::Forms::Button^ btnCPCancellar;
		System::Windows::Forms::Button^ btnGLEsborrarPartit;
		System::Windows::Forms::Panel^ pnlEsborrarPartit;
		System::Windows::Forms::Label^ lblEPTitle;
		System::Windows::Forms::Button^ btnEPTornar;
		System::Windows::Forms::Label^ lblEPTemporada;
		System::Windows::Forms::ComboBox^ cmbEPTemporades;
		System::Collections::Generic::List<String^>^ epTemporadaIds;
		System::Windows::Forms::Label^ lblEPJornada;
		System::Windows::Forms::ComboBox^ cmbEPJornades;
		System::Collections::Generic::List<String^>^ epJornadaIds;
		System::Windows::Forms::Label^ lblEPPartit;
		System::Windows::Forms::ComboBox^ cmbEPPartits;
		System::Collections::Generic::List<String^>^ epPartitIds;
		System::Windows::Forms::Button^ btnEPEsborrarFinal;
		// Nou panell per la cerca i la taula
				System::Windows::Forms::Button^ btnEstLliga;
		System::Windows::Forms::Panel^ pnlEstadistiquesLligaDetail;
		System::Windows::Forms::Label^ lblEstLligaBuscar;
		System::Windows::Forms::TextBox^ txtEstLligaBuscar;
		System::Windows::Forms::Button^ btnEstLligaExecutarCerca;
		System::Windows::Forms::Label^ lblEstLligaTemporada;
		System::Windows::Forms::ComboBox^ cmbEstLligaTemporades;
		System::Windows::Forms::DataGridView^ dgvEstLligaClassificacio;
		System::Windows::Forms::Button^ btnEstLligaTornar;
		private: System::Windows::Forms::Panel^ pnlConvocatoria;
		private: System::Windows::Forms::Button^ btnGestionarConvocatoria;
		private: System::Windows::Forms::Button^ btnTornarConvocatoria;
		private: System::Windows::Forms::ComboBox^ cbPartitsConvocatoria;
		private: System::Windows::Forms::DataGridView^ dgvConvocatoria;
		private: System::Collections::Generic::List<System::String^>^ convocatoriaPartitIds;
		// Variables pel cartell del jugador
			private: System::Windows::Forms::Panel^ pnlAvisJugador;
		private: System::String^ idPartitPendentConfirmar;
		String^ currentIdLligaEstadistiques;
		// Per guardar la ID de la lliga cercada
		
			// NOU: Components per al panell d'edició de partits
			private: System::Windows::Forms::Panel^ pnlEditarPartit;
		private: System::Windows::Forms::Label^ lblEditarPartitTitle;
		private: System::Windows::Forms::ComboBox^ cmbPartitsAEditar;
		private: System::Windows::Forms::Label^ lblPartitsAEditar;
		private: System::Windows::Forms::DataGridView^ dgvEstadistiquesJugadors;
		private: System::Windows::Forms::Button^ btnGuardarEstadistiques;
		private: System::Windows::Forms::Button^ btnTornarEditarPartit;
		private: System::Windows::Forms::Label^ lblResultatLocal;
		private: System::Windows::Forms::TextBox^ txtResultatLocal;
		private: System::Windows::Forms::Label^ lblResultatVisitant;
		private: System::Windows::Forms::TextBox^ txtResultatVisitant;
		private: System::Windows::Forms::Label^ lblEstatPartit;
		private: System::Windows::Forms::ComboBox^ cmbEstatPartit;
		private: System::Windows::Forms::Label^ lblDataPartit;
		private: System::Windows::Forms::DateTimePicker^ dtpDataPartit;
		private: System::Collections::Generic::Dictionary<String^, String^>^ partitPerId;

	public:
		System::Void MostrarPantallaEditarPartit();
		void MostrarPantallaIniciInicial();
		void MostrarPantallaLoginInicial();
		void MostrarPantallaRegistreInicial();
		void MostrarPantallaMenuPrincipalInicial();
		void MostrarPantallaConsultarInicial();
		void MostrarPantallaCrearLligaInicial();
		void MostrarPantallaGestionarLligaInicial();
		void MostrarPantallaCrearPartitInicial();
		void MostrarPantallaEditarPartitInicial();
		void MostrarPantallaCrearTemporadaInicial();
		void MostrarPantallaCrearJornadaInicial();
		void MostrarPantallaEsborrarPartitInicial();
		void MostrarPantallaEnregistrarEquipInicial();
		void MostrarPantallaGestionarEquipInicial();
		void MostrarPantallaAfegirJugadorInicial();
		void MostrarPantallaAssignarJugadorPartitInicial();
		void MostrarPantallaUnirEquipLligaInicial();
		void MostrarPantallaEstadistiquesInicial();
		void MostrarPantallaEstadistiquesLligaInicial();
		void MostrarPantallaConvocatoriaInicial();

	private:
		void InitializeComponent(void);
		System::Void Form1_Resize(System::Object^ sender, System::EventArgs^ e);
		System::Void btnUnirEquipLligaAct_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnUELTornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnUELComprovar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnUELUnir_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnShowLogin_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnShowRegister_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnShowRegisterFromLogin_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmbRegTipus_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnLoginAct_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmbPartitsAEditar_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGuardarEstadistiques_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnTornarEditarPartit_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmbEstatPartit_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void btnRegAct_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnConsultar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnTornarConsultar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnComprovarLliga_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCrearLligaMainMenu_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLTornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLCrearJornada_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCJCancellar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCJBuscarTemporades_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCJConfirmar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLCrearTemporada_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCTCancellar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCTConfirmar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLAfegirPartit_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLEditarPartit_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCPValidarLliga_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmbCPTemporada_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCPCancellar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCPConfirmar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void MostrarTaulaConsulta(System::String^ titol, System::Data::DataTable^ dades);
		System::Void MostrarConsultaGeneral(System::String^ titol, System::Data::DataTable^ dades);
		System::Void btnProgPartits_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEstatLligues_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEstadistiquesMenu_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEstTornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEstadistiques_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLMostrarEquips_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGL_EnDesenvolupament_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCLTornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnCLGuarda_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEnregistrarEquip_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGETornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGEEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLRetirarTemporada_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGEAssignarJugador_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGEAfegirJugador_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGEEliminarJugador_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGEEditarJugador_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnAJConfirmar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnAJCancellar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEETornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEEEnregistrar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGLEsborrarPartit_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEPTornar_Click(System::Object^ sender, System::EventArgs^ e);
		void CarregarTemporadesEsborrar();
		System::Void btnEstLliga_Click(System::Object^ sender, System::EventArgs^ e);
		void CarregarDadesLligaDirecte(Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl, String^ idLliga);
		System::Void btnEstLligaExecutarCerca_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmbEPTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEstLligaTornar_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void cmbEPJornades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void btnEPEsborrarFinal_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnGestionarConvocatoria_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnTornarConvocatoria_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void CarregarPartitsConvocatoria();
		System::Void cbPartitsConvocatoria_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void dgvConvocatoria_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		System::Void MostrarAvisJugador(String^ missatge);
		System::Void btnConfirmarSi_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void btnConfirmarNo_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void ProcessarConfirmacio(bool assisteix);
		void MostrarPanelInicialTask162(System::Windows::Forms::Panel^ panel);
		void OcultarPantallesPrincipalsTask162();
	};
}
