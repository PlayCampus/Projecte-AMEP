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
	public ref class PlayCampusLegacyForm : public System::Windows::Forms::Form
	{
	public:
		PlayCampusLegacyForm(void)
		{
			InitializeComponent(); // IMPORTANT: NO ESBORRAR

			// 1. Creació d'objectes
			this->pnlConvocatoria = gcnew System::Windows::Forms::Panel();
			this->btnGestionarConvocatoria = gcnew System::Windows::Forms::Button();
			this->btnTornarConvocatoria = gcnew System::Windows::Forms::Button();
			this->cbPartitsConvocatoria = gcnew System::Windows::Forms::ComboBox();
			this->dgvConvocatoria = gcnew System::Windows::Forms::DataGridView();
			this->convocatoriaPartitIds = gcnew System::Collections::Generic::List<System::String^>();

			// 2. Propietats i Events
			this->btnGestionarConvocatoria->Text = L"Gestionar Convocatòries";
			this->btnGestionarConvocatoria->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGestionarConvocatoria_Click);

			this->btnTornarConvocatoria->Text = L"Tornar al Menú";
			this->btnTornarConvocatoria->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnTornarConvocatoria_Click);

			this->cbPartitsConvocatoria->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbPartitsConvocatoria->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cbPartitsConvocatoria_SelectedIndexChanged);

			this->dgvConvocatoria->AllowUserToAddRows = false;
			this->dgvConvocatoria->ReadOnly = true;
			this->dgvConvocatoria->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvConvocatoria->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &PlayCampusLegacyForm::dgvConvocatoria_CellClick);

			// 3. Jerarquia (Afegir-los a la pantalla)
			this->pnlMain->Controls->Add(this->btnGestionarConvocatoria);
			this->Controls->Add(this->pnlConvocatoria);
			this->pnlConvocatoria->Controls->Add(this->btnTornarConvocatoria);
			this->pnlConvocatoria->Controls->Add(this->cbPartitsConvocatoria);
			this->pnlConvocatoria->Controls->Add(this->dgvConvocatoria);

			// 4. Estat Inicial
			this->pnlConvocatoria->Visible = false;
			this->btnGestionarConvocatoria->Visible = false;

			Form1_Resize(nullptr, nullptr);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlayCampusLegacyForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
		System::Collections::Generic::List<String^>^ cpTemporadesIds; // Para guardar la ID de la temporada
		System::Collections::Generic::List<String^>^ cpJornadesIds;   // Para guardar la ID de la jornada
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

		String^ currentIdLligaEstadistiques; // Per guardar la ID de la lliga cercada

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


		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(600, 500);
			this->Text = L"Playcampus";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Resize += gcnew System::EventHandler(this, &PlayCampusLegacyForm::Form1_Resize);

			// pnlInici
			this->pnlInici = gcnew System::Windows::Forms::Panel();
			this->btnShowLogin = gcnew System::Windows::Forms::Button();
			this->btnShowRegister = gcnew System::Windows::Forms::Button();
			this->picLogoInici = gcnew System::Windows::Forms::PictureBox();
			this->pnlInici->Controls->Add(this->btnShowLogin);
			this->pnlInici->Controls->Add(this->btnShowRegister);
			this->pnlInici->Controls->Add(this->picLogoInici);
			this->pnlInici->Dock = System::Windows::Forms::DockStyle::Fill;

			this->picLogoInici->ImageLocation = L"imatges\\logo.png";
			this->picLogoInici->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoInici->Size = System::Drawing::Size(150, 150);

			this->btnShowLogin->Text = L"Iniciar Sessió";
			this->btnShowLogin->Location = System::Drawing::Point(100, 100);
			this->btnShowLogin->Size = System::Drawing::Size(200, 40);
			this->btnShowLogin->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnShowLogin_Click);

			this->btnShowRegister->Text = L"Registrar-se";
			this->btnShowRegister->Location = System::Drawing::Point(100, 160);
			this->btnShowRegister->Size = System::Drawing::Size(200, 40);
			this->btnShowRegister->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnShowRegister_Click);

			// pnlLogin
			this->pnlLogin = gcnew System::Windows::Forms::Panel();
			this->lblLoginUsuari = gcnew System::Windows::Forms::Label();
			this->lblLoginPass = gcnew System::Windows::Forms::Label();
			this->txtLoginCorreu = gcnew System::Windows::Forms::TextBox();
			this->txtLoginPass = gcnew System::Windows::Forms::TextBox();
			this->btnLoginAct = gcnew System::Windows::Forms::Button();
			this->btnLoginBack = gcnew System::Windows::Forms::Button();
			this->lblLoginTitle = gcnew System::Windows::Forms::Label();
			this->picLogoLogin = gcnew System::Windows::Forms::PictureBox();

			this->pnlLogin->Controls->Add(this->lblLoginUsuari);
			this->pnlLogin->Controls->Add(this->lblLoginPass);
			this->pnlLogin->Controls->Add(this->txtLoginCorreu);
			this->pnlLogin->Controls->Add(this->txtLoginPass);
			this->pnlLogin->Controls->Add(this->btnLoginAct);
			this->pnlLogin->Controls->Add(this->btnLoginBack);
			this->pnlLogin->Controls->Add(this->lblLoginTitle);
			this->pnlLogin->Controls->Add(this->picLogoLogin);
			this->pnlLogin->Dock = System::Windows::Forms::DockStyle::Fill;

			this->picLogoLogin->ImageLocation = L"imatges\\logo.png";
			this->picLogoLogin->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoLogin->Size = System::Drawing::Size(150, 150);

			this->lblLoginTitle->Text = L"Iniciar Sessió";
			this->lblLoginTitle->Location = System::Drawing::Point(150, 20);

			this->lblLoginUsuari->Text = L"Correu";
			this->lblLoginUsuari->Location = System::Drawing::Point(50, 50);
			this->lblLoginUsuari->Size = System::Drawing::Size(100, 20);

			this->txtLoginCorreu->Text = L"";
			this->txtLoginCorreu->Location = System::Drawing::Point(150, 50);
			this->txtLoginCorreu->Size = System::Drawing::Size(150, 20);

			this->lblLoginPass->Text = L"Contrasenya";
			this->lblLoginPass->Location = System::Drawing::Point(50, 90);
			this->lblLoginPass->Size = System::Drawing::Size(100, 20);

			this->txtLoginPass->Text = L"";
			this->txtLoginPass->UseSystemPasswordChar = true;
			this->txtLoginPass->Location = System::Drawing::Point(150, 90);
			this->txtLoginPass->Size = System::Drawing::Size(150, 20);

			this->btnLoginAct->Text = L"Entrar";
			this->btnLoginAct->Location = System::Drawing::Point(50, 130);
			this->btnLoginAct->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnLoginAct_Click);

			this->btnLoginBack->Text = L"Registrar-se";
			this->btnLoginBack->Location = System::Drawing::Point(150, 130);
			this->btnLoginBack->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnShowRegisterFromLogin_Click);

			// pnlRegister
			this->pnlRegister = gcnew System::Windows::Forms::Panel();
			this->lblRegId = gcnew System::Windows::Forms::Label();
			this->lblRegNom = gcnew System::Windows::Forms::Label();
			this->lblRegCorreu = gcnew System::Windows::Forms::Label();
			this->lblRegPass = gcnew System::Windows::Forms::Label();
			this->lblRegTipus = gcnew System::Windows::Forms::Label();
			this->lblRegTelefon = gcnew System::Windows::Forms::Label();
			this->txtRegId = gcnew System::Windows::Forms::TextBox();
			this->txtRegNom = gcnew System::Windows::Forms::TextBox();
			this->txtRegCorreu = gcnew System::Windows::Forms::TextBox();
			this->txtRegPass = gcnew System::Windows::Forms::TextBox();
			this->cmbRegTipus = gcnew System::Windows::Forms::ComboBox();
			this->txtRegTelefon = gcnew System::Windows::Forms::TextBox();
			this->btnRegAct = gcnew System::Windows::Forms::Button();
			this->btnRegBack = gcnew System::Windows::Forms::Button();
			this->lblRegTitle = gcnew System::Windows::Forms::Label();
			this->picLogoRegister = gcnew System::Windows::Forms::PictureBox();

			this->pnlRegister->Controls->Add(this->lblRegNom);
			this->pnlRegister->Controls->Add(this->lblRegCorreu);
			this->pnlRegister->Controls->Add(this->lblRegPass);
			this->pnlRegister->Controls->Add(this->lblRegTipus);
			this->pnlRegister->Controls->Add(this->lblRegTelefon);
			this->pnlRegister->Controls->Add(this->txtRegNom);
			this->pnlRegister->Controls->Add(this->txtRegCorreu);
			this->pnlRegister->Controls->Add(this->txtRegPass);
			this->pnlRegister->Controls->Add(this->cmbRegTipus);
			this->pnlRegister->Controls->Add(this->txtRegTelefon);
			this->pnlRegister->Controls->Add(this->btnRegAct);
			this->pnlRegister->Controls->Add(this->btnRegBack);
			this->pnlRegister->Controls->Add(this->lblRegTitle);
			this->pnlRegister->Controls->Add(this->picLogoRegister);
			this->pnlRegister->Dock = System::Windows::Forms::DockStyle::Fill;

			this->picLogoRegister->ImageLocation = L"imatges\\logo.png";
			this->picLogoRegister->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoRegister->Size = System::Drawing::Size(150, 150);

			this->lblRegTitle->Text = L"Registrar-se";
			this->lblRegTitle->Location = System::Drawing::Point(150, 10);

			this->lblRegNom->Text = L"Nom";
			this->lblRegNom->Location = System::Drawing::Point(50, 70);
			this->lblRegNom->Size = System::Drawing::Size(100, 20);

			this->txtRegNom->Text = L"";
			this->txtRegNom->Location = System::Drawing::Point(150, 70);
			this->txtRegNom->Size = System::Drawing::Size(150, 20);

			this->lblRegCorreu->Text = L"Correu";
			this->lblRegCorreu->Location = System::Drawing::Point(50, 100);
			this->lblRegCorreu->Size = System::Drawing::Size(100, 20);

			this->txtRegCorreu->Text = L"";
			this->txtRegCorreu->Location = System::Drawing::Point(150, 100);
			this->txtRegCorreu->Size = System::Drawing::Size(150, 20);

			this->lblRegPass->Text = L"Contrasenya";
			this->lblRegPass->Location = System::Drawing::Point(50, 130);
			this->lblRegPass->Size = System::Drawing::Size(100, 20);

			this->txtRegPass->Text = L"";
			this->txtRegPass->UseSystemPasswordChar = true;
			this->txtRegPass->Location = System::Drawing::Point(150, 130);
			this->txtRegPass->Size = System::Drawing::Size(150, 20);

			this->lblRegTipus->Text = L"Tipus";
			this->lblRegTipus->Location = System::Drawing::Point(50, 160);
			this->lblRegTipus->Size = System::Drawing::Size(100, 20);

			this->cmbRegTipus->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Estudiant", L"Capita", L"Administrador" });
			this->cmbRegTipus->SelectedIndex = 0;
			this->cmbRegTipus->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbRegTipus->Location = System::Drawing::Point(150, 160);
			this->cmbRegTipus->Size = System::Drawing::Size(150, 20);
			this->cmbRegTipus->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cmbRegTipus_SelectedIndexChanged);

			this->lblRegTelefon->Text = L"Telèfon";
			this->lblRegTelefon->Location = System::Drawing::Point(50, 190);
			this->lblRegTelefon->Size = System::Drawing::Size(100, 20);
			this->lblRegTelefon->Visible = false;

			this->txtRegTelefon->Text = L"";
			this->txtRegTelefon->Location = System::Drawing::Point(150, 190);
			this->txtRegTelefon->Size = System::Drawing::Size(150, 20);
			this->txtRegTelefon->Visible = false;

			this->btnRegAct->Text = L"Registrar";
			this->btnRegAct->Location = System::Drawing::Point(50, 230);
			this->btnRegAct->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnRegAct_Click);

			this->btnRegBack->Text = L"Tornar";
			this->btnRegBack->Location = System::Drawing::Point(150, 230);
			this->btnRegBack->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnBack_Click);

			// pnlMain
			this->pnlMain = gcnew System::Windows::Forms::Panel();
			this->lblMainTitle = gcnew System::Windows::Forms::Label();
			this->btnProgPartits = gcnew System::Windows::Forms::Button();
			this->btnEstatLligues = gcnew System::Windows::Forms::Button();
			this->btnEstadistiques = gcnew System::Windows::Forms::Button();
			this->btnConsultar = gcnew System::Windows::Forms::Button();
			this->picImatge = gcnew System::Windows::Forms::PictureBox(); 
			this->lblNoticies = gcnew System::Windows::Forms::Label();
			this->lstNoticies = gcnew System::Windows::Forms::ListBox();
			this->btnLogoutMainMenu = gcnew System::Windows::Forms::Button();
			this->picLogoMain = gcnew System::Windows::Forms::PictureBox();

			this->pnlMain->Controls->Add(this->lblMainTitle);
			this->pnlMain->Controls->Add(this->btnProgPartits);
			this->pnlMain->Controls->Add(this->btnEstatLligues);
			this->pnlMain->Controls->Add(this->btnEstadistiques);
			this->pnlMain->Controls->Add(this->btnConsultar); 
			this->pnlMain->Controls->Add(this->picImatge);
			this->pnlMain->Controls->Add(this->lblNoticies);
			this->pnlMain->Controls->Add(this->lstNoticies);
			this->pnlMain->Controls->Add(this->btnLogoutMainMenu);
			this->pnlMain->Controls->Add(this->picLogoMain);
			this->pnlMain->Dock = System::Windows::Forms::DockStyle::Fill;

			this->picLogoMain->ImageLocation = L"imatges\\logo.png";
			this->picLogoMain->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoMain->Size = System::Drawing::Size(150, 100);
			this->picLogoMain->Location = System::Drawing::Point(470, 50);

			this->lblMainTitle->Text = L"PlayCampus";
			this->lblMainTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblMainTitle->Location = System::Drawing::Point(230, 20);
			this->lblMainTitle->AutoSize = true;

			this->btnProgPartits->Text = L"Programació de partits";
			this->btnProgPartits->Location = System::Drawing::Point(20, 60);
		 this->btnProgPartits->Size = System::Drawing::Size(130, 40);
			this->btnProgPartits->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnProgPartits_Click);

			this->btnEstatLligues->Text = L"Estat de les Lligues";
			this->btnEstatLligues->Location = System::Drawing::Point(160, 60);
			this->btnEstatLligues->Size = System::Drawing::Size(130, 40);
			this->btnEstatLligues->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstatLligues_Click);

			this->btnEstadistiques->Text = L"Estadístiques";
			this->btnEstadistiques->Location = System::Drawing::Point(300, 60);
			this->btnEstadistiques->Size = System::Drawing::Size(130, 40);
			this->btnEstadistiques->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstadistiquesMenu_Click);

			this->btnConsultar->Text = L"Consultar";
			this->btnConsultar->Location = System::Drawing::Point(440, 60);
			this->btnConsultar->Size = System::Drawing::Size(130, 40);
			this->btnConsultar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnConsultar_Click);

			this->picImatge->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picImatge->Location = System::Drawing::Point(20, 120);
			this->picImatge->Size = System::Drawing::Size(550, 200);

			this->lblNoticies->Text = L"Notícies Generals";
			this->lblNoticies->Location = System::Drawing::Point(20, 330);
			this->lblNoticies->AutoSize = true;

			this->lstNoticies->Location = System::Drawing::Point(20, 350);
			this->lstNoticies->Size = System::Drawing::Size(550, 80);

			this->btnLogoutMainMenu->Text = L"Tancar Sessió";
			this->btnLogoutMainMenu->Location = System::Drawing::Point(470, 20);
			this->btnLogoutMainMenu->Size = System::Drawing::Size(100, 25);
			this->btnLogoutMainMenu->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnLogout_Click);

			// pnlConsultar
			this->pnlConsultar = gcnew System::Windows::Forms::Panel();
			this->lblConsultarTitle = gcnew System::Windows::Forms::Label();
			this->btnTornarConsultar = gcnew System::Windows::Forms::Button();
			this->lblNomLliga = gcnew System::Windows::Forms::Label();
			this->txtNomLliga = gcnew System::Windows::Forms::TextBox();
			this->btnComprovarLliga = gcnew System::Windows::Forms::Button();
			this->btnCrearLligaMainMenu = gcnew System::Windows::Forms::Button();
			this->pnlMain->Controls->Add(this->btnCrearLligaMainMenu);

			

			

			this->btnCrearLligaMainMenu->Text = L"Crear Lliga";
			this->btnCrearLligaMainMenu->Size = System::Drawing::Size(130, 40);
			this->btnCrearLligaMainMenu->Visible = false;
			this->btnCrearLligaMainMenu->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCrearLligaMainMenu_Click);
			this->pnlConsultar->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlConsultar->Visible = false;
			this->pnlConsultar->Controls->Add(this->lblConsultarTitle);
			this->pnlConsultar->Controls->Add(this->btnTornarConsultar);
			this->pnlConsultar->Controls->Add(this->lblNomLliga);
			this->pnlConsultar->Controls->Add(this->txtNomLliga);
			this->pnlConsultar->Controls->Add(this->btnComprovarLliga);

			this->lblConsultarTitle->Text = L"Consultar";
			this->lblConsultarTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblConsultarTitle->AutoSize = true;
			this->lblConsultarTitle->Location = System::Drawing::Point(350, 30);

			this->btnTornarConsultar->Text = L"Tornar";
			this->btnTornarConsultar->Size = System::Drawing::Size(100, 30);
			this->btnTornarConsultar->Location = System::Drawing::Point(30, 30);
			this->btnTornarConsultar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnTornarConsultar_Click);

			this->lblNomLliga->Text = L"Nom de la lliga";
			this->lblNomLliga->Location = System::Drawing::Point(300, 140);
			this->lblNomLliga->Size = System::Drawing::Size(120, 20);
			this->lblNomLliga->Visible = true;

			this->txtNomLliga->Text = L"";
			this->txtNomLliga->Location = System::Drawing::Point(430, 140);
			this->txtNomLliga->Size = System::Drawing::Size(200, 20);
			this->txtNomLliga->Visible = true;

			this->btnComprovarLliga->Text = L"Comprovar lliga";
			this->btnComprovarLliga->Location = System::Drawing::Point(430, 180);
			this->btnComprovarLliga->Size = System::Drawing::Size(200, 35);
			this->btnComprovarLliga->UseVisualStyleBackColor = true;
			this->btnComprovarLliga->Visible = true;
			this->btnComprovarLliga->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnComprovarLliga_Click);

			// pnlCrearLliga
			this->pnlCrearLliga = gcnew System::Windows::Forms::Panel();
			this->lblCLTitle = gcnew System::Windows::Forms::Label();
			this->lblCLNom = gcnew System::Windows::Forms::Label();
			this->txtCLNom = gcnew System::Windows::Forms::TextBox();
			this->lblCLPass = gcnew System::Windows::Forms::Label();
			this->txtCLPass = gcnew System::Windows::Forms::TextBox();
			this->lblCLEsport = gcnew System::Windows::Forms::Label();
			this->cmbCLEsport = gcnew System::Windows::Forms::ComboBox();
			this->btnCLGuarda = gcnew System::Windows::Forms::Button();
			this->btnCLTornar = gcnew System::Windows::Forms::Button();

			this->pnlCrearLliga->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlCrearLliga->Visible = false;
			this->pnlCrearLliga->Controls->Add(this->lblCLTitle);
			this->pnlCrearLliga->Controls->Add(this->lblCLNom);
			this->pnlCrearLliga->Controls->Add(this->txtCLNom);
			this->pnlCrearLliga->Controls->Add(this->lblCLPass);
			this->pnlCrearLliga->Controls->Add(this->txtCLPass);
			this->pnlCrearLliga->Controls->Add(this->lblCLEsport);
			this->pnlCrearLliga->Controls->Add(this->cmbCLEsport);
			this->pnlCrearLliga->Controls->Add(this->btnCLGuarda);
			this->pnlCrearLliga->Controls->Add(this->btnCLTornar);

			this->lblCLTitle->Text = L"Crear Nova Lliga";
			this->lblCLTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblCLTitle->AutoSize = true;

			this->lblCLNom->Text = L"Nom de la Lliga:";
			this->lblCLNom->Size = System::Drawing::Size(100, 20);

			this->txtCLNom->Size = System::Drawing::Size(150, 20);

			this->lblCLPass->Text = L"Contrasenya:";
			this->lblCLPass->Size = System::Drawing::Size(100, 20);

			this->txtCLPass->UseSystemPasswordChar = true;
			this->txtCLPass->Size = System::Drawing::Size(150, 20);

			this->lblCLEsport->Text = L"Esport:";
			this->lblCLEsport->Size = System::Drawing::Size(100, 20);

			this->cmbCLEsport->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Futbol", L"Basquet", L"Voley" });
			this->cmbCLEsport->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCLEsport->Size = System::Drawing::Size(150, 20);

			this->btnCLGuarda->Text = L"Crear";
			this->btnCLGuarda->Size = System::Drawing::Size(100, 30);
			this->btnCLGuarda->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCLGuarda_Click);

			this->btnCLTornar->Text = L"Tornar";
			this->btnCLTornar->Size = System::Drawing::Size(100, 30);
			this->btnCLTornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCLTornar_Click);



			this->btnEnregistrarEquip = gcnew System::Windows::Forms::Button();
			this->pnlMain->Controls->Add(this->btnEnregistrarEquip);
			this->btnEnregistrarEquip->Text = L"Enregistrar Equip";
			this->btnEnregistrarEquip->Size = System::Drawing::Size(130, 40);
			this->btnEnregistrarEquip->Visible = false;
			this->btnEnregistrarEquip->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEnregistrarEquip_Click);

			this->btnUnirEquipLliga = gcnew System::Windows::Forms::Button();
			this->pnlMain->Controls->Add(this->btnUnirEquipLliga);
			this->btnUnirEquipLliga->Text = L"Unir equip a lliga";
			this->btnUnirEquipLliga->Size = System::Drawing::Size(130, 40);
			this->btnUnirEquipLliga->Visible = false;
			this->btnUnirEquipLliga->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnUnirEquipLligaAct_Click);
	

			

			// pnlGestionarLliga
			this->pnlGestionarLliga = gcnew System::Windows::Forms::Panel();
			this->lblGLTitle = gcnew System::Windows::Forms::Label();
			this->btnGLAfegirPartit = gcnew System::Windows::Forms::Button();
			this->btnGLEditarPartit = gcnew System::Windows::Forms::Button();
			this->btnGLMostrarEquips = gcnew System::Windows::Forms::Button();
			this->btnGLEsborrarEquip = gcnew System::Windows::Forms::Button();
			this->btnGLCrearJornada = gcnew System::Windows::Forms::Button(); 
			this->btnGLCrearTemporada = gcnew System::Windows::Forms::Button();
			this->btnGLTornar = gcnew System::Windows::Forms::Button();

			this->picLogoGL = gcnew System::Windows::Forms::PictureBox();
			this->pnlGestionarLliga->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlGestionarLliga->Visible = false;
			this->pnlGestionarLliga->Controls->Add(this->lblGLTitle);
			this->pnlGestionarLliga->Controls->Add(this->btnGLAfegirPartit);
			this->pnlGestionarLliga->Controls->Add(this->btnGLEditarPartit);
			this->pnlGestionarLliga->Controls->Add(this->btnGLMostrarEquips);
			this->pnlGestionarLliga->Controls->Add(this->btnGLEsborrarEquip);
			this->pnlGestionarLliga->Controls->Add(this->btnGLCrearJornada);
			this->pnlGestionarLliga->Controls->Add(this->btnGLCrearTemporada);
			this->pnlGestionarLliga->Controls->Add(this->btnGLTornar);
			this->pnlGestionarLliga->Controls->Add(this->picLogoGL);
			
			this->picLogoGL->ImageLocation = L"imatges\\logo.png";
			this->picLogoGL->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoGL->Size = System::Drawing::Size(150, 100);

			this->lblGLTitle->Text = L"Gestionar Lliga";
			this->lblGLTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblGLTitle->AutoSize = true;

			System::Drawing::Font^ actionBtnFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);

			this->btnGLAfegirPartit->Text = L"Crear partit";
			this->btnGLAfegirPartit->Size = System::Drawing::Size(220, 60);
			this->btnGLAfegirPartit->Font = actionBtnFont;
			this->btnGLAfegirPartit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLAfegirPartit->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLAfegirPartit_Click);

			this->btnGLEditarPartit->Text = L"Editar partit";
			this->btnGLEditarPartit->Size = System::Drawing::Size(220, 60);
			this->btnGLEditarPartit->Font = actionBtnFont;
			this->btnGLEditarPartit->Cursor = System::Windows::Forms::Cursors::Hand;
          this->btnGLEditarPartit->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLEditarPartit_Click);

			this->btnGLMostrarEquips->Text = L"Mostrar equips";
			this->btnGLMostrarEquips->Size = System::Drawing::Size(220, 60);
			this->btnGLMostrarEquips->Font = actionBtnFont;
			this->btnGLMostrarEquips->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLMostrarEquips->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLMostrarEquips_Click);

			this->btnGLEsborrarEquip->Text = L"Esborrar equip";
			this->btnGLEsborrarEquip->Size = System::Drawing::Size(220, 60);
			this->btnGLEsborrarEquip->Font = actionBtnFont;
			this->btnGLEsborrarEquip->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLEsborrarEquip->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLEsborrarEquip_Click);

			
			this->btnGLCrearJornada->Text = L"Crear jornada";
			this->btnGLCrearJornada->Size = System::Drawing::Size(220, 60);
			this->btnGLCrearJornada->Font = actionBtnFont;
			this->btnGLCrearJornada->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLCrearJornada->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLCrearJornada_Click);
			

			this->btnGLCrearTemporada->Text = L"Crear temporada";
			this->btnGLCrearTemporada->Size = System::Drawing::Size(220, 60);
			this->btnGLCrearTemporada->Font = actionBtnFont;
			this->btnGLCrearTemporada->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLCrearTemporada->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLCrearTemporada_Click);

			this->btnGLRetirarTemporada = gcnew System::Windows::Forms::Button();
			this->pnlGestionarLliga->Controls->Add(this->btnGLRetirarTemporada);
			this->btnGLRetirarTemporada->Text = L"Retirar temporada";
			this->btnGLRetirarTemporada->Size = System::Drawing::Size(220, 60);
			this->btnGLRetirarTemporada->Font = actionBtnFont;
			this->btnGLRetirarTemporada->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLRetirarTemporada->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLRetirarTemporada_Click);

			this->btnGLTornar->Text = L"Tornar";
			this->btnGLTornar->Size = System::Drawing::Size(100, 30);
			this->btnGLTornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLTornar_Click);

			// pnlEstadistiques
			this->pnlEstadistiques = gcnew System::Windows::Forms::Panel();
			this->lblEstTitle = gcnew System::Windows::Forms::Label();
			this->btnEstEquips = gcnew System::Windows::Forms::Button();
			this->btnEstTornar = gcnew System::Windows::Forms::Button();
			this->picLogoEst = gcnew System::Windows::Forms::PictureBox();

			this->pnlEstadistiques->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlEstadistiques->Visible = false;
			this->pnlEstadistiques->Controls->Add(this->lblEstTitle);
			this->pnlEstadistiques->Controls->Add(this->btnEstEquips);
			this->pnlEstadistiques->Controls->Add(this->btnEstTornar);
			this->pnlEstadistiques->Controls->Add(this->picLogoEst);

			this->picLogoEst->ImageLocation = L"imatges\\logo.png";
			this->picLogoEst->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoEst->Size = System::Drawing::Size(150, 100);

			this->lblEstTitle->Text = L"Estadístiques";
			this->lblEstTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblEstTitle->AutoSize = true;

			this->btnEstEquips->Text = L"Estadístiques equips";
			this->btnEstEquips->Size = System::Drawing::Size(220, 60);
			this->btnEstEquips->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnEstEquips->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnEstEquips->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstadistiques_Click);

			this->btnEstTornar->Text = L"Tornar";
			this->btnEstTornar->Size = System::Drawing::Size(100, 30);
			this->btnEstTornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstTornar_Click);

			// Form
			this->Controls->Add(this->pnlInici);
			this->Controls->Add(this->pnlLogin);
			this->Controls->Add(this->pnlRegister);
			this->Controls->Add(this->pnlMain);
			this->Controls->Add(this->pnlConsultar);
			this->Controls->Add(this->pnlCrearLliga);
			this->Controls->Add(this->pnlGestionarLliga);
			this->Controls->Add(this->pnlEstadistiques);

			// pnlCrearPartit
			this->pnlCrearPartit = gcnew System::Windows::Forms::Panel();
			this->pnlCrearPartit->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlCrearPartit->Visible = false;

			this->lblCPTitle = gcnew System::Windows::Forms::Label();
			this->lblCPNomLliga = gcnew System::Windows::Forms::Label();
			this->txtCPNomLliga = gcnew System::Windows::Forms::TextBox();
			this->btnCPValidarLliga = gcnew System::Windows::Forms::Button();
			this->lblCPTemporada = gcnew System::Windows::Forms::Label();
			this->cmbCPTemporada = gcnew System::Windows::Forms::ComboBox();
			this->cpTemporadesIds = gcnew System::Collections::Generic::List<String^>();
			this->cpJornadesIds = gcnew System::Collections::Generic::List<String^>();
			this->lblCPJornada = gcnew System::Windows::Forms::Label();
			this->cmbCPJornada = gcnew System::Windows::Forms::ComboBox();
			this->lblCPData = gcnew System::Windows::Forms::Label();
			this->dtpCPData = gcnew System::Windows::Forms::DateTimePicker();
			this->lblCPUbicacio = gcnew System::Windows::Forms::Label();
			this->txtCPUbicacio = gcnew System::Windows::Forms::TextBox();
			this->lblCPEquipLocal = gcnew System::Windows::Forms::Label();
			this->cmbCPEquipLocal = gcnew System::Windows::Forms::ComboBox();
			this->lblCPEquipVisitant = gcnew System::Windows::Forms::Label();
			this->cmbCPEquipVisitant = gcnew System::Windows::Forms::ComboBox();
			this->btnCPConfirmar = gcnew System::Windows::Forms::Button();
			this->btnCPCancellar = gcnew System::Windows::Forms::Button();

			//pnl Esborrar Partir 

			this->btnGLEsborrarPartit = gcnew System::Windows::Forms::Button();
			this->pnlGestionarLliga->Controls->Add(this->btnGLEsborrarPartit);
			this->btnGLEsborrarPartit->Text = L"Esborrar partit";
			this->btnGLEsborrarPartit->Size = System::Drawing::Size(220, 60);
			this->btnGLEsborrarPartit->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGLEsborrarPartit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLEsborrarPartit->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLEsborrarPartit_Click);

			// --- Añadir todos los controles al Panel ---
			this->pnlCrearPartit->Controls->Add(this->lblCPTitle);
			this->pnlCrearPartit->Controls->Add(this->lblCPNomLliga);     // AFEGIT
			this->pnlCrearPartit->Controls->Add(this->txtCPNomLliga);     // AFEGIT
			this->pnlCrearPartit->Controls->Add(this->btnCPValidarLliga); // AFEGIT
			this->pnlCrearPartit->Controls->Add(this->lblCPTemporada);    // AFEGIT
			this->pnlCrearPartit->Controls->Add(this->cmbCPTemporada);    // AFEGIT
			this->pnlCrearPartit->Controls->Add(this->lblCPJornada);
			this->pnlCrearPartit->Controls->Add(this->cmbCPJornada);
			this->pnlCrearPartit->Controls->Add(this->lblCPData);
			this->pnlCrearPartit->Controls->Add(this->dtpCPData);
			this->pnlCrearPartit->Controls->Add(this->lblCPUbicacio);
			this->pnlCrearPartit->Controls->Add(this->txtCPUbicacio);
			this->pnlCrearPartit->Controls->Add(this->lblCPEquipLocal);
			this->pnlCrearPartit->Controls->Add(this->cmbCPEquipLocal);
			this->pnlCrearPartit->Controls->Add(this->lblCPEquipVisitant);
			this->pnlCrearPartit->Controls->Add(this->cmbCPEquipVisitant);
			this->pnlCrearPartit->Controls->Add(this->btnCPConfirmar);
			this->pnlCrearPartit->Controls->Add(this->btnCPCancellar);

			this->lblCPTitle->Text = L"Crear Partit";
			this->lblCPTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblCPTitle->AutoSize = true;

			// --- Propiedades NOU CAMPS Lliga i Temporada ---
			this->lblCPNomLliga->Text = L"Nom Lliga:";
			this->lblCPNomLliga->Size = System::Drawing::Size(100, 20);
			this->txtCPNomLliga->Size = System::Drawing::Size(100, 20);

			this->btnCPValidarLliga->Text = L"Validar Lliga";
			this->btnCPValidarLliga->Size = System::Drawing::Size(100, 25);
			this->btnCPValidarLliga->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCPValidarLliga_Click);

			this->lblCPTemporada->Text = L"Temporada:";
			this->lblCPTemporada->Size = System::Drawing::Size(100, 20);
			this->cmbCPTemporada->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCPTemporada->Size = System::Drawing::Size(150, 20);
			this->cmbCPTemporada->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cmbCPTemporada_SelectedIndexChanged);

			// --- Resta de propietats originals ---
			this->lblCPJornada->Text = L"Jornada:";
			this->lblCPJornada->Size = System::Drawing::Size(100, 20);
			this->cmbCPJornada->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCPJornada->Size = System::Drawing::Size(150, 20);

			this->lblCPData->Text = L"Data del partit:";
			this->lblCPData->Size = System::Drawing::Size(100, 20);
			this->dtpCPData->Size = System::Drawing::Size(150, 20);
			this->dtpCPData->Format = System::Windows::Forms::DateTimePickerFormat::Short;

			this->lblCPUbicacio->Text = L"Ubicació:";
			this->lblCPUbicacio->Size = System::Drawing::Size(100, 20);
			this->txtCPUbicacio->Size = System::Drawing::Size(150, 20);

			this->lblCPEquipLocal->Text = L"Equip Local:";
			this->lblCPEquipLocal->Size = System::Drawing::Size(100, 20);
			this->cmbCPEquipLocal->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCPEquipLocal->Size = System::Drawing::Size(150, 20);

			this->lblCPEquipVisitant->Text = L"Equip Visitant:";
			this->lblCPEquipVisitant->Size = System::Drawing::Size(100, 20);
			this->cmbCPEquipVisitant->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCPEquipVisitant->Size = System::Drawing::Size(150, 20);

			this->btnCPConfirmar->Text = L"Confirmar";
			this->btnCPConfirmar->Size = System::Drawing::Size(100, 30);
			this->btnCPConfirmar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCPConfirmar_Click);

			this->btnCPCancellar->Text = L"Cancel·lar";
			this->btnCPCancellar->Size = System::Drawing::Size(100, 30);
			this->btnCPCancellar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCPCancellar_Click);

			// pnlCrearTemporada
			this->pnlCrearTemporada = gcnew System::Windows::Forms::Panel();
			this->lblCTTitle = gcnew System::Windows::Forms::Label();
			this->lblCTNomLliga = gcnew System::Windows::Forms::Label();   
			this->txtCTNomLliga = gcnew System::Windows::Forms::TextBox();
			this->lblCTDataInici = gcnew System::Windows::Forms::Label();
			this->dtpCTDataInici = gcnew System::Windows::Forms::DateTimePicker();
			this->lblCTDataFi = gcnew System::Windows::Forms::Label();
			this->dtpCTDataFi = gcnew System::Windows::Forms::DateTimePicker();
			this->btnCTConfirmar = gcnew System::Windows::Forms::Button();
			this->btnCTCancellar = gcnew System::Windows::Forms::Button();

			this->pnlCrearTemporada->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlCrearTemporada->Visible = false;
			this->pnlCrearTemporada->Controls->Add(this->lblCTTitle);
			this->pnlCrearTemporada->Controls->Add(this->lblCTNomLliga);
			this->pnlCrearTemporada->Controls->Add(this->txtCTNomLliga);
			this->pnlCrearTemporada->Controls->Add(this->lblCTDataInici);
			this->pnlCrearTemporada->Controls->Add(this->dtpCTDataInici);
			this->pnlCrearTemporada->Controls->Add(this->lblCTDataFi);
			this->pnlCrearTemporada->Controls->Add(this->dtpCTDataFi);
			this->pnlCrearTemporada->Controls->Add(this->btnCTConfirmar);
			this->pnlCrearTemporada->Controls->Add(this->btnCTCancellar);

			this->lblCTTitle->Text = L"Crear Temporada";
			this->lblCTTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblCTTitle->AutoSize = true;

			this->lblCTNomLliga->Text = L"Nom de la Lliga:";
			this->lblCTNomLliga->Size = System::Drawing::Size(100, 20);
			this->txtCTNomLliga->Size = System::Drawing::Size(150, 20);


			this->lblCTDataInici->Text = L"Data d'Inici:";
			this->dtpCTDataInici->Format = System::Windows::Forms::DateTimePickerFormat::Short;

			this->lblCTDataFi->Text = L"Data de Fi:";
			this->dtpCTDataFi->Format = System::Windows::Forms::DateTimePickerFormat::Short;

			this->btnCTConfirmar->Text = L"Confirmar";
			this->btnCTConfirmar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCTConfirmar_Click);

			this->btnCTCancellar->Text = L"Cancel·lar";
			this->btnCTCancellar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCTCancellar_Click);

			this->Controls->Add(this->pnlCrearTemporada);

			this->Controls->Add(this->pnlCrearPartit);

			// pnlCrearJornada
			this->pnlCrearJornada = gcnew System::Windows::Forms::Panel();
			this->lblCJTitle = gcnew System::Windows::Forms::Label();
			this->lblCJNomLliga = gcnew System::Windows::Forms::Label();
			this->txtCJNomLliga = gcnew System::Windows::Forms::TextBox();
			this->btnCJBuscarTemporades = gcnew System::Windows::Forms::Button();
			this->lblCJTemporada = gcnew System::Windows::Forms::Label();
			this->cmbCJTemporada = gcnew System::Windows::Forms::ComboBox();
			this->lblCJDataInici = gcnew System::Windows::Forms::Label();
			this->dtpCJDataInici = gcnew System::Windows::Forms::DateTimePicker();
			this->lblCJDataFi = gcnew System::Windows::Forms::Label();
			this->dtpCJDataFi = gcnew System::Windows::Forms::DateTimePicker();
			this->btnCJConfirmar = gcnew System::Windows::Forms::Button();
			this->btnCJCancellar = gcnew System::Windows::Forms::Button();
			this->cjTemporadaIds = gcnew System::Collections::Generic::List<String^>();
			this->lblCJNumero = gcnew System::Windows::Forms::Label();
			this->txtCJNumero = gcnew System::Windows::Forms::TextBox();
			


			this->pnlCrearJornada->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlCrearJornada->Visible = false;
			this->pnlCrearJornada->Controls->Add(this->lblCJTitle);
			this->pnlCrearJornada->Controls->Add(this->lblCJNomLliga);
			this->pnlCrearJornada->Controls->Add(this->txtCJNomLliga);
			this->pnlCrearJornada->Controls->Add(this->btnCJBuscarTemporades);
			this->pnlCrearJornada->Controls->Add(this->lblCJTemporada);
			this->pnlCrearJornada->Controls->Add(this->cmbCJTemporada);
			this->pnlCrearJornada->Controls->Add(this->lblCJDataInici);
			this->pnlCrearJornada->Controls->Add(this->dtpCJDataInici);
			this->pnlCrearJornada->Controls->Add(this->lblCJDataFi);
			this->pnlCrearJornada->Controls->Add(this->dtpCJDataFi);
			this->pnlCrearJornada->Controls->Add(this->lblCJNumero);
			this->pnlCrearJornada->Controls->Add(this->txtCJNumero);
			this->pnlCrearJornada->Controls->Add(this->btnCJConfirmar);
			this->pnlCrearJornada->Controls->Add(this->btnCJCancellar);

			this->lblCJTitle->Text = L"Crear Jornada";
			this->lblCJTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblCJTitle->AutoSize = true;

			this->lblCJNomLliga->Text = L"Nom Lliga:";
			this->btnCJBuscarTemporades->Text = L"Cercar Temporades";
			this->btnCJBuscarTemporades->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCJBuscarTemporades_Click);

			this->lblCJTemporada->Text = L"Temporada:";
			this->cmbCJTemporada->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

			this->lblCJNumero->Text = L"Número Jornada:";

			this->lblCJDataInici->Text = L"Data d'Inici:";
			this->dtpCJDataInici->Format = System::Windows::Forms::DateTimePickerFormat::Short;

			this->lblCJDataFi->Text = L"Data de Fi:";
			this->dtpCJDataFi->Format = System::Windows::Forms::DateTimePickerFormat::Short;

			this->btnCJConfirmar->Text = L"Confirmar";
			this->btnCJConfirmar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCJConfirmar_Click);

			this->btnCJCancellar->Text = L"Cancel·lar";
			this->btnCJCancellar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnCJCancellar_Click);

			// AFEGIR pnlCrearJornada AL FORMULARi
			this->Controls->Add(this->pnlCrearJornada);

			// pnlEnregistrarEquip
			this->pnlEnregistrarEquip = gcnew System::Windows::Forms::Panel();
			this->lblEETitle = gcnew System::Windows::Forms::Label();
			this->lblEENom = gcnew System::Windows::Forms::Label();
			this->txtEENom = gcnew System::Windows::Forms::TextBox();
			this->lblEEData = gcnew System::Windows::Forms::Label();
			this->dtpEEData = gcnew System::Windows::Forms::DateTimePicker();
			this->lblEEEscollirEsport = gcnew System::Windows::Forms::Label();
			this->cmbEEEscollirEsport = gcnew System::Windows::Forms::ComboBox();
			this->btnEEEnregistrar = gcnew System::Windows::Forms::Button();
			this->btnEETornar = gcnew System::Windows::Forms::Button();

			this->pnlEnregistrarEquip->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlEnregistrarEquip->Visible = false;
			this->pnlEnregistrarEquip->Controls->Add(this->lblEETitle);
			this->pnlEnregistrarEquip->Controls->Add(this->lblEENom);
			this->pnlEnregistrarEquip->Controls->Add(this->txtEENom);
			this->pnlEnregistrarEquip->Controls->Add(this->lblEEData);
			this->pnlEnregistrarEquip->Controls->Add(this->dtpEEData);
			this->pnlEnregistrarEquip->Controls->Add(this->lblEEEscollirEsport);
			this->pnlEnregistrarEquip->Controls->Add(this->cmbEEEscollirEsport);
			this->pnlEnregistrarEquip->Controls->Add(this->btnEEEnregistrar);
			this->pnlEnregistrarEquip->Controls->Add(this->btnEETornar);

			this->lblEETitle->Text = L"Enregistrar Equip";
			this->lblEETitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblEETitle->AutoSize = true;

			this->lblEENom->Text = L"Nom de l'Equip:";
			this->lblEENom->Size = System::Drawing::Size(100, 20);

			this->txtEENom->Size = System::Drawing::Size(150, 20);

			this->lblEEData->Text = L"Data Fundació:";
			this->lblEEData->Size = System::Drawing::Size(100, 20);

			this->dtpEEData->Size = System::Drawing::Size(150, 20);
			this->dtpEEData->Format = System::Windows::Forms::DateTimePickerFormat::Short;

			this->lblEEEscollirEsport->Text = L"Esport:";
			this->lblEEEscollirEsport->Size = System::Drawing::Size(100, 20);

			this->cmbEEEscollirEsport->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Futbol", L"Basquet", L"Voley" });
			this->cmbEEEscollirEsport->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEEEscollirEsport->Size = System::Drawing::Size(150, 20);

			this->btnEEEnregistrar->Text = L"Enregistrar";
			this->btnEEEnregistrar->Size = System::Drawing::Size(100, 30);
			this->btnEEEnregistrar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEEEnregistrar_Click);

			this->btnEETornar->Text = L"Tornar";
			this->btnEETornar->Size = System::Drawing::Size(100, 30);
			this->btnEETornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEETornar_Click);

			this->Controls->Add(this->pnlEnregistrarEquip);

			// pnlGestionarEquip
			this->pnlGestionarEquip = gcnew System::Windows::Forms::Panel();
			this->lblGETitle = gcnew System::Windows::Forms::Label();
			this->dgvPlantilla = gcnew System::Windows::Forms::DataGridView();
			this->btnGEEsborrarEquip = gcnew System::Windows::Forms::Button();
			this->btnGEAfegirJugador = gcnew System::Windows::Forms::Button();
            this->btnGEEliminarJugador = gcnew System::Windows::Forms::Button();
			this->btnGEAssignarJugador = gcnew System::Windows::Forms::Button();
			this->btnGETornar = gcnew System::Windows::Forms::Button();

			this->pnlGestionarEquip->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlGestionarEquip->Visible = false;
			this->pnlGestionarEquip->Controls->Add(this->lblGETitle);
			this->pnlGestionarEquip->Controls->Add(this->dgvPlantilla);
			this->pnlGestionarEquip->Controls->Add(this->btnGEEsborrarEquip);
			this->pnlGestionarEquip->Controls->Add(this->btnGEAfegirJugador);
         this->pnlGestionarEquip->Controls->Add(this->btnGEEliminarJugador);
			this->pnlGestionarEquip->Controls->Add(this->btnGEAssignarJugador);
			this->pnlGestionarEquip->Controls->Add(this->btnGETornar);

			this->lblGETitle->Text = L"Gestionar Equip";
			this->lblGETitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblGETitle->AutoSize = true;

			this->dgvPlantilla->AllowUserToAddRows = false;
			this->dgvPlantilla->AllowUserToDeleteRows = false;
			this->dgvPlantilla->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvPlantilla->ReadOnly = true;
			this->dgvPlantilla->RowHeadersVisible = false;
			this->dgvPlantilla->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvPlantilla->Size = System::Drawing::Size(400, 150);

			actionBtnFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);

			this->btnGEEsborrarEquip->Text = L"Esborrar equip";
			this->btnGEEsborrarEquip->Size = System::Drawing::Size(220, 60);
			this->btnGEEsborrarEquip->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGEEsborrarEquip->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGEEsborrarEquip->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGEEsborrarEquip_Click);

			this->btnGEAfegirJugador->Text = L"Afegir jugador";
			this->btnGEAfegirJugador->Size = System::Drawing::Size(220, 60);
			this->btnGEAfegirJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGEAfegirJugador->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGEAfegirJugador->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGEAfegirJugador_Click);

			this->btnGEEliminarJugador->Text = L"Eliminar jugador";
			this->btnGEEliminarJugador->Size = System::Drawing::Size(220, 60);
			this->btnGEEliminarJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGEEliminarJugador->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGEEliminarJugador->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGEEliminarJugador_Click);

			this->btnGEAssignarJugador->Text = L"Assignar jugador a partit";
			this->btnGEAssignarJugador->Size = System::Drawing::Size(220, 60);
			this->btnGEAssignarJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGEAssignarJugador->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGEAssignarJugador->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGEAssignarJugador_Click);

			this->btnGETornar->Text = L"Tornar";
			this->btnGETornar->Size = System::Drawing::Size(100, 30);
			this->btnGETornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGETornar_Click);

			this->Controls->Add(this->pnlGestionarEquip);

			// pnlAfegirJugador
			this->pnlAfegirJugador = gcnew System::Windows::Forms::Panel();
			this->lblAJTitle = gcnew System::Windows::Forms::Label();
			this->lblAJCorreu = gcnew System::Windows::Forms::Label();
			this->txtAJCorreu = gcnew System::Windows::Forms::TextBox();
			this->lblAJDorsal = gcnew System::Windows::Forms::Label();
			this->txtAJDorsal = gcnew System::Windows::Forms::TextBox();
			this->lblAJPosicio = gcnew System::Windows::Forms::Label();
			this->txtAJPosicio = gcnew System::Windows::Forms::TextBox();
			this->btnAJConfirmar = gcnew System::Windows::Forms::Button();
			this->btnAJCancellar = gcnew System::Windows::Forms::Button();

			this->pnlAfegirJugador->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlAfegirJugador->Visible = false;
			this->pnlAfegirJugador->Controls->Add(this->lblAJTitle);
			this->pnlAfegirJugador->Controls->Add(this->lblAJCorreu);
			this->pnlAfegirJugador->Controls->Add(this->txtAJCorreu);
			this->pnlAfegirJugador->Controls->Add(this->lblAJDorsal);
			this->pnlAfegirJugador->Controls->Add(this->txtAJDorsal);
			this->pnlAfegirJugador->Controls->Add(this->lblAJPosicio);
			this->pnlAfegirJugador->Controls->Add(this->txtAJPosicio);
			this->pnlAfegirJugador->Controls->Add(this->btnAJConfirmar);
			this->pnlAfegirJugador->Controls->Add(this->btnAJCancellar);

			this->lblAJTitle->Text = L"Afegir Jugador";
			this->lblAJTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblAJTitle->AutoSize = true;

			this->lblAJCorreu->Text = L"Correu Estudiant:";
			this->lblAJCorreu->Size = System::Drawing::Size(120, 20);

			this->txtAJCorreu->Size = System::Drawing::Size(200, 20);

			this->lblAJDorsal->Text = L"Dorsal:";
			this->lblAJDorsal->Size = System::Drawing::Size(120, 20);

			this->txtAJDorsal->Size = System::Drawing::Size(200, 20);

			this->lblAJPosicio->Text = L"Posició (Opcional):";
			this->lblAJPosicio->Size = System::Drawing::Size(120, 20);

			this->txtAJPosicio->Size = System::Drawing::Size(200, 20);

			this->btnAJConfirmar->Text = L"Confirmar";
			this->btnAJConfirmar->Size = System::Drawing::Size(100, 30);
			this->btnAJConfirmar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnAJConfirmar_Click);

			this->btnAJCancellar->Text = L"Cancel·lar";
			this->btnAJCancellar->Size = System::Drawing::Size(100, 30);
			this->btnAJCancellar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnAJCancellar_Click);

			this->Controls->Add(this->pnlAfegirJugador);

			// pnlUnirEquipLliga
			this->pnlUnirEquipLliga = gcnew System::Windows::Forms::Panel();
			this->lblUELTitle = gcnew System::Windows::Forms::Label();
			this->lblUELNom = gcnew System::Windows::Forms::Label();
			this->txtUELNom = gcnew System::Windows::Forms::TextBox();
			this->btnUELComprovar = gcnew System::Windows::Forms::Button();
			this->lblUELPass = gcnew System::Windows::Forms::Label();
			this->txtUELPass = gcnew System::Windows::Forms::TextBox();
			this->btnUELUnir = gcnew System::Windows::Forms::Button();
			this->btnUELTornar = gcnew System::Windows::Forms::Button();

			this->pnlUnirEquipLliga->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlUnirEquipLliga->Visible = false;
			this->pnlUnirEquipLliga->Controls->Add(this->lblUELTitle);
			this->pnlUnirEquipLliga->Controls->Add(this->lblUELNom);
			this->pnlUnirEquipLliga->Controls->Add(this->txtUELNom);
			this->pnlUnirEquipLliga->Controls->Add(this->btnUELComprovar);
			this->pnlUnirEquipLliga->Controls->Add(this->lblUELPass);
		 this->pnlUnirEquipLliga->Controls->Add(this->txtUELPass);
			this->pnlUnirEquipLliga->Controls->Add(this->btnUELUnir);
			this->pnlUnirEquipLliga->Controls->Add(this->btnUELTornar);

			this->lblUELTitle->Text = L"Unir Equip a Lliga";
			this->lblUELTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblUELTitle->AutoSize = true;

			this->lblUELNom->Text = L"Nom de la Lliga:";
			this->lblUELNom->Size = System::Drawing::Size(100, 20);

			this->txtUELNom->Size = System::Drawing::Size(150, 20);

			this->btnUELComprovar->Text = L"Comprovar";
			this->btnUELComprovar->Size = System::Drawing::Size(100, 30);
			this->btnUELComprovar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnUELComprovar_Click);

			this->lblUELPass->Text = L"Contrasenya:";
			this->lblUELPass->Size = System::Drawing::Size(100, 20);
			this->lblUELPass->Visible = false;

			this->txtUELPass->UseSystemPasswordChar = true;
			this->txtUELPass->Size = System::Drawing::Size(150, 20);
			this->txtUELPass->Visible = false;

			this->btnUELUnir->Text = L"Unir";
			this->btnUELUnir->Size = System::Drawing::Size(100, 30);
			this->btnUELUnir->Visible = false;
			this->btnUELUnir->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnUELUnir_Click);

			this->btnUELTornar->Text = L"Tornar";
			this->btnUELTornar->Size = System::Drawing::Size(100, 30);
			this->btnUELTornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnUELTornar_Click);

			this->Controls->Add(this->pnlUnirEquipLliga);

			this->btnGLEsborrarPartit->Text = L"Esborrar partit";
			this->btnGLEsborrarPartit->Size = System::Drawing::Size(220, 60);
			this->btnGLEsborrarPartit->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGLEsborrarPartit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLEsborrarPartit->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGLEsborrarPartit_Click);

			// pnlEsborrarParti

			this->pnlEsborrarPartit = gcnew System::Windows::Forms::Panel();
			this->lblEPTitle = gcnew System::Windows::Forms::Label();
			this->btnEPTornar = gcnew System::Windows::Forms::Button();

			this->lblEPTemporada = gcnew System::Windows::Forms::Label();
			this->cmbEPTemporades = gcnew System::Windows::Forms::ComboBox();
			this->epTemporadaIds = gcnew System::Collections::Generic::List<String^>();

			this->lblEPJornada = gcnew System::Windows::Forms::Label();
			this->cmbEPJornades = gcnew System::Windows::Forms::ComboBox();
			this->epJornadaIds = gcnew System::Collections::Generic::List<String^>();

			this->lblEPPartit = gcnew System::Windows::Forms::Label();
			this->cmbEPPartits = gcnew System::Windows::Forms::ComboBox();
			this->epPartitIds = gcnew System::Collections::Generic::List<String^>();

			this->btnEPEsborrarFinal = gcnew System::Windows::Forms::Button();

			this->pnlEsborrarPartit->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlEsborrarPartit->Visible = false;

			this->pnlEsborrarPartit->Controls->Add(this->lblEPTitle);
			this->pnlEsborrarPartit->Controls->Add(this->btnEPTornar);
			this->pnlEsborrarPartit->Controls->Add(this->lblEPTemporada);
			this->pnlEsborrarPartit->Controls->Add(this->cmbEPTemporades);
			this->pnlEsborrarPartit->Controls->Add(this->lblEPJornada);
			this->pnlEsborrarPartit->Controls->Add(this->cmbEPJornades);
			this->pnlEsborrarPartit->Controls->Add(this->lblEPPartit);
			this->pnlEsborrarPartit->Controls->Add(this->cmbEPPartits);
			this->pnlEsborrarPartit->Controls->Add(this->btnEPEsborrarFinal);

			this->lblEPTitle->Text = L"Esborrar Partit - Selecció";
			this->lblEPTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
			this->lblEPTitle->AutoSize = true;

			this->btnEPTornar->Text = L"Tornar";
			this->btnEPTornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEPTornar_Click);

			// Config Temporades
			this->lblEPTemporada->Text = L"Tria una Temporada:";
			this->lblEPTemporada->AutoSize = true;
			this->cmbEPTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEPTemporades->Size = System::Drawing::Size(450, 24);
			this->cmbEPTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cmbEPTemporades_SelectedIndexChanged);

			// Config Jornades
			this->lblEPJornada->Text = L"Tria una Jornada:";
			this->lblEPJornada->AutoSize = true;
			this->cmbEPJornades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEPJornades->Size = System::Drawing::Size(450, 24);
			this->cmbEPJornades->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cmbEPJornades_SelectedIndexChanged);

			// Config Partits
			this->lblEPPartit->Text = L"Tria el Partit a esborrar:";
			this->lblEPPartit->AutoSize = true; 
			this->cmbEPPartits->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEPPartits->Size = System::Drawing::Size(550, 24);

			this->btnEPEsborrarFinal->Text = L"Esborrar Partit Seleccionat";
			this->btnEPEsborrarFinal->BackColor = System::Drawing::Color::Red;
			this->btnEPEsborrarFinal->ForeColor = System::Drawing::Color::White;
			this->btnEPEsborrarFinal->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold);
			this->btnEPEsborrarFinal->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEPEsborrarFinal_Click);

			this->Controls->Add(this->pnlEsborrarPartit);

			this->btnEstLliga = gcnew System::Windows::Forms::Button();
			this->btnEstLliga->Text = L"Estadístiques Lliga";
			this->btnEstLliga->Size = System::Drawing::Size(220, 60);
			this->btnEstLliga->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnEstLliga->Cursor = System::Windows::Forms::Cursors::Hand;

			// Posición inicial fija
			this->btnEstLliga->Location = System::Drawing::Point(190, 230);

			this->btnEstLliga->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstLliga_Click);
			this->pnlEstadistiques->Controls->Add(this->btnEstLliga);

			// 2. Panel de Detalle (el que se abre al pulsar el botón)
			this->pnlEstadistiquesLligaDetail = gcnew System::Windows::Forms::Panel();
			this->pnlEstadistiquesLligaDetail->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlEstadistiquesLligaDetail->Visible = false;
			this->pnlEstadistiquesLligaDetail->BackColor = System::Drawing::Color::White;

			// 3. Elementos de Búsqueda (Estudiante)
			this->lblEstLligaBuscar = gcnew System::Windows::Forms::Label();
			this->lblEstLligaBuscar->Text = L"Escriu el nom de la Lliga:";
			this->lblEstLligaBuscar->Location = System::Drawing::Point(50, 40);
			this->lblEstLligaBuscar->AutoSize = true;

			this->txtEstLligaBuscar = gcnew System::Windows::Forms::TextBox();
			this->txtEstLligaBuscar->Location = System::Drawing::Point(200, 38);
			this->txtEstLligaBuscar->Size = System::Drawing::Size(200, 20);

			this->btnEstLligaExecutarCerca = gcnew System::Windows::Forms::Button();
			this->btnEstLligaExecutarCerca->Text = L"Cercar";
			this->btnEstLligaExecutarCerca->Location = System::Drawing::Point(410, 36);
			this->btnEstLligaExecutarCerca->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstLligaExecutarCerca_Click);

			// 4. Temporada y Tabla
			this->lblEstLligaTemporada = gcnew System::Windows::Forms::Label();
			this->lblEstLligaTemporada->Text = L"Temporada:";
			this->lblEstLligaTemporada->Location = System::Drawing::Point(50, 80);
			this->lblEstLligaTemporada->Visible = false;

			this->cmbEstLligaTemporades = gcnew System::Windows::Forms::ComboBox();
			this->cmbEstLligaTemporades->Location = System::Drawing::Point(150, 78);
			this->cmbEstLligaTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEstLligaTemporades->Visible = false;

			this->dgvEstLligaClassificacio = gcnew System::Windows::Forms::DataGridView();
			this->dgvEstLligaClassificacio->Location = System::Drawing::Point(50, 120);
			this->dgvEstLligaClassificacio->Size = System::Drawing::Size(700, 350);
			this->dgvEstLligaClassificacio->Visible = false;
			this->dgvEstLligaClassificacio->AllowUserToAddRows = false;
			this->dgvEstLligaClassificacio->ReadOnly = true;
			this->dgvEstLligaClassificacio->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

			// 5. Botón Volver
			this->btnEstLligaTornar = gcnew System::Windows::Forms::Button();
			this->btnEstLligaTornar->Text = L"<- Tornar";
			this->btnEstLligaTornar->Location = System::Drawing::Point(50, 490);
			this->btnEstLligaTornar->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnEstLligaTornar_Click);

			// Agregar todo al panel de detalle
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->lblEstLligaBuscar);
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->txtEstLligaBuscar);
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->btnEstLligaExecutarCerca);
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->lblEstLligaTemporada);
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->cmbEstLligaTemporades);
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->dgvEstLligaClassificacio);
			this->pnlEstadistiquesLligaDetail->Controls->Add(this->btnEstLligaTornar);

			// Agregar el panel de detalle al formulario principal
			this->Controls->Add(this->pnlEstadistiquesLligaDetail);
			this->pnlEstadistiquesLligaDetail->BringToFront();
			String^ logoPath = L"imatges\\logo.png";
			if (!System::IO::File::Exists(logoPath)) {
				logoPath = L"..\\..\\imatges\\logo.png";
			}
			if (System::IO::File::Exists(logoPath)) {
				this->picLogoInici->ImageLocation = logoPath;
				this->picLogoLogin->ImageLocation = logoPath;
				this->picLogoRegister->ImageLocation = logoPath;
				this->picLogoMain->ImageLocation = logoPath;
				this->picLogoGL->ImageLocation = logoPath;
				this->picLogoEst->ImageLocation = logoPath;
			}

			// NOU: Inicialització del panell d'edició de partits
			this->pnlEditarPartit = gcnew System::Windows::Forms::Panel();
			this->lblEditarPartitTitle = gcnew System::Windows::Forms::Label();
			this->cmbPartitsAEditar = gcnew System::Windows::Forms::ComboBox();
			this->lblPartitsAEditar = gcnew System::Windows::Forms::Label();
			this->dgvEstadistiquesJugadors = gcnew System::Windows::Forms::DataGridView();
			this->btnGuardarEstadistiques = gcnew System::Windows::Forms::Button();
			this->btnTornarEditarPartit = gcnew System::Windows::Forms::Button();
			this->lblResultatLocal = gcnew System::Windows::Forms::Label();
			this->txtResultatLocal = gcnew System::Windows::Forms::TextBox();
			this->lblResultatVisitant = gcnew System::Windows::Forms::Label();
			this->txtResultatVisitant = gcnew System::Windows::Forms::TextBox();
			this->lblEstatPartit = gcnew System::Windows::Forms::Label();
			this->cmbEstatPartit = gcnew System::Windows::Forms::ComboBox();
			this->lblDataPartit = gcnew System::Windows::Forms::Label();
			this->dtpDataPartit = gcnew System::Windows::Forms::DateTimePicker();
			this->partitPerId = gcnew System::Collections::Generic::Dictionary<String^, String^>();

			this->pnlEditarPartit->SuspendLayout();
			this->SuspendLayout();

			// Configuració del panell
			this->pnlEditarPartit->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlEditarPartit->Visible = false;
			this->pnlEditarPartit->Controls->Add(this->lblEditarPartitTitle);
			this->pnlEditarPartit->Controls->Add(this->lblPartitsAEditar);
			this->pnlEditarPartit->Controls->Add(this->cmbPartitsAEditar);
			this->pnlEditarPartit->Controls->Add(this->dgvEstadistiquesJugadors);
			this->pnlEditarPartit->Controls->Add(this->btnGuardarEstadistiques);
			this->pnlEditarPartit->Controls->Add(this->btnTornarEditarPartit);
			this->pnlEditarPartit->Controls->Add(this->lblResultatLocal);
			this->pnlEditarPartit->Controls->Add(this->txtResultatLocal);
			this->pnlEditarPartit->Controls->Add(this->lblResultatVisitant);
			this->pnlEditarPartit->Controls->Add(this->txtResultatVisitant);
			this->pnlEditarPartit->Controls->Add(this->lblEstatPartit);
			this->pnlEditarPartit->Controls->Add(this->cmbEstatPartit);
			this->pnlEditarPartit->Controls->Add(this->lblDataPartit);
			this->pnlEditarPartit->Controls->Add(this->dtpDataPartit);

			// Títol
			this->lblEditarPartitTitle->Text = L"Editar Partit i Estadístiques";
			this->lblEditarPartitTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold);
			this->lblEditarPartitTitle->AutoSize = true;

			// Label i ComboBox per seleccionar partit
			this->lblPartitsAEditar->Text = L"Selecciona un partit:";
			this->lblPartitsAEditar->AutoSize = true;
			this->cmbPartitsAEditar->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbPartitsAEditar->Size = System::Drawing::Size(400, 21);
			this->cmbPartitsAEditar->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cmbPartitsAEditar_SelectedIndexChanged);

			// Resultats i Estat
			this->lblResultatLocal->Text = L"Gols Local:";
			this->txtResultatLocal->Size = System::Drawing::Size(50, 20);
			this->lblResultatVisitant->Text = L"Gols Visitant:";
			this->txtResultatVisitant->Size = System::Drawing::Size(50, 20);
			this->lblEstatPartit->Text = L"Estat:";
			this->cmbEstatPartit->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEstatPartit->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Pendent", L"En joc", L"Finalitzat", L"Aplaçat", L"Cancel·lat" });
			this->cmbEstatPartit->SelectedIndexChanged += gcnew System::EventHandler(this, &PlayCampusLegacyForm::cmbEstatPartit_SelectedIndexChanged);

			// Data partit (per si s'aplaça)
			this->lblDataPartit->Text = L"Nova data:";
			this->dtpDataPartit->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtpDataPartit->CustomFormat = L"yyyy-MM-dd HH:mm:ss";
			this->dtpDataPartit->Visible = false;
			this->lblDataPartit->Visible = false;

			// DataGridView per a les estadístiques
			this->dgvEstadistiquesJugadors->AllowUserToAddRows = false;
			this->dgvEstadistiquesJugadors->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;

			// Botons
			this->btnGuardarEstadistiques->Text = L"Guardar Canvis";
			this->btnGuardarEstadistiques->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnGuardarEstadistiques_Click);
			this->btnTornarEditarPartit->Text = L"Tornar";
			this->btnTornarEditarPartit->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnTornarEditarPartit_Click);

			this->Controls->Add(this->pnlEditarPartit);
			this->pnlEditarPartit->ResumeLayout(false);
			this->pnlEditarPartit->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void Form1_Resize(System::Object^ sender, System::EventArgs^ e) {
		// Comprobar que no estamos procesando el resize demasiado pronto u ocultos
			if (this->ClientSize.Width == 0 || this->ClientSize.Height == 0) return;

		// Prevenir problemas si el Resize se dispara antes de terminar InitializeComponent
		if (this->lblEPTitle == nullptr || this->btnEPEsborrarFinal == nullptr) return;

		int cw = this->ClientSize.Width;
		int ch = this->ClientSize.Height;
		int centerX = cw / 2;
		int centerY = ch / 2;

		// 1. DISSENY DEL MENÚ PRINCIPAL (Botó del Capità)
		int startBtnX = (this->ClientSize.Width - 800) / 2; // Punt de partida centrat

		if (this->btnGestionarConvocatoria != nullptr && pnlMain->Visible) {
			// El posem al costat dels altres botons del capità. Ajusta el '600' i '80' si se superposen.
			this->btnGestionarConvocatoria->Location = System::Drawing::Point(startBtnX + 600, 80);
			this->btnGestionarConvocatoria->Size = System::Drawing::Size(180, 40);
		}

		// 2. DISSENY DEL PANELL DE CONVOCATÒRIES
		if (this->pnlConvocatoria != nullptr && this->pnlConvocatoria->Visible) {
			// Ocupa gairebé tota la pantalla
			this->pnlConvocatoria->Location = System::Drawing::Point(0, 140);
			this->pnlConvocatoria->Size = System::Drawing::Size(this->ClientSize.Width, this->ClientSize.Height - 140);
			this->pnlConvocatoria->BackColor = System::Drawing::Color::WhiteSmoke;

			// Botó Tornar
			if (this->btnTornarConvocatoria != nullptr) {
				this->btnTornarConvocatoria->Location = System::Drawing::Point(20, 10);
				this->btnTornarConvocatoria->Size = System::Drawing::Size(120, 30);
			}

			// Desplegable de partits
			if (this->cbPartitsConvocatoria != nullptr) {
				this->cbPartitsConvocatoria->Location = System::Drawing::Point(20, 50);
				this->cbPartitsConvocatoria->Size = System::Drawing::Size(400, 30);
			}

			// Taula de jugadors
			if (this->dgvConvocatoria != nullptr) {
				this->dgvConvocatoria->Location = System::Drawing::Point(20, 90);
				this->dgvConvocatoria->Size = System::Drawing::Size(this->pnlConvocatoria->Width - 40, this->pnlConvocatoria->Height - 120);
				this->dgvConvocatoria->BackgroundColor = System::Drawing::Color::White;
			}
		}

		// 3. DISSENY DEL CARTELL DEL JUGADOR (Si està actiu)
		if (this->pnlAvisJugador != nullptr && pnlMain->Controls->Contains(pnlAvisJugador)) {
			// El centrem just al mig del panell principal
			this->pnlAvisJugador->Location = System::Drawing::Point(
				(pnlMain->Width - pnlAvisJugador->Width) / 2,
				(pnlMain->Height - pnlAvisJugador->Height) / 2
			);
		}

		// --- PANELS DE LOGIN/REGISTRE ---
		this->picLogoInici->Location = System::Drawing::Point(centerX - this->picLogoInici->Width / 2, centerY - 250);
		this->btnShowLogin->Location = System::Drawing::Point(centerX - this->btnShowLogin->Width / 2, centerY - 50);
		this->btnShowRegister->Location = System::Drawing::Point(centerX - this->btnShowRegister->Width / 2, centerY + 10);

		int loginStartX = centerX - 125;
		int loginStartY = centerY - 75;
		this->picLogoLogin->Location = System::Drawing::Point(centerX - this->picLogoLogin->Width / 2, loginStartY - 160);
		this->lblLoginTitle->Location = System::Drawing::Point(loginStartX + 90, loginStartY);
		this->lblLoginUsuari->Location = System::Drawing::Point(loginStartX, loginStartY + 30);
		this->txtLoginCorreu->Location = System::Drawing::Point(loginStartX + 100, loginStartY + 30);
		this->lblLoginPass->Location = System::Drawing::Point(loginStartX, loginStartY + 70);
		this->txtLoginPass->Location = System::Drawing::Point(loginStartX + 100, loginStartY + 70);
		this->btnLoginAct->Location = System::Drawing::Point(loginStartX, loginStartY + 110);
		this->btnLoginBack->Location = System::Drawing::Point(loginStartX + 100, loginStartY + 110);

		int rgStartX = centerX - 125;
		int rgStartY = centerY - 95;
		this->picLogoRegister->Location = System::Drawing::Point(centerX - this->picLogoRegister->Width / 2, rgStartY - 160);
		this->lblRegTitle->Location = System::Drawing::Point(rgStartX + 90, rgStartY);
		this->lblRegNom->Location = System::Drawing::Point(rgStartX, rgStartY + 30);
		this->txtRegNom->Location = System::Drawing::Point(rgStartX + 100, rgStartY + 30);
		this->lblRegCorreu->Location = System::Drawing::Point(rgStartX, rgStartY + 60);
		this->txtRegCorreu->Location = System::Drawing::Point(rgStartX + 100, rgStartY + 60);
		this->lblRegPass->Location = System::Drawing::Point(rgStartX, rgStartY + 90);
		this->txtRegPass->Location = System::Drawing::Point(rgStartX + 100, rgStartY + 90);
		this->lblRegTipus->Location = System::Drawing::Point(rgStartX, rgStartY + 120);
		this->cmbRegTipus->Location = System::Drawing::Point(rgStartX + 100, rgStartY + 120);
		this->lblRegTelefon->Location = System::Drawing::Point(rgStartX, rgStartY + 150);
		this->txtRegTelefon->Location = System::Drawing::Point(rgStartX + 100, rgStartY + 150);
		this->btnRegAct->Location = System::Drawing::Point(rgStartX, rgStartY + 190);
		this->btnRegBack->Location = System::Drawing::Point(rgStartX + 100, rgStartY + 190);

		// --- PANEL MAIN ---
		this->lblMainTitle->Location = System::Drawing::Point(centerX - this->lblMainTitle->Width / 2, 20);

		this->picLogoMain->Location = System::Drawing::Point(cw - this->picLogoMain->Width - 30, 20);
		this->btnLogoutMainMenu->Location = System::Drawing::Point(20, 20);
		this->btnLogoutMainMenu->BringToFront();

		int totalBtnWidth = 130 * 5 + 20 * 4;
		this->btnProgPartits->Location = System::Drawing::Point(startBtnX, 80);
		this->btnEstatLligues->Location = System::Drawing::Point(startBtnX + 150, 80);
		this->btnEstadistiques->Location = System::Drawing::Point(startBtnX + 300, 80);
		this->btnConsultar->Location = System::Drawing::Point(startBtnX + 450, 80);

		this->btnCrearLligaMainMenu->Location = System::Drawing::Point(startBtnX + 600, 80);
		this->btnEnregistrarEquip->Location = System::Drawing::Point(startBtnX - 150, 80); // Posicionament a l'esquerra
		this->btnUnirEquipLliga->Location = System::Drawing::Point(startBtnX - 300, 80);

		int picY = 140;
		int picBottomMargin = 160;
		int picH = System::Math::Max(10, ch - picY - picBottomMargin);
		this->picImatge->Location = System::Drawing::Point(50, picY);
		this->picImatge->Size = System::Drawing::Size(cw - 100, picH);

		int noticiesY = this->picImatge->Bottom + 20;
		this->lblNoticies->Location = System::Drawing::Point(50, noticiesY);
		this->lstNoticies->Location = System::Drawing::Point(50, noticiesY + 25);
		this->lstNoticies->Size = System::Drawing::Size(cw - 100, ch - (noticiesY + 25) - 20);

		// --- PANEL CONSULTAR ---
		this->lblConsultarTitle->Location = System::Drawing::Point(centerX - this->lblConsultarTitle->Width / 2, 30);
		this->btnTornarConsultar->Location = System::Drawing::Point(30, 30);
		this->lblNomLliga->Location = System::Drawing::Point(centerX - 170, centerY - 30);
		this->txtNomLliga->Location = System::Drawing::Point(centerX - 30, centerY - 30);
		this->btnComprovarLliga->Location = System::Drawing::Point(centerX - 30, centerY + 15);

		// --- PANEL CREAR LLIGA ---
		this->lblCLTitle->Location = System::Drawing::Point(centerX - this->lblCLTitle->Width / 2, 30);
		this->btnCLTornar->Location = System::Drawing::Point(30, 30);
		
		int clStartX = centerX - 125;
		int clStartY = centerY - 50;
		this->lblCLNom->Location = System::Drawing::Point(clStartX, clStartY);
		this->txtCLNom->Location = System::Drawing::Point(clStartX + 120, clStartY);
		this->lblCLPass->Location = System::Drawing::Point(clStartX, clStartY + 40);
		this->txtCLPass->Location = System::Drawing::Point(clStartX + 120, clStartY + 40);
		this->lblCLEsport->Location = System::Drawing::Point(clStartX, clStartY + 80);
		this->cmbCLEsport->Location = System::Drawing::Point(clStartX + 120, clStartY + 80);
		this->btnCLGuarda->Location = System::Drawing::Point(centerX - 50, clStartY + 130);

		// --- PANEL ESTADISTIQUES ---
		this->lblEstTitle->Location = System::Drawing::Point(centerX - this->lblEstTitle->Width / 2, 40);
		this->btnEstTornar->Location = System::Drawing::Point(30, 30);

		int estStartY = centerY - 20;
		this->btnEstEquips->Location = System::Drawing::Point(centerX - (this->btnEstEquips->Width / 2), estStartY);
		this->picLogoEst->Location = System::Drawing::Point(centerX - (this->picLogoEst->Width / 2), estStartY - this->picLogoEst->Height - 40);

		// --- PANEL GESTIONAR LLIGA ---
		this->lblGLTitle->Location = System::Drawing::Point(centerX - this->lblGLTitle->Width / 2, 40);
		this->btnGLTornar->Location = System::Drawing::Point(30, 30);

		int glStartY = centerY - 20;
		int glSpacingX = 40;
		int glSpacingY = 40;
		int btnGLW = this->btnGLAfegirPartit->Width;
		int btnGLH = this->btnGLAfegirPartit->Height;

		this->btnGLAfegirPartit->Location = System::Drawing::Point(centerX - btnGLW - (glSpacingX / 2), glStartY);
		this->btnGLEditarPartit->Location = System::Drawing::Point(centerX + (glSpacingX / 2), glStartY);
		this->btnGLMostrarEquips->Location = System::Drawing::Point(centerX - btnGLW - (glSpacingX / 2), glStartY + btnGLH + glSpacingY);
		this->btnGLEsborrarEquip->Location = System::Drawing::Point(centerX + (glSpacingX / 2), glStartY + btnGLH + glSpacingY);
		this->btnGLCrearJornada->Location = System::Drawing::Point(centerX - btnGLW - (glSpacingX / 2), glStartY + (btnGLH + glSpacingY) * 2);
		this->btnGLCrearTemporada->Location = System::Drawing::Point(centerX + (glSpacingX / 2), glStartY + (btnGLH + glSpacingY) * 2);
		this->btnGLEsborrarPartit->Location = System::Drawing::Point(centerX - btnGLW - (glSpacingX / 2), glStartY + (btnGLH + glSpacingY) * 3);
		if (this->btnGLRetirarTemporada != nullptr) {
			this->btnGLRetirarTemporada->Location = System::Drawing::Point(centerX + (glSpacingX / 2), glStartY + (btnGLH + glSpacingY) * 3);
		}

		this->picLogoGL->Location = System::Drawing::Point(centerX - (this->picLogoGL->Width / 2), glStartY - this->picLogoGL->Height - 40);

		// --- PANEL CREAR PARTIT ---
		this->lblCPTitle->Location = System::Drawing::Point(centerX - this->lblCPTitle->Width / 2, 10); // Más arriba

		int cpStartX = centerX - 160;
		int cpStartY = centerY - 150; // Empezamos más arriba

		// 1. Liga
		this->lblCPNomLliga->Location = System::Drawing::Point(cpStartX, cpStartY);
		this->txtCPNomLliga->Location = System::Drawing::Point(cpStartX + 120, cpStartY);
		// Botón de validación a un lado
		this->btnCPValidarLliga->Location = System::Drawing::Point(cpStartX + 230, cpStartY - 3);

		// 2. Temporada
		this->lblCPTemporada->Location = System::Drawing::Point(cpStartX, cpStartY + 40);
		this->cmbCPTemporada->Location = System::Drawing::Point(cpStartX + 120, cpStartY + 40);

		// 3. Jornada
		this->lblCPJornada->Location = System::Drawing::Point(cpStartX, cpStartY + 80);
		this->cmbCPJornada->Location = System::Drawing::Point(cpStartX + 120, cpStartY + 80);

		// 4. Data
		this->lblCPData->Location = System::Drawing::Point(cpStartX, cpStartY + 120);
		this->dtpCPData->Location = System::Drawing::Point(cpStartX + 120, cpStartY + 120);

		// 5. Ubicació
		this->lblCPUbicacio->Location = System::Drawing::Point(cpStartX, cpStartY + 160);
		this->txtCPUbicacio->Location = System::Drawing::Point(cpStartX + 120, cpStartY + 160);

		// 6. Equipos
		this->lblCPEquipLocal->Location = System::Drawing::Point(cpStartX, cpStartY + 200);
		this->cmbCPEquipLocal->Location = System::Drawing::Point(cpStartX + 120, cpStartY + 200);

		this->lblCPEquipVisitant->Location = System::Drawing::Point(cpStartX, cpStartY + 240);
		this->cmbCPEquipVisitant->Location = System::Drawing::Point(cpStartX + 120, cpStartY + 240);

		// 7. Botones confirmación
		this->btnCPConfirmar->Location = System::Drawing::Point(cpStartX + 20, cpStartY + 290);
		this->btnCPCancellar->Location = System::Drawing::Point(cpStartX + 140, cpStartY + 290);

		// --- PANEL GESTIONAR EQUIP ---
		this->lblGETitle->Location = System::Drawing::Point(centerX - this->lblGETitle->Width / 2, 40);
		this->btnGETornar->Location = System::Drawing::Point(30, 30);

		int geDgvY = 80;
		this->dgvPlantilla->Location = System::Drawing::Point(centerX - (this->dgvPlantilla->Width / 2), geDgvY);

		int geStartY = geDgvY + this->dgvPlantilla->Height + 20;
		int btnGEW = this->btnGEEsborrarEquip->Width;
		this->btnGEEsborrarEquip->Location = System::Drawing::Point(centerX - (btnGEW / 2), geStartY);
		this->btnGEAfegirJugador->Location = System::Drawing::Point(centerX - (btnGEW / 2), geStartY + 70);
		this->btnGEEliminarJugador->Location = System::Drawing::Point(centerX - (btnGEW / 2), geStartY + 140);
		this->btnGEAssignarJugador->Location = System::Drawing::Point(centerX - (btnGEW / 2), geStartY + 210);

		// --- PANEL ESBORRAR PARTIT 
		this->lblEPTitle->Location = System::Drawing::Point(centerX - this->lblEPTitle->Width / 2, 30);
		this->btnEPTornar->Location = System::Drawing::Point(30, 30);

		int epStartX = centerX - 250;
		int epStartY = centerY - 100;

		this->lblEPTemporada->Location = System::Drawing::Point(epStartX, epStartY);
		this->cmbEPTemporades->Location = System::Drawing::Point(epStartX + 150, epStartY - 3);

		this->lblEPJornada->Location = System::Drawing::Point(epStartX, epStartY + 50);
		this->cmbEPJornades->Location = System::Drawing::Point(epStartX + 150, epStartY + 47);

		this->lblEPPartit->Location = System::Drawing::Point(epStartX, epStartY + 100);
		this->cmbEPPartits->Location = System::Drawing::Point(epStartX + 150, epStartY + 97);

		this->btnEPEsborrarFinal->Location = System::Drawing::Point(centerX - 100, epStartY + 180);
		this->btnEPEsborrarFinal->Size = System::Drawing::Size(200, 40);

		// --- PANEL AFEGIR JUGADOR ---
		this->lblAJTitle->Location = System::Drawing::Point(centerX - this->lblAJTitle->Width / 2, 30);
		this->btnAJCancellar->Location = System::Drawing::Point(30, 30);

		int ajStartX = centerX - 125;
		int ajStartY = centerY - 50;
		this->lblAJCorreu->Location = System::Drawing::Point(ajStartX, ajStartY);
		this->txtAJCorreu->Location = System::Drawing::Point(ajStartX + 140, ajStartY);
		this->lblAJDorsal->Location = System::Drawing::Point(ajStartX, ajStartY + 40);
		this->txtAJDorsal->Location = System::Drawing::Point(ajStartX + 140, ajStartY + 40);
		this->lblAJPosicio->Location = System::Drawing::Point(ajStartX, ajStartY + 80);
		this->txtAJPosicio->Location = System::Drawing::Point(ajStartX + 140, ajStartY + 80);
		this->btnAJConfirmar->Location = System::Drawing::Point(ajStartX + 20, ajStartY + 130);
		this->btnAJCancellar->Location = System::Drawing::Point(ajStartX + 150, ajStartY + 130);

		// --- PANEL ENREGISTRAR EQUIP ---
		this->lblEETitle->Location = System::Drawing::Point(centerX - this->lblEETitle->Width / 2, 30);
		this->btnEETornar->Location = System::Drawing::Point(30, 30);

		int eeStartX = centerX - 125;
		int eeStartY = centerY - 50;
		this->lblEENom->Location = System::Drawing::Point(eeStartX, eeStartY);
		this->txtEENom->Location = System::Drawing::Point(eeStartX + 120, eeStartY);
		this->lblEEData->Location = System::Drawing::Point(eeStartX, eeStartY + 40);
		this->dtpEEData->Location = System::Drawing::Point(eeStartX + 120, eeStartY + 40);
		this->lblEEEscollirEsport->Location = System::Drawing::Point(eeStartX, eeStartY + 80);
		this->cmbEEEscollirEsport->Location = System::Drawing::Point(eeStartX + 120, eeStartY + 80);
		this->btnEEEnregistrar->Location = System::Drawing::Point(centerX - 50, eeStartY + 130);

		// --- PANEL UNIR EQUIP LLIGA ---
		this->lblUELTitle->Location = System::Drawing::Point(centerX - this->lblUELTitle->Width / 2, 30);
		this->btnUELTornar->Location = System::Drawing::Point(30, 30);

		int uelStartX = centerX - 125;
		int uelStartY = centerY - 50;
		this->lblUELNom->Location = System::Drawing::Point(uelStartX, uelStartY);
		this->txtUELNom->Location = System::Drawing::Point(uelStartX + 120, uelStartY);
		this->btnUELComprovar->Location = System::Drawing::Point(uelStartX + 120, uelStartY + 30);
		this->lblUELPass->Location = System::Drawing::Point(uelStartX, uelStartY + 70);
		this->txtUELPass->Location = System::Drawing::Point(uelStartX + 120, uelStartY + 70);
		this->btnUELUnir->Location = System::Drawing::Point(centerX - 50, uelStartY + 120);

		// --- PANEL CREAR TEMPORADA ---
		this->lblCTTitle->Location = System::Drawing::Point(centerX - this->lblCTTitle->Width / 2, 30);
		int ctStartY = centerY - 70; // <-- He pujat el panel 20px per fer espai (-50 a -70)
		int ctStartX = centerX - 125;

		// --- AFEGIR EL POSICIONAMENT DEL NOM LLIGA ---
		this->lblCTNomLliga->Location = System::Drawing::Point(ctStartX, ctStartY);
		this->txtCTNomLliga->Location = System::Drawing::Point(ctStartX + 120, ctStartY);

		this->lblCTDataInici->Location = System::Drawing::Point(ctStartX, ctStartY + 40);
		this->lblCTDataInici->Size = System::Drawing::Size(100, 20);
		this->dtpCTDataInici->Location = System::Drawing::Point(ctStartX + 120, ctStartY + 40);

		this->lblCTDataFi->Location = System::Drawing::Point(ctStartX, ctStartY + 80);
		this->lblCTDataFi->Size = System::Drawing::Size(100, 20);
		this->dtpCTDataFi->Location = System::Drawing::Point(ctStartX + 120, ctStartY + 80);

		this->btnCTConfirmar->Location = System::Drawing::Point(ctStartX + 20, ctStartY + 140);
		this->btnCTConfirmar->Size = System::Drawing::Size(100, 30);
		this->btnCTCancellar->Location = System::Drawing::Point(ctStartX + 140, ctStartY + 140);
		this->btnCTCancellar->Size = System::Drawing::Size(100, 30);

		// --- PANEL CREAR JORNADA ---
		this->lblCJTitle->Location = System::Drawing::Point(centerX - this->lblCJTitle->Width / 2, 30);
		int cjStartY = centerY - 100;
		int cjStartX = centerX - 150;

		this->lblCJNomLliga->Location = System::Drawing::Point(cjStartX, cjStartY);
		this->lblCJNomLliga->Size = System::Drawing::Size(100, 20);
		this->txtCJNomLliga->Location = System::Drawing::Point(cjStartX + 120, cjStartY);
		this->txtCJNomLliga->Size = System::Drawing::Size(150, 20);

		this->btnCJBuscarTemporades->Location = System::Drawing::Point(cjStartX + 290, cjStartY);
		this->btnCJBuscarTemporades->Size = System::Drawing::Size(130, 25);

		this->lblCJTemporada->Location = System::Drawing::Point(cjStartX, cjStartY + 40);
		this->lblCJTemporada->Size = System::Drawing::Size(100, 20);
		this->cmbCJTemporada->Location = System::Drawing::Point(cjStartX + 120, cjStartY + 40);
		this->cmbCJTemporada->Size = System::Drawing::Size(300, 20);

		this->lblCJNumero->Location = System::Drawing::Point(cjStartX, cjStartY + 80);
		this->lblCJNumero->Size = System::Drawing::Size(100, 20);
		this->txtCJNumero->Location = System::Drawing::Point(cjStartX + 120, cjStartY + 80);


		this->lblCJDataInici->Location = System::Drawing::Point(cjStartX, cjStartY + 120);
		this->lblCJDataInici->Size = System::Drawing::Size(100, 20);
		this->dtpCJDataInici->Location = System::Drawing::Point(cjStartX + 120, cjStartY + 120);

		this->lblCJDataFi->Location = System::Drawing::Point(cjStartX, cjStartY + 160);
		this->lblCJDataFi->Size = System::Drawing::Size(100, 20);
		this->dtpCJDataFi->Location = System::Drawing::Point(cjStartX + 120, cjStartY + 160);

		this->btnCJConfirmar->Location = System::Drawing::Point(cjStartX + 50, cjStartY + 220);
		this->btnCJConfirmar->Size = System::Drawing::Size(100, 30);
		this->btnCJCancellar->Location = System::Drawing::Point(cjStartX + 170, cjStartY + 220);
		this->btnCJCancellar->Size = System::Drawing::Size(100, 30);

		if (this->btnEstEquips != nullptr) {
			// Centramos el botón de Equipos (un poco más arriba del centro de la pantalla)
			this->btnEstEquips->Location = System::Drawing::Point(centerX - (this->btnEstEquips->Width / 2), centerY - 60);
		}

		if (this->btnEstLliga != nullptr && this->btnEstEquips != nullptr) {
			// Ponemos el botón de la Liga exactamente debajo del de Equipos
			this->btnEstLliga->Location = System::Drawing::Point(this->btnEstEquips->Location.X, this->btnEstEquips->Location.Y + this->btnEstEquips->Height + 20);
		}

		// NOU: Posicionament del panell d'edició de partits
		if (this->pnlEditarPartit->Visible) {
			int startX = 50;
			int startY = 30;
			this->btnTornarEditarPartit->Location = System::Drawing::Point(startX, startY);
			this->lblEditarPartitTitle->Location = System::Drawing::Point(centerX - this->lblEditarPartitTitle->Width / 2, startY);

			startY += 60;
			this->lblPartitsAEditar->Location = System::Drawing::Point(startX, startY);
			this->cmbPartitsAEditar->Location = System::Drawing::Point(startX + 120, startY);

           startY += 40;
          this->lblResultatLocal->Location = System::Drawing::Point(startX, startY);
			this->txtResultatLocal->Location = System::Drawing::Point(startX + 120, startY);
			this->txtResultatLocal->Size = System::Drawing::Size(60, this->txtResultatLocal->Height);
			this->lblResultatVisitant->Location = System::Drawing::Point(startX + 220, startY);
			this->txtResultatVisitant->Location = System::Drawing::Point(startX + 360, startY);
			this->txtResultatVisitant->Size = System::Drawing::Size(60, this->txtResultatVisitant->Height);

			startY += 40;
            this->lblEstatPartit->Location = System::Drawing::Point(startX, startY);
			this->cmbEstatPartit->Location = System::Drawing::Point(startX + 120, startY);
			this->cmbEstatPartit->Size = System::Drawing::Size(220, this->cmbEstatPartit->Height);

           this->lblDataPartit->Location = System::Drawing::Point(startX + 380, startY);
			this->dtpDataPartit->Location = System::Drawing::Point(startX + 490, startY);
			this->dtpDataPartit->Size = System::Drawing::Size(200, this->dtpDataPartit->Height);

			startY += 40;
			this->dgvEstadistiquesJugadors->Location = System::Drawing::Point(startX, startY);
			this->dgvEstadistiquesJugadors->Size = System::Drawing::Size(cw - 100, ch - startY - 100);

			this->btnGuardarEstadistiques->Location = System::Drawing::Point(centerX - this->btnGuardarEstadistiques->Width / 2, ch - 70);
		}

	}

	private: System::Void btnUnirEquipLligaAct_Click(System::Object^ sender, System::EventArgs^ e) {
		if (btnUnirEquipLliga->Text == L"Abandonar Lliga") {
			MessageBox::Show(L"Funcionalitat en desenvolupament.");
			return;
		}

		pnlMain->Visible = false;
		pnlUnirEquipLliga->Visible = true;
		
		txtUELNom->Text = L"";
		txtUELPass->Text = L"";
		txtUELNom->Enabled = true;
		btnUELComprovar->Visible = true;
		lblUELPass->Visible = false;
		txtUELPass->Visible = false;
		btnUELUnir->Visible = false;
	}

	private: System::Void btnUELTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlUnirEquipLliga->Visible = false;
		pnlMain->Visible = true;
	}

	private: System::Void btnUELComprovar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtUELNom->Text;
		if (String::IsNullOrWhiteSpace(nomLliga)) { 
			MessageBox::Show(L"Introdueix nom de la lliga", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return; 
		}

		try {
			Playcampus::Domini::CtrlUnirEquipLliga^ ctrl = gcnew Playcampus::Domini::CtrlUnirEquipLliga();
			String^ lligaTroba = ctrl->ComprovarSiLligaExisteix(nomLliga);
			
			if (lligaTroba != nullptr) {
				txtUELNom->Enabled = false;
				btnUELComprovar->Visible = false;
				
				lblUELPass->Visible = true;
				txtUELPass->Visible = true;
				btnUELUnir->Visible = true;
			}
			else {
				MessageBox::Show(L"La lliga no existeix, si us plau, introdueix una d'existent.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				txtUELNom->Text = L""; 
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error de BD: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnUELUnir_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtUELNom->Text;
		String^ passLliga = txtUELPass->Text;

		if(String::IsNullOrWhiteSpace(passLliga)) return;

		try {
			Playcampus::Domini::CtrlUnirEquipLliga^ ctrl = gcnew Playcampus::Domini::CtrlUnirEquipLliga();
			
			if (ctrl->ValidarContrasenyaLliga(nomLliga, passLliga)) {
				String^ missatgeExit = ctrl->VincularEquip(currentUsuariCorreu, nomLliga);
				MessageBox::Show(missatgeExit, L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);

				btnUnirEquipLliga->Text = L"Abandonar Lliga";

				pnlUnirEquipLliga->Visible = false;
				pnlMain->Visible = true;
			}
			else {
				MessageBox::Show(L"Contrasenya incorrecta. Torna a intentar-ho.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				txtUELPass->Text = L""; 
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"No s'ha pogut vincular: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			txtUELNom->Enabled = true;
			btnUELComprovar->Visible = true;
			lblUELPass->Visible = false;
			txtUELPass->Visible = false;
			btnUELUnir->Visible = false;
			txtUELNom->Text = L"";
			txtUELPass->Text = L"";
		}
	}

	private: System::Void btnShowLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlInici->Visible = false;
		pnlLogin->Visible = true;
	}

	private: System::Void btnShowRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlInici->Visible = false;
		pnlRegister->Visible = true;
	}

	private: System::Void btnShowRegisterFromLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlLogin->Visible = false;
		pnlRegister->Visible = true;
	}

	private: System::Void cmbRegTipus_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ tipus = cmbRegTipus->Text;
		if (tipus == L"Capita" || tipus == L"Capità" || tipus == L"Administrador") {
			lblRegTelefon->Visible = true;
			txtRegTelefon->Visible = true;
		}
		else {
			lblRegTelefon->Visible = false;
			txtRegTelefon->Visible = false;
		}
	}

	private: System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlLogin->Visible = false;
		pnlRegister->Visible = false;
		pnlInici->Visible = true;
	}

	private: System::Void btnLoginAct_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ correu = txtLoginCorreu->Text;
		String^ pass = txtLoginPass->Text;

		try {
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			bool valid = ctrlInici->IniciarSessio(correu, pass);
			if (valid) {
				currentUsuariTipus = ctrlInici->ObtenirTipusUsuari(correu);
				currentUsuariCorreu = correu;
				pnlLogin->Visible = false;
				pnlMain->Visible = true;
				pnlMain->BringToFront();
				pnlRegister->Visible = false;
				pnlConsultar->Visible = false;
				pnlCrearLliga->Visible = false;
				pnlGestionarLliga->Visible = false;
				pnlEnregistrarEquip->Visible = false;
				pnlGestionarEquip->Visible = false;
				pnlAfegirJugador->Visible = false;

				// --- LÒGICA ADMINISTRADOR ---
				if (currentUsuariTipus->ToLower() == "administrador") {
					btnCrearLligaMainMenu->Visible = true;
					Playcampus::Domini::CtrlCrearLliga^ ctrlCrear = gcnew Playcampus::Domini::CtrlCrearLliga();
					if (ctrlCrear->TeLligaActiva(currentUsuariCorreu)) {
						btnCrearLligaMainMenu->Text = L"Gestionar Lliga";
					}
					else {
						btnCrearLligaMainMenu->Text = L"Crear Lliga";
					}
				}
				else {
					btnCrearLligaMainMenu->Visible = false;
				}

				// --- LÒGICA CAPITÀ ---
				if (currentUsuariTipus->ToLower() == "capita") {
					btnEnregistrarEquip->Visible = true;
					btnUnirEquipLliga->Visible = true;

					// NOU: Mostrem el botó de gestionar convocatòries
					if (btnGestionarConvocatoria != nullptr) {
						btnGestionarConvocatoria->Visible = true;
						btnGestionarConvocatoria->BringToFront();
					}

					if (ctrlInici->CapitaTeEquip(currentUsuariCorreu)) {
						btnEnregistrarEquip->Text = L"Gestionar Equip";
					}
					else {
						btnEnregistrarEquip->Text = L"Enregistrar Equip";
					}

					if (ctrlInici->EquipEstaEnLliga(currentUsuariCorreu)) {
						btnUnirEquipLliga->Text = L"Abandonar Lliga";
					}
					else {
						btnUnirEquipLliga->Text = L"Unir equip a lliga";
					}

				}
				else {
					btnEnregistrarEquip->Visible = false;
					btnUnirEquipLliga->Visible = false;
					if (btnGestionarConvocatoria != nullptr) btnGestionarConvocatoria->Visible = false;
				}

				// --- LÒGICA JUGADOR (NOU CARTELL) ---
				if (currentUsuariTipus->ToLower() == "jugador") {
					Playcampus::Domini::CtlrConvocarJugadors^ ctrlConv = gcnew Playcampus::Domini::CtlrConvocarJugadors();
					auto avis = ctrlConv->ObtenirAvisPendent(currentUsuariCorreu);

					if (avis != nullptr) {
						idPartitPendentConfirmar = avis["idPartit"];
						MostrarAvisJugador(avis["missatge"] + L"\n\nPots assistir-hi?");
					}
				}

				txtLoginCorreu->Text = "";
				txtLoginPass->Text = "";

				// Forcem a redibuixar la pantalla amb els nous botons
				Form1_Resize(nullptr, nullptr);
			}
			else {
				MessageBox::Show(L"Credencials incorrectes.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en iniciar sessió: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	// NOU: Mètodes per gestionar el panell d'edició de partits
	private: System::Void MostrarPantallaEditarPartit() {
		pnlGestionarLliga->Visible = false;
		pnlEditarPartit->Visible = true;
		pnlEditarPartit->BringToFront();

		try {
			Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
			String^ nomLliga = ctrl->ObtenirNomLligaAdmin(currentUsuariCorreu);
			if (String::IsNullOrEmpty(nomLliga)) {
				MessageBox::Show(L"No s'ha trobat cap lliga per a aquest administrador.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			auto partits = ctrl->ObtenirPartitsPerLliga(nomLliga, currentUsuariCorreu);
			cmbPartitsAEditar->Items->Clear();
			partitPerId->Clear();

			for each (auto partit in partits) {
				String^ displayText = String::Format("{0} vs {1} ({2})", partit["equipLocal"], partit["equipVisitant"], partit["dataHora"]);
				cmbPartitsAEditar->Items->Add(displayText);
				partitPerId[displayText] = partit["idPartit"];
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar els partits: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		Form1_Resize(nullptr, nullptr);
	}

	private: System::Void cmbPartitsAEditar_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbPartitsAEditar->SelectedIndex == -1) return;

		String^ selectedDisplayText = cmbPartitsAEditar->SelectedItem->ToString();
		String^ idPartit = partitPerId[selectedDisplayText];

		try {
			Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
			auto detallPartit = ctrl->ObtenirDetallPartit(idPartit, currentUsuariCorreu);

			txtResultatLocal->Text = detallPartit["golsLocal"];
			txtResultatVisitant->Text = detallPartit["golsVisitant"];
           int idxEstat = cmbEstatPartit->FindStringExact(detallPartit["estat"]);
			cmbEstatPartit->SelectedIndex = (idxEstat >= 0) ? idxEstat : -1;

			auto jugadors = ctrl->ObtenirJugadorsPartit(idPartit, currentUsuariCorreu);
			dgvEstadistiquesJugadors->Columns->Clear();
			dgvEstadistiquesJugadors->DataSource = nullptr;

			DataTable^ dt = gcnew DataTable();
			dt->Columns->Add("idJugador");
			dt->Columns->Add("Nom Jugador");
			dt->Columns->Add("Equip");
			dt->Columns->Add("Gols", System::Int32::typeid);
			dt->Columns->Add("Assistencies", System::Int32::typeid);
			dt->Columns->Add("Targetes Grogues", System::Int32::typeid);
			dt->Columns->Add("Targetes Vermelles", System::Int32::typeid);

			for each (auto jugador in jugadors) {
				dt->Rows->Add(jugador["idJugador"], jugador["nomJugador"], jugador["nomEquip"], 0, 0, 0, 0);
			}

			dgvEstadistiquesJugadors->DataSource = dt;
			dgvEstadistiquesJugadors->Columns["idJugador"]->Visible = false;
			dgvEstadistiquesJugadors->Columns["Nom Jugador"]->ReadOnly = true;
			dgvEstadistiquesJugadors->Columns["Equip"]->ReadOnly = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar els detalls del partit: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnGuardarEstadistiques_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbPartitsAEditar->SelectedIndex == -1) {
			MessageBox::Show(L"Selecciona un partit primer.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		String^ selectedDisplayText = cmbPartitsAEditar->SelectedItem->ToString();
		String^ idPartit = partitPerId[selectedDisplayText];
		String^ nouEstat = cmbEstatPartit->SelectedItem->ToString();
		int golsLocal;
		int golsVisitant;

		if (!Int32::TryParse(txtResultatLocal->Text, golsLocal) || !Int32::TryParse(txtResultatVisitant->Text, golsVisitant)) {
			MessageBox::Show(L"Els resultats han de ser números enters.", L"Error de validació", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		System::Text::StringBuilder^ statsCsv = gcnew System::Text::StringBuilder();
		statsCsv->AppendLine("idJugador;NomJugador;equip;gols;assistencies;targetesGrogues;targetesVermelles");

		for each (DataGridViewRow^ row in dgvEstadistiquesJugadors->Rows) {
			if (row->IsNewRow) continue;
			String^ idJugador = row->Cells["idJugador"]->Value->ToString();
			String^ nom = row->Cells["Nom Jugador"]->Value->ToString();
			String^ equip = row->Cells["Equip"]->Value->ToString();
			int gols = Convert::ToInt32(row->Cells["Gols"]->Value);
			int assist = Convert::ToInt32(row->Cells["Assistencies"]->Value);
			int tg = Convert::ToInt32(row->Cells["Targetes Grogues"]->Value);
			int tv = Convert::ToInt32(row->Cells["Targetes Vermelles"]->Value);
			statsCsv->AppendFormat("{0};{1};{2};{3};{4};{5};{6}\n", idJugador, nom, equip, gols, assist, tg, tv);
		}

		Nullable<DateTime> novaData;
		if (nouEstat == "Aplaçat") {
			novaData = dtpDataPartit->Value;
		}

		try {
			Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();
			ctrl->ActualitzarPartitIStats(idPartit, nouEstat, golsLocal, golsVisitant, statsCsv->ToString(), currentUsuariCorreu, novaData);
			MessageBox::Show(L"Partit i estadístiques actualitzats correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			btnTornarEditarPartit_Click(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al guardar les dades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnTornarEditarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEditarPartit->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

	private: System::Void cmbEstatPartit_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		bool esAplacat = cmbEstatPartit->SelectedItem->ToString() == "Aplaçat";
		lblDataPartit->Visible = esAplacat;
		dtpDataPartit->Visible = esAplacat;
	}


	private: System::Void btnRegAct_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtRegNom->Text;
		String^ correu = txtRegCorreu->Text;
		String^ pass = txtRegPass->Text;
		String^ tipus = cmbRegTipus->Text;
		String^ telefon = txtRegTelefon->Text;

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(correu) || String::IsNullOrEmpty(pass)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		if ((tipus == L"Capita" || tipus == L"Administrador") && String::IsNullOrEmpty(telefon)) {
			MessageBox::Show(L"Cal introduir el telèfon per al capità i administrador.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlRegistrarUsuari^ ctrlReg = gcnew Playcampus::Domini::CtrlRegistrarUsuari();
			ctrlReg->CrearUsuari(nom, pass, DateTime::Now, correu, tipus, telefon);
			MessageBox::Show(L"Usuari registrat correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			pnlRegister->Visible = false;
			pnlInici->Visible = true;

			txtRegNom->Text = L"";
			txtRegCorreu->Text = L"";
		txtRegPass->Text = L"";
			cmbRegTipus->SelectedIndex = 0;
			txtRegTelefon->Text = L"";
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al registrar: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
		Playcampus::Domini::CtrlTancarSessio^ ctrlTancar = gcnew Playcampus::Domini::CtrlTancarSessio();
		ctrlTancar->TancarSessio();

		currentUsuariTipus = L"";
		currentUsuariCorreu = L"";
		pnlConsultar->Visible = false;
		pnlCrearLliga->Visible = false;
		pnlGestionarLliga->Visible = false;
		pnlEnregistrarEquip->Visible = false;
		pnlGestionarEquip->Visible = false;
		pnlAfegirJugador->Visible = false;
		pnlEstadistiques->Visible = false;
		pnlMain->Visible = false;
		pnlInici->Visible = true;
	}

	private: System::Void btnConsultar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlConsultar->Visible = true;
		txtNomLliga->Text = L"";
	}

	private: System::Void btnTornarConsultar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlConsultar->Visible = false;
		pnlMain->Visible = true;
		txtNomLliga->Text = L"";
	}

	private: System::Void btnComprovarLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtNomLliga->Text;
		try {
			Playcampus::Domini::CtrlCrearLliga^ ctrlTornar = gcnew Playcampus::Domini::CtrlCrearLliga();
			bool check = ctrlTornar->ExisteixLliga(nom);
			if (check) MessageBox::Show(L"Aquesta lliga ja existeix");
			else MessageBox::Show(L"Aquesta lliga no existeix");
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error : " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnCrearLligaMainMenu_Click(System::Object^ sender, System::EventArgs^ e) {
		if (btnCrearLligaMainMenu->Text == L"Gestionar Lliga") {
			pnlMain->Visible = false;
			pnlGestionarLliga->Visible = true;
			return;
		}
		pnlMain->Visible = false;
		pnlCrearLliga->Visible = true;
		txtCLNom->Text = L"";
		txtCLPass->Text = L"";
		cmbCLEsport->SelectedIndex = -1;
	}

	private: System::Void btnGLTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarLliga->Visible = false;
		pnlMain->Visible = true;
	}

		private: System::Void btnGLCrearJornada_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearJornada->Visible = true;

			txtCJNomLliga->Text = L"";
			cmbCJTemporada->Items->Clear();
			cjTemporadaIds->Clear();
			dtpCJDataInici->Value = DateTime::Now;
			dtpCJDataFi->Value = DateTime::Now.AddDays(7); // Acostuma a durar 1 setmana
		}

	private: System::Void btnCJCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearJornada->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

	private: System::Void btnCJBuscarTemporades_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtCJNomLliga->Text;
		if (String::IsNullOrWhiteSpace(nomLliga)) {
			MessageBox::Show(L"Introdueix el nom de la Lliga.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			
			Playcampus::Domini::CtrlCrearJornada^ ctrl = gcnew Playcampus::Domini::CtrlCrearJornada();

			// Comprovar que ets l'administrador
			bool esAdmin = ctrl->ValidarAdministradorLliga(nomLliga, currentUsuariCorreu);
			if (!esAdmin) {
				MessageBox::Show(L"No ets l'administrador d'aquesta lliga o la lliga no existeix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// Obtenir temporades de la lliga
			System::Collections::Generic::List<System::Collections::Generic::Dictionary<String^, String^>^>^ temporades = ctrl->ObtenirTemporadesLliga(nomLliga);

			cmbCJTemporada->Items->Clear();
			cjTemporadaIds->Clear();

			for each(auto temp in temporades) {
				String^ display = temp["dataInici"] + L" - " + temp["dataFi"];
				cmbCJTemporada->Items->Add(display);
				cjTemporadaIds->Add(temp["idTemporada"]);
			}

			if (cmbCJTemporada->Items->Count > 0) cmbCJTemporada->SelectedIndex = 0;
			else MessageBox::Show(L"No s'han trobat temporades per a aquesta lliga.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Information);
			

		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al cercar temporades: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnCJConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbCJTemporada->SelectedIndex == -1) {
			MessageBox::Show(L"Si us plau, cerca i selecciona una Temporada.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int numJornada = 0; 
		if (!Int32::TryParse(txtCJNumero->Text, numJornada)) {
			MessageBox::Show(L"Introdueix un número de jornada vàlid.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		DateTime dataInici = dtpCJDataInici->Value;
		DateTime dataFi = dtpCJDataFi->Value;

		if (dataFi <= dataInici) {
			MessageBox::Show(L"La data de fi ha de ser posterior a la data d'inici.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			
			Playcampus::Domini::CtrlCrearJornada^ ctrl = gcnew Playcampus::Domini::CtrlCrearJornada();
			String^ idTemporadaSelecionada = cjTemporadaIds[cmbCJTemporada->SelectedIndex];
			String^ estat = L"Proxim"; // Per defecte

			ctrl->CrearJornada(idTemporadaSelecionada, numJornada, dataInici, dataFi, estat);
			
			MessageBox::Show(L"Jornada creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			pnlCrearJornada->Visible = false;
			pnlGestionarLliga->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al desar la jornada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

		private: System::Void btnGLCrearTemporada_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearTemporada->Visible = true;
			txtCTNomLliga->Text = L""; // <--- AFEGIR AQUESTA LÍNIA PELS VALORS RESIDUALS
			dtpCTDataInici->Value = DateTime::Now;
			dtpCTDataFi->Value = DateTime::Now.AddMonths(6); // Por defecto acaba en 6 meses
		}

	private: System::Void btnCTCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearTemporada->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

	private: System::Void btnCTConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		DateTime dataInici = dtpCTDataInici->Value;
		DateTime dataFi = dtpCTDataFi->Value;
		String^ nomLliga = txtCTNomLliga->Text; // <--- AFEGIR AQUESTA VARIABLE

		if (String::IsNullOrWhiteSpace(nomLliga)) { // <-- EVITAR QUE EL NOMBRE ESTE EN BLANCO
			MessageBox::Show(L"Introdueix el nom de la Lliga a la que vols unir la temporada.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (dataFi <= dataInici) {
			MessageBox::Show(L"La data de fi ha de ser posterior a la data d'inici.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			// Instanciar el controlador y llamar a la BD pasandole ahora el nombre
			Playcampus::Domini::CtrlCrearTemporada^ ctrl = gcnew Playcampus::Domini::CtrlCrearTemporada();
			ctrl->CrearTemporada(dataInici, dataFi, currentUsuariCorreu, nomLliga); // <--- AFEGIM EL NOU PARAMETRE

			MessageBox::Show(L"Temporada creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			pnlCrearTemporada->Visible = false;
			pnlGestionarLliga->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al crear la temporada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}


		private: System::Void btnGLAfegirPartit_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlGestionarLliga->Visible = false;
			pnlCrearPartit->Visible = true;

			// Netejem tot 
			txtCPNomLliga->Text = L"";
			cmbCPTemporada->Items->Clear();
			cmbCPJornada->Items->Clear();
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();
			txtCPUbicacio->Text = L"";
			dtpCPData->Value = DateTime::Now;

			// Deshabilitem combos fins que es validi la lliga
			cmbCPTemporada->Enabled = false;
			cmbCPJornada->Enabled = false;
			cmbCPEquipLocal->Enabled = false;
			cmbCPEquipVisitant->Enabled = false;
		}

		private: System::Void btnGLEditarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
           MostrarPantallaEditarPartit();
			return;
			try {
                Playcampus::Domini::CtrlEditarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEditarPartit();

				String^ nomLliga = ctrl->ObtenirNomLligaAdmin(currentUsuariCorreu);
				if (String::IsNullOrWhiteSpace(nomLliga)) {
					MessageBox::Show(L"No s'ha trobat cap lliga associada a aquest administrador.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

				auto partits = ctrl->ObtenirPartitsPerLliga(nomLliga, currentUsuariCorreu);
				if (partits->Count == 0) {
					MessageBox::Show(L"No s'han trobat partits per a aquesta lliga.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
					return;
				}

				Form^ frmPartit = gcnew Form();
				frmPartit->Text = L"Editar partit - Selecció de partit";
              frmPartit->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				frmPartit->StartPosition = FormStartPosition::CenterParent;
				frmPartit->ClientSize = System::Drawing::Size(720, 170);
				frmPartit->MinimizeBox = false;
				frmPartit->MaximizeBox = false;

				Label^ lblPartit = gcnew Label();
				lblPartit->Text = L"Selecciona el partit:";
				lblPartit->Location = System::Drawing::Point(20, 22);
				lblPartit->AutoSize = true;

				ComboBox^ cmbPartits = gcnew ComboBox();
				cmbPartits->DropDownStyle = ComboBoxStyle::DropDownList;
				cmbPartits->Location = System::Drawing::Point(20, 48);
				cmbPartits->Size = System::Drawing::Size(680, 24);

				for each (auto p in partits) {
					String^ display = p["dataHora"] + L" - " + p["equipLocal"] + L" vs " + p["equipVisitant"] + L" [" + p["estat"] + L"]";
					cmbPartits->Items->Add(display);
				}

				if (cmbPartits->Items->Count > 0) {
					cmbPartits->SelectedIndex = 0;
				}

				Button^ btnOkPartit = gcnew Button();
				btnOkPartit->Text = L"Editar";
				btnOkPartit->DialogResult = System::Windows::Forms::DialogResult::OK;
				btnOkPartit->Location = System::Drawing::Point(520, 110);
				btnOkPartit->Size = System::Drawing::Size(85, 30);

				Button^ btnCancelPartit = gcnew Button();
				btnCancelPartit->Text = L"Cancel·lar";
				btnCancelPartit->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				btnCancelPartit->Location = System::Drawing::Point(615, 110);
				btnCancelPartit->Size = System::Drawing::Size(85, 30);

				frmPartit->Controls->Add(lblPartit);
				frmPartit->Controls->Add(cmbPartits);
				frmPartit->Controls->Add(btnOkPartit);
				frmPartit->Controls->Add(btnCancelPartit);
				frmPartit->AcceptButton = btnOkPartit;
				frmPartit->CancelButton = btnCancelPartit;

				if (frmPartit->ShowDialog(this) != System::Windows::Forms::DialogResult::OK) {
					return;
				}

				if (cmbPartits->SelectedIndex < 0) {
					MessageBox::Show(L"Selecciona un partit.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

		
				String^ idPartit = partits[cmbPartits->SelectedIndex]->default["idPartit"];

				auto detall = ctrl->ObtenirDetallPartit(idPartit, currentUsuariCorreu);

				String^ disciplina = detall["disciplina"];
				String^ disciplinaLower = disciplina->ToLowerInvariant();
               array<String^>^ campsStats;
				if (disciplinaLower->Contains(L"fut")) {
					campsStats = gcnew array<String^>{ L"gols", L"assistencies", L"targetesGrogues", L"targetesVermelles" };
				}
				else if (disciplinaLower->Contains(L"basq")) {
					campsStats = gcnew array<String^>{ L"punts", L"rebots", L"assistencies", L"faltes" };
				}
				else {
					campsStats = gcnew array<String^>{ L"punts", L"aces", L"blocs", L"errors" };
				}

				Form^ frmEditar = gcnew Form();
				frmEditar->Text = L"Editar partit";
              frmEditar->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				frmEditar->StartPosition = FormStartPosition::CenterParent;
				frmEditar->ClientSize = System::Drawing::Size(760, 540);
				frmEditar->MinimizeBox = false;
				frmEditar->MaximizeBox = false;

				Label^ lblEstat = gcnew Label();
				lblEstat->Text = L"Estat del partit:";
				lblEstat->Location = System::Drawing::Point(20, 20);
				lblEstat->AutoSize = true;

				ComboBox^ cmbEstat = gcnew ComboBox();
				cmbEstat->DropDownStyle = ComboBoxStyle::DropDownList;
				cmbEstat->Items->AddRange(gcnew cli::array<System::Object^>(4) { L"Pendent", L"En joc", L"Finalitzat", L"Aplaçat" });
				cmbEstat->Location = System::Drawing::Point(150, 18);
				cmbEstat->Size = System::Drawing::Size(160, 24);

				int idxEstat = cmbEstat->FindStringExact(detall["estat"]);
				cmbEstat->SelectedIndex = (idxEstat >= 0) ? idxEstat : 0;

				Label^ lblNovaData = gcnew Label();
             lblNovaData->Text = L"Nova data i hora (si Aplaçat):";
				lblNovaData->Location = System::Drawing::Point(340, 20);
				lblNovaData->AutoSize = true;

				DateTimePicker^ dtpNovaData = gcnew DateTimePicker();
              dtpNovaData->Format = DateTimePickerFormat::Custom;
				dtpNovaData->CustomFormat = L"dd/MM/yyyy HH:mm";
				dtpNovaData->ShowUpDown = true;
				dtpNovaData->Location = System::Drawing::Point(500, 18);
             dtpNovaData->Size = System::Drawing::Size(150, 22);
				dtpNovaData->Value = DateTime::Now.AddDays(1);

				Label^ lblResLocal = gcnew Label();
				lblResLocal->Text = L"Resultat local:";
				lblResLocal->Location = System::Drawing::Point(20, 62);
				lblResLocal->AutoSize = true;

				NumericUpDown^ numLocal = gcnew NumericUpDown();
				numLocal->Location = System::Drawing::Point(150, 60);
				numLocal->Size = System::Drawing::Size(100, 22);
				numLocal->Minimum = 0;
				numLocal->Maximum = 300;

				Label^ lblResVisit = gcnew Label();
				lblResVisit->Text = L"Resultat visitant:";
				lblResVisit->Location = System::Drawing::Point(280, 62);
				lblResVisit->AutoSize = true;

				NumericUpDown^ numVisit = gcnew NumericUpDown();
				numVisit->Location = System::Drawing::Point(420, 60);
				numVisit->Size = System::Drawing::Size(100, 22);
				numVisit->Minimum = 0;
				numVisit->Maximum = 300;

				int golsLocal = 0;
				int golsVisitant = 0;
				Int32::TryParse(detall["golsLocal"], golsLocal);
				Int32::TryParse(detall["golsVisitant"], golsVisitant);
				numLocal->Value = golsLocal;
				numVisit->Value = golsVisitant;

				Label^ lblDisc = gcnew Label();
				lblDisc->Text = L"Disciplina de la lliga: " + disciplina;
				lblDisc->Location = System::Drawing::Point(20, 104);
				lblDisc->AutoSize = true;

				Label^ lblStatsInfo = gcnew Label();
                lblStatsInfo->Text = L"Estadístiques individuals (taula per jugadors):";
				lblStatsInfo->Location = System::Drawing::Point(20, 132);
				lblStatsInfo->AutoSize = true;

                DataGridView^ dgvStats = gcnew DataGridView();
				dgvStats->Location = System::Drawing::Point(20, 160);
				dgvStats->Size = System::Drawing::Size(720, 310);
                dgvStats->AllowUserToAddRows = false;
				dgvStats->AllowUserToDeleteRows = true;
				dgvStats->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
				dgvStats->RowHeadersVisible = false;
				dgvStats->SelectionMode = DataGridViewSelectionMode::FullRowSelect;

				DataGridViewCheckBoxColumn^ colIncloure = gcnew DataGridViewCheckBoxColumn();
				colIncloure->HeaderText = L"Incloure";
				colIncloure->Name = L"Incloure";
				colIncloure->Width = 70;
				dgvStats->Columns->Add(colIncloure);

				DataGridViewTextBoxColumn^ colNom = gcnew DataGridViewTextBoxColumn();
				colNom->HeaderText = L"NomJugador";
				colNom->Name = L"NomJugador";
				dgvStats->Columns->Add(colNom);

				DataGridViewComboBoxColumn^ colEquip = gcnew DataGridViewComboBoxColumn();
				colEquip->HeaderText = L"equip";
				colEquip->Name = L"equip";
				colEquip->Items->Add(L"Local");
				colEquip->Items->Add(L"Visitant");
				dgvStats->Columns->Add(colEquip);

				for each (String ^ camp in campsStats) {
					DataGridViewTextBoxColumn^ col = gcnew DataGridViewTextBoxColumn();
					col->HeaderText = camp;
					col->Name = camp;
					dgvStats->Columns->Add(col);
				}

				auto jugadorsPartit = ctrl->ObtenirJugadorsPartit(idPartit, currentUsuariCorreu);
				if (jugadorsPartit->Count == 0) {
                    dgvStats->AllowUserToAddRows = false;
				}

				for each (auto j in jugadorsPartit) {
					String^ nomJ = j["nomJugador"];
					String^ equipJ = j["equip"];
					array<Object^>^ fila = gcnew array<Object^>(3 + campsStats->Length);
					fila[0] = false;
					fila[1] = nomJ;
					fila[2] = equipJ;
					for (int i = 0; i < campsStats->Length; ++i) {
						fila[3 + i] = L"0";
					}

					dgvStats->Rows->Add(fila);
				}

				Button^ btnGuardar = gcnew Button();
				btnGuardar->Text = L"Guardar canvis";
				btnGuardar->DialogResult = System::Windows::Forms::DialogResult::OK;
				btnGuardar->Location = System::Drawing::Point(548, 490);
				btnGuardar->Size = System::Drawing::Size(95, 32);

				Button^ btnCancelEditar = gcnew Button();
				btnCancelEditar->Text = L"Cancel·lar";
				btnCancelEditar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				btnCancelEditar->Location = System::Drawing::Point(648, 490);
				btnCancelEditar->Size = System::Drawing::Size(92, 32);

				frmEditar->Controls->Add(lblEstat);
				frmEditar->Controls->Add(cmbEstat);
              frmEditar->Controls->Add(lblNovaData);
				frmEditar->Controls->Add(dtpNovaData);
				frmEditar->Controls->Add(lblResLocal);
				frmEditar->Controls->Add(numLocal);
				frmEditar->Controls->Add(lblResVisit);
				frmEditar->Controls->Add(numVisit);
				frmEditar->Controls->Add(lblDisc);
				frmEditar->Controls->Add(lblStatsInfo);
             frmEditar->Controls->Add(dgvStats);
				frmEditar->Controls->Add(btnGuardar);
				frmEditar->Controls->Add(btnCancelEditar);
				frmEditar->AcceptButton = btnGuardar;
				frmEditar->CancelButton = btnCancelEditar;

				if (frmEditar->ShowDialog(this) != System::Windows::Forms::DialogResult::OK) {
					return;
				}

				if (String::IsNullOrWhiteSpace(cmbEstat->Text)) {
					MessageBox::Show(L"Selecciona un estat del partit.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return;
				}

                bool esAplacat = (cmbEstat->Text == L"Aplaçat");
				if (esAplacat) {
					numLocal->Value = 0;
					numVisit->Value = 0;
				}

				String^ statsSerialitzades = L"";
				if (!esAplacat) {
					String^ capcalera = L"NomJugador;equip";
					for each (String ^ camp in campsStats) {
						capcalera += L";" + camp;
					}

					System::Text::StringBuilder^ sbStats = gcnew System::Text::StringBuilder();
					sbStats->AppendLine(capcalera);

					for each (DataGridViewRow ^ row in dgvStats->Rows) {
						if (row->IsNewRow) continue;

						bool incloure = false;
						if (row->Cells[0]->Value != nullptr) {
							incloure = Convert::ToBoolean(row->Cells[0]->Value);
						}
						if (!incloure) continue;

						String^ nomJugador = (row->Cells[1]->Value == nullptr) ? L"" : row->Cells[1]->Value->ToString()->Trim();
						String^ equipJugador = (row->Cells[2]->Value == nullptr) ? L"" : row->Cells[2]->Value->ToString()->Trim();

						if (String::IsNullOrWhiteSpace(nomJugador) && String::IsNullOrWhiteSpace(equipJugador)) {
							continue;
						}

						if (String::IsNullOrWhiteSpace(nomJugador) || String::IsNullOrWhiteSpace(equipJugador)) {
							MessageBox::Show(L"Cada fila de estadístiques ha de tenir NomJugador i Equip.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
							return;
						}

						String^ liniaStats = nomJugador + L";" + equipJugador;
						for (int i = 0; i < campsStats->Length; ++i) {
							Object^ valor = row->Cells[3 + i]->Value;
							String^ txtValor = (valor == nullptr) ? L"0" : valor->ToString()->Trim();

							int valorNumeric = 0;
							if (!Int32::TryParse(txtValor, valorNumeric) || valorNumeric < 0) {
								MessageBox::Show(L"Els camps estadístics han de ser números enters positius o zero.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
								return;
							}

							liniaStats += L";" + valorNumeric.ToString();
						}

						sbStats->AppendLine(liniaStats);
					}

                   statsSerialitzades = sbStats->ToString();
				}
				Nullable<DateTime> novaDataPartit = Nullable<DateTime>();
				if (esAplacat) {
					novaDataPartit = dtpNovaData->Value;
				}

				ctrl->ActualitzarPartitIStats(
					idPartit,
					cmbEstat->Text,
					Convert::ToInt32(numLocal->Value),
					Convert::ToInt32(numVisit->Value),
                    statsSerialitzades,
					currentUsuariCorreu,
					novaDataPartit
				);

				MessageBox::Show(L"Partit actualitzat correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error en editar el partit: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		

	private: System::Void btnCPValidarLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nomLliga = txtCPNomLliga->Text;
		if (String::IsNullOrWhiteSpace(nomLliga)) {
			MessageBox::Show(L"Introdueix el nom de la Lliga a validar", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();

			// 1. Validar que la liga existe y somos dueños
			if (!ctrl->ValidarAdministradorLliga(nomLliga, currentUsuariCorreu)) {
				MessageBox::Show(L"No ets administrador d'aquesta lliga o no existeix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			// 2. Obtener Temporadas
			auto temporades = ctrl->ObtenirTemporadesLliga(nomLliga);
			cmbCPTemporada->Items->Clear();
			cpTemporadesIds->Clear();

			for each(auto temp in temporades) {
				String^ txt = temp["dataInici"] + L" a " + temp["dataFi"];
				cmbCPTemporada->Items->Add(txt);
				cpTemporadesIds->Add(temp["idTemporada"]); // Guardar ID Oculto
			}

			// 3. Cargar Equipos (se hace por liga, así que los cargamos ya)
			auto equips = ctrl->ObtenirNomsEquipsPerLliga(nomLliga);
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();

			for each(String ^ nom in equips) {
				cmbCPEquipLocal->Items->Add(nom);
				cmbCPEquipVisitant->Items->Add(nom);
			}

			// Habilitar los combos porque la liga es válida
			cmbCPTemporada->Enabled = true;
			cmbCPEquipLocal->Enabled = true;
			cmbCPEquipVisitant->Enabled = true;

			if (cmbCPTemporada->Items->Count > 0) cmbCPTemporada->SelectedIndex = 0;

			MessageBox::Show(L"Lliga carregada correctament. Selecciona temporada i equips.", L"Lliga Trobada", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al validar la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

		   // Cuando escoges una Temporada, buscar las Jornadas correspondientes
	private: System::Void cmbCPTemporada_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cmbCPTemporada->SelectedIndex == -1) return;

		try {
			Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();
			String^ idTempSeleccionada = cpTemporadesIds[cmbCPTemporada->SelectedIndex];

			auto jornades = ctrl->ObtenirJornadesTemporada(idTempSeleccionada);

			cmbCPJornada->Items->Clear();
			cpJornadesIds->Clear();

			for each(auto jorn in jornades) {
				String^ text = L"Jornada " + jorn["numero"] + L" (" + jorn["dataInici"] + L")";
				cmbCPJornada->Items->Add(text);
				cpJornadesIds->Add(jorn["idJornada"]); // Guardar la ID
			}

			cmbCPJornada->Enabled = true;
			if (cmbCPJornada->Items->Count > 0) cmbCPJornada->SelectedIndex = 0;
			else MessageBox::Show(L"Aquesta temporada no té jornades.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);

		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant jornades: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}


		private: System::Void btnCPCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlCrearPartit->Visible = false;

			// Netegem els combos quan marxem
			cmbCPJornada->Items->Clear();
			cmbCPEquipLocal->Items->Clear();
			cmbCPEquipVisitant->Items->Clear();
			txtCPUbicacio->Text = L"";

			if (btnCrearLligaMainMenu->Text == L"Gestionar Lliga") {
				pnlGestionarLliga->Visible = true;
			}
			else {
				pnlMain->Visible = true;
			}
		}

		private: System::Void btnCPConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
			// Validar dades
			if (cmbCPJornada->SelectedIndex == -1 || cmbCPEquipLocal->SelectedIndex == -1 || cmbCPEquipVisitant->SelectedIndex == -1 || String::IsNullOrWhiteSpace(txtCPUbicacio->Text) || String::IsNullOrWhiteSpace(txtCPNomLliga->Text)) {
				MessageBox::Show(L"Si us plau, valida la lliga i omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			String^ equipLocal = cmbCPEquipLocal->SelectedItem->ToString();
			String^ equipVisit = cmbCPEquipVisitant->SelectedItem->ToString();

			if (equipLocal == equipVisit) {
				MessageBox::Show(L"L'equip local i visitant no poden ser el mateix.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			DateTime dataPartit = dtpCPData->Value;
			String^ ubicacioStr = txtCPUbicacio->Text;
			String^ lligaStr = txtCPNomLliga->Text;

			// Agafar la ID de la jornada que hem guardat prèviament al omplir el ComboBox
			int indexJornada = cmbCPJornada->SelectedIndex;
			if (indexJornada < 0 || indexJornada >= cpJornadesIds->Count) {
				MessageBox::Show(L"No s'ha pogut determinar la jornada seleccionada", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ idJornada = cpJornadesIds[indexJornada];

			try {
				Playcampus::Domini::CtrlCrearPartit^ ctrl = gcnew Playcampus::Domini::CtrlCrearPartit();

				// Passem l'ID de la jornada (String) en el 5è paràmetre
				ctrl->CrearPartit(dataPartit, ubicacioStr, equipLocal, equipVisit, idJornada, currentUsuariTipus);

				MessageBox::Show(L"Partit creat i desat a la base de dades correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				pnlCrearPartit->Visible = false;
				pnlGestionarLliga->Visible = true;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al desar el partit: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

	private: System::Void MostrarTaulaConsulta(System::String^ titol, System::Data::DataTable^ dades) {
		Form^ finestra = gcnew Form();
		finestra->Text = titol;
		finestra->StartPosition = FormStartPosition::CenterParent;
		finestra->Size = System::Drawing::Size(950, 520);
		finestra->MinimizeBox = false;
		finestra->MaximizeBox = true;

		DataGridView^ graella = gcnew DataGridView();
		graella->Dock = DockStyle::Fill;
		graella->ReadOnly = true;
		graella->AllowUserToAddRows = false;
		graella->AllowUserToDeleteRows = false;
		graella->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
		graella->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		graella->DataSource = dades;

		Button^ btnTancar = gcnew Button();
		btnTancar->Text = L"Tancar";
		btnTancar->Dock = DockStyle::Bottom;
		btnTancar->Height = 35;
		btnTancar->DialogResult = System::Windows::Forms::DialogResult::OK;

		finestra->Controls->Add(graella);
		finestra->Controls->Add(btnTancar);
		finestra->AcceptButton = btnTancar;
		finestra->ShowDialog(this);
	}

	private: System::Void MostrarConsultaGeneral(System::String^ titol, System::Data::DataTable^ dades) {
		if (dades == nullptr || dades->Rows->Count == 0) {
			MessageBox::Show(L"No hi ha dades per mostrar.", titol, MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			MostrarTaulaConsulta(titol, dades);
		}
	}

	private: System::Void btnProgPartits_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			MostrarConsultaGeneral(L"Programació de partits", ctrl->ObtenirProgramacioPartits());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant la programacio de partits: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnEstatLligues_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			MostrarConsultaGeneral(L"Estat de les lligues", ctrl->ObtenirEstatLligues());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant l'estat de les lligues: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnEstadistiquesMenu_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlEstadistiques->Visible = true;
	}

	private: System::Void btnEstTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlMain->Visible = true;
	}

	private: System::Void btnEstadistiques_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			MostrarConsultaGeneral(L"Estadístiques equips", ctrl->ObtenirEstadistiquesEquips());
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant les estadistiques: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnGLMostrarEquips_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			String^ nomLliga = ctrl->ObtenirNomLligaAdministrador(currentUsuariCorreu);
			if (String::IsNullOrWhiteSpace(nomLliga)) {
				MessageBox::Show(L"No tens cap lliga activa associada.", L"Avis", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else {
				MostrarConsultaGeneral(L"Equips de " + nomLliga, ctrl->ObtenirEquipsDeLaLligaAdministrador(currentUsuariCorreu));
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error carregant els equips: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnGLEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			Playcampus::Domini::CtrlConsultes^ ctrl = gcnew Playcampus::Domini::CtrlConsultes();
			DataTable^ equips = ctrl->ObtenirEquipsDeLaLligaAdministrador(currentUsuariCorreu);
			if (equips == nullptr || equips->Rows->Count == 0) {
				MessageBox::Show(L"No hi ha equips dins de la teva lliga activa.", L"Avis", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				Form^ finestra = gcnew Form();
				finestra->Text = L"Esborrar equip de la lliga";
				finestra->StartPosition = FormStartPosition::CenterParent;
				finestra->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
				finestra->ClientSize = System::Drawing::Size(430, 150);
				finestra->MinimizeBox = false;
				finestra->MaximizeBox = false;

				Label^ lblEquip = gcnew Label();
				lblEquip->Text = L"Selecciona l'equip:";
				lblEquip->Location = System::Drawing::Point(20, 20);
				lblEquip->AutoSize = true;

				ComboBox^ cmbEquips = gcnew ComboBox();
				cmbEquips->DropDownStyle = ComboBoxStyle::DropDownList;
				cmbEquips->Location = System::Drawing::Point(20, 50);
				cmbEquips->Size = System::Drawing::Size(390, 24);

				for each (DataRow^ fila in equips->Rows) {
					cmbEquips->Items->Add(fila[L"Equip"]->ToString() + L" (" + fila[L"IdEquip"]->ToString() + L")");
				}
				cmbEquips->SelectedIndex = 0;

				Button^ btnConfirmar = gcnew Button();
				btnConfirmar->Text = L"Esborrar";
				btnConfirmar->DialogResult = System::Windows::Forms::DialogResult::OK;
				btnConfirmar->Location = System::Drawing::Point(220, 100);
				btnConfirmar->Size = System::Drawing::Size(90, 30);

				Button^ btnCancelar = gcnew Button();
				btnCancelar->Text = L"Cancelar";
				btnCancelar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				btnCancelar->Location = System::Drawing::Point(320, 100);
				btnCancelar->Size = System::Drawing::Size(90, 30);

				finestra->Controls->Add(lblEquip);
				finestra->Controls->Add(cmbEquips);
				finestra->Controls->Add(btnConfirmar);
				finestra->Controls->Add(btnCancelar);
				finestra->AcceptButton = btnConfirmar;
				finestra->CancelButton = btnCancelar;

				if (finestra->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
					DataRow^ filaSeleccionada = equips->Rows[cmbEquips->SelectedIndex];
					String^ idEquip = filaSeleccionada[L"IdEquip"]->ToString();
					String^ nomEquip = filaSeleccionada[L"Equip"]->ToString();

					System::Windows::Forms::DialogResult confirmacio = MessageBox::Show(
						L"Vols treure l'equip '" + nomEquip + L"' de la lliga?",
						L"Confirmació",
						MessageBoxButtons::YesNo,
						MessageBoxIcon::Warning);

					if (confirmacio == System::Windows::Forms::DialogResult::Yes) {
						ctrl->TreureEquipDeLaLliga(idEquip, currentUsuariCorreu);
						MessageBox::Show(L"Equip tret de la lliga correctament.", L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en esborrar l'equip de la lliga: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnGL_EnDesenvolupament_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(L"Funcionalitat en desenvolupament.");
	}

	private: System::Void btnCLTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlCrearLliga->Visible = false;
		pnlMain->Visible = true;
	}

	private: System::Void btnCLGuarda_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtCLNom->Text;
		String^ pass = txtCLPass->Text;
		String^ esport = cmbCLEsport->Text;

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(pass) || String::IsNullOrEmpty(esport)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		Playcampus::Domini::Disciplina disc;
		if (esport == L"Futbol") disc = Playcampus::Domini::Disciplina::Futbol;
		else if (esport == L"Basquet") disc = Playcampus::Domini::Disciplina::Basquet;
		else if (esport == L"Voley") disc = Playcampus::Domini::Disciplina::Voley;
		else disc = Playcampus::Domini::Disciplina::Futbol;

		try {
			Playcampus::Domini::CtrlCrearLliga^ ctrlCrear = gcnew Playcampus::Domini::CtrlCrearLliga();
			// El mètode CrearLliga requereix: idLliga, nom, disciplina, descripcio, contrasenya, tipusUsuari, correuUsuari
			// Generem un ID aleatori o utilitzem el nom com a ID base per fer-ho simple.
			String^ idLliga = "L-" + Guid::NewGuid().ToString()->Substring(0, 8);

			ctrlCrear->CrearLliga(idLliga, nom, disc, L"Nova Lliga " + nom, pass, currentUsuariTipus, currentUsuariCorreu);
			MessageBox::Show(L"Lliga creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			
			btnCrearLligaMainMenu->Text = L"Gestionar Lliga";

			pnlCrearLliga->Visible = false;
			pnlMain->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al crear lliga: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnEnregistrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		if (btnEnregistrarEquip->Text == L"Gestionar Equip") {
			pnlMain->Visible = false;
			pnlGestionarEquip->Visible = true;
			try {
				Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
				dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
               if (dgvPlantilla->Columns->Contains("IdJugador")) {
					dgvPlantilla->Columns["IdJugador"]->Visible = false;
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar la plantilla: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			return;
		}

		pnlMain->Visible = false;
		pnlEnregistrarEquip->Visible = true;
		txtEENom->Text = L"";
		dtpEEData->Value = DateTime::Now;
		cmbEEEscollirEsport->SelectedIndex = -1;
	}

	private: System::Void btnGETornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarEquip->Visible = false;
		pnlMain->Visible = true;
	}

	private: System::Void btnGEEsborrarEquip_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult result = MessageBox::Show(L"Estàs segur que vols esborrar l'equip?", L"Esborrar Equip", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (result == System::Windows::Forms::DialogResult::Yes) {
			try {
				Playcampus::Domini::CtrlEsborrarEquip^ ctrlEsborrar = gcnew Playcampus::Domini::CtrlEsborrarEquip();
				ctrlEsborrar->EsborrarEquip(currentUsuariCorreu);

				MessageBox::Show(L"Equip esborrat correctament!", L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				btnEnregistrarEquip->Text = L"Enregistrar Equip";
				pnlGestionarEquip->Visible = false;
				pnlMain->Visible = true;
			} catch (Exception^ ex) {
				MessageBox::Show(L"Error a l'esborrar l'equip: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
			private: System::Void btnGLRetirarTemporada_Click(System::Object^ sender, System::EventArgs^ e) {
				System::Windows::Forms::DialogResult confirmacio = MessageBox::Show(
					L"Estàs segur que vols retirar la temporada activa respecte a la teva Lliga?",
					L"Confirmació",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Warning
				);

				if (confirmacio == System::Windows::Forms::DialogResult::Yes) {
					try {
						// Es fa servir la teva classe CtrlRetirarTemporada que ja inclous.
						Playcampus::Domini::CtrlRetirarTemporada^ ctrl = gcnew Playcampus::Domini::CtrlRetirarTemporada();

						// Assumint que el mètode accepti el correu de l'administrador per saber-ne la lliga activa:
						ctrl->RetirarTemporada(currentUsuariCorreu); // *Nota: Si la funció d'aquest controlador es diu diferent o prent un altre paràmetre, adapta aquest mètode aquí pel que posa a "CtrlRetirarTemporada.hxx".

						MessageBox::Show(L"La temporada i les seves jornades han estat retirades correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					catch (Exception^ ex) {
						MessageBox::Show(L"Error al retirar la temporada: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}

	private: System::Void btnGEAssignarJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"capita") {
			MessageBox::Show(L"Només els capitans poden accedir a aquesta funcionalitat.", L"Accés denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlAssignarJugador^ ctrlAssignar = gcnew Playcampus::Domini::CtrlAssignarJugador();
			auto partits = ctrlAssignar->ObtenirPartitsDisponibles(currentUsuariCorreu);
			if (partits->Count == 0) {
				MessageBox::Show(L"No hi ha partits no finalitzats disponibles per al teu equip.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			auto jugadors = ctrlAssignar->ObtenirJugadorsEquip(currentUsuariCorreu);
			if (jugadors->Count == 0) {
				MessageBox::Show(L"El teu equip no té jugadors disponibles.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			Form^ frmAssignar = gcnew Form();
			frmAssignar->Text = L"Assignar jugador a partit";
			frmAssignar->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			frmAssignar->StartPosition = FormStartPosition::CenterParent;
			frmAssignar->ClientSize = System::Drawing::Size(720, 220);
			frmAssignar->MinimizeBox = false;
			frmAssignar->MaximizeBox = false;

			Label^ lblPartit = gcnew Label();
			lblPartit->Text = L"Selecciona el partit:";
			lblPartit->Location = System::Drawing::Point(20, 22);
			lblPartit->AutoSize = true;

			ComboBox^ cmbPartits = gcnew ComboBox();
			cmbPartits->DropDownStyle = ComboBoxStyle::DropDownList;
			cmbPartits->Location = System::Drawing::Point(20, 48);
			cmbPartits->Size = System::Drawing::Size(680, 24);

			for each (auto p in partits) {
				String^ ubicacio = String::IsNullOrWhiteSpace(p["ubicacio"]) ? L"" : L" - " + p["ubicacio"];
				String^ display = p["dataHora"] + L" - " + p["equipLocal"] + L" vs " + p["equipVisitant"] + L" [" + p["estat"] + L"]" + ubicacio;
				cmbPartits->Items->Add(display);
			}
			cmbPartits->SelectedIndex = 0;

			Label^ lblJugador = gcnew Label();
			lblJugador->Text = L"Selecciona el jugador:";
			lblJugador->Location = System::Drawing::Point(20, 92);
			lblJugador->AutoSize = true;

			ComboBox^ cmbJugadors = gcnew ComboBox();
			cmbJugadors->DropDownStyle = ComboBoxStyle::DropDownList;
			cmbJugadors->Location = System::Drawing::Point(20, 118);
			cmbJugadors->Size = System::Drawing::Size(680, 24);

			for each (auto j in jugadors) {
				String^ dorsal = String::IsNullOrWhiteSpace(j["dorsal"]) ? L"S/D" : j["dorsal"];
				String^ posicio = String::IsNullOrWhiteSpace(j["posicio"]) ? L"" : L" - " + j["posicio"];
				String^ display = L"#" + dorsal + L" " + j["nom"] + posicio;
				cmbJugadors->Items->Add(display);
			}
			cmbJugadors->SelectedIndex = 0;

			Button^ btnConfirmar = gcnew Button();
			btnConfirmar->Text = L"Assignar";
			btnConfirmar->DialogResult = System::Windows::Forms::DialogResult::OK;
			btnConfirmar->Location = System::Drawing::Point(520, 170);
			btnConfirmar->Size = System::Drawing::Size(85, 30);

			Button^ btnCancelar = gcnew Button();
			btnCancelar->Text = L"Cancel·lar";
			btnCancelar->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			btnCancelar->Location = System::Drawing::Point(615, 170);
			btnCancelar->Size = System::Drawing::Size(85, 30);

			frmAssignar->Controls->Add(lblPartit);
			frmAssignar->Controls->Add(cmbPartits);
			frmAssignar->Controls->Add(lblJugador);
			frmAssignar->Controls->Add(cmbJugadors);
			frmAssignar->Controls->Add(btnConfirmar);
			frmAssignar->Controls->Add(btnCancelar);
			frmAssignar->AcceptButton = btnConfirmar;
			frmAssignar->CancelButton = btnCancelar;

			if (frmAssignar->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
				if (cmbPartits->SelectedIndex < 0 || cmbJugadors->SelectedIndex < 0) {
					MessageBox::Show(L"Cal seleccionar un partit i un jugador.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				else {
					String^ idPartit = partits[cmbPartits->SelectedIndex]->default["idPartit"];
					String^ idJugador = jugadors[cmbJugadors->SelectedIndex]->default["idJugador"];
					String^ resultat = ctrlAssignar->AssignarJugador(currentUsuariCorreu, idPartit, idJugador);
					MessageBox::Show(resultat, L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en assignar jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnGEAfegirJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarEquip->Visible = false;
		pnlAfegirJugador->Visible = true;
		txtAJCorreu->Text = L"";
		txtAJDorsal->Text = L"";
		txtAJPosicio->Text = L"";
	}

	private: System::Void btnGEEliminarJugador_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsuariTipus == nullptr || currentUsuariTipus->ToLower() != L"capita") {
			MessageBox::Show(L"Només els capitans poden accedir a aquesta funcionalitat.", L"Accés denegat", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (dgvPlantilla->SelectedRows == nullptr || dgvPlantilla->SelectedRows->Count == 0) {
			MessageBox::Show(L"Selecciona un jugador de la plantilla.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		DataGridViewRow^ row = dgvPlantilla->SelectedRows[0];
		String^ idJugador = nullptr;
		if (dgvPlantilla->Columns->Contains("IdJugador") && row->Cells["IdJugador"]->Value != nullptr) {
			idJugador = row->Cells["IdJugador"]->Value->ToString();
		}

		if (String::IsNullOrWhiteSpace(idJugador)) {
			MessageBox::Show(L"No s'ha pogut obtenir l'IdJugador de la fila seleccionada.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		String^ nomJugador = L"";
		if (dgvPlantilla->Columns->Contains("Nom") && row->Cells["Nom"]->Value != nullptr) {
			nomJugador = row->Cells["Nom"]->Value->ToString();
		}

		System::Windows::Forms::DialogResult confirmacio = MessageBox::Show(
			L"Vols eliminar/expulsar el jugador '" + nomJugador + L"' de l'equip?",
			L"Confirmació",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Warning);

		if (confirmacio != System::Windows::Forms::DialogResult::Yes) {
			return;
		}

		try {
			Playcampus::Domini::CtrlEliminarJugador^ ctrlEliminar = gcnew Playcampus::Domini::CtrlEliminarJugador();
			String^ resultat = ctrlEliminar->EliminarJugador(currentUsuariCorreu, idJugador);
			MessageBox::Show(resultat, L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
			dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
           if (dgvPlantilla->Columns->Contains("IdJugador")) {
				dgvPlantilla->Columns["IdJugador"]->Visible = false;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en expulsar el jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnAJConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ correuEstudiant = txtAJCorreu->Text;
		String^ dorsalText = txtAJDorsal->Text;
		String^ posicioText = txtAJPosicio->Text;

		if (String::IsNullOrWhiteSpace(correuEstudiant) || String::IsNullOrWhiteSpace(dorsalText)) {
			MessageBox::Show(L"Si us plau, omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int dorsal = 0;
		if (!Int32::TryParse(dorsalText, dorsal) || dorsal < 0) {
			MessageBox::Show(L"El dorsal ha de ser un número enter positiu.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlAfegirJugador^ ctrlAfegir = gcnew Playcampus::Domini::CtrlAfegirJugador();
			String^ resultat = ctrlAfegir->AfegirJugador(correuEstudiant, dorsal, posicioText, currentUsuariCorreu);

			MessageBox::Show(resultat, L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

          Playcampus::Domini::CtrlVeurePlantilla^ ctrlVP = gcnew Playcampus::Domini::CtrlVeurePlantilla();
			dgvPlantilla->DataSource = ctrlVP->ObtenirPlantillaEquip(currentUsuariCorreu);
			if (dgvPlantilla->Columns->Contains("IdJugador")) {
				dgvPlantilla->Columns["IdJugador"]->Visible = false;
			}

			pnlAfegirJugador->Visible = false;
			pnlGestionarEquip->Visible = true;
			txtAJCorreu->Text = L"";
			txtAJDorsal->Text = L"";
			txtAJPosicio->Text = L"";
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al afegir jugador: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnAJCancellar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlAfegirJugador->Visible = false;
		pnlGestionarEquip->Visible = true;
		txtAJCorreu->Text = L"";
		txtAJDorsal->Text = L"";
		txtAJPosicio->Text = L"";
	}

	private: System::Void btnEETornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEnregistrarEquip->Visible = false;
		pnlMain->Visible = true;
	}

	private: System::Void btnEEEnregistrar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nom = txtEENom->Text;
		DateTime data = dtpEEData->Value;
		String^ esport = cmbEEEscollirEsport->Text;

		if (String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(esport)) {
			MessageBox::Show(L"Omple tots els camps.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			Playcampus::Domini::CtrlEnregistrarEquip^ ctrlEE = gcnew Playcampus::Domini::CtrlEnregistrarEquip();
			String^ idEquip = "E-" + Guid::NewGuid().ToString()->Substring(0, 8);
			ctrlEE->EnregistrarEquip(idEquip, nom, data, esport, currentUsuariTipus, currentUsuariCorreu);
			MessageBox::Show(L"Equip enregistrat correctament!", L"Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			btnEnregistrarEquip->Text = L"Gestionar Equip";

			pnlEnregistrarEquip->Visible = false;
			pnlMain->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al enregistrar equip: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	


	private: System::Void btnGLEsborrarPartit_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlGestionarLliga->Visible = false;
		pnlEsborrarPartit->Visible = true;
		CarregarTemporadesEsborrar();
	}

	private: System::Void btnEPTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEsborrarPartit->Visible = false;
		pnlGestionarLliga->Visible = true;
	}

		   // 1. CARREGAR TEMPORADES USANT EL CONTROLADOR DOMINI
	private: void CarregarTemporadesEsborrar() {
		cmbEPTemporades->Items->Clear();
		epTemporadaIds->Clear();
		cmbEPJornades->Items->Clear();
		epJornadaIds->Clear();
		cmbEPPartits->Items->Clear();
		epPartitIds->Clear();

		try {
			Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
			auto temporades = ctrl->ObtenirTemporadesAdmin(currentUsuariCorreu);

			for each(auto dict in temporades) {
				String^ display = dict["dataInici"] + L" a " + dict["dataFi"] + L" [" + dict["estat"] + L"]";
				cmbEPTemporades->Items->Add(display);
				epTemporadaIds->Add(dict["idTemporada"]);
			}

			if (cmbEPTemporades->Items->Count > 0) cmbEPTemporades->SelectedIndex = 0;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar temporades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void btnEstLliga_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiques->Visible = false;
		pnlEstadistiquesLligaDetail->Visible = true;
		pnlEstadistiquesLligaDetail->BringToFront();

		Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
		String^ idLligaFound = nullptr;

		// 1. Comprovem si és un Administrador fent servir la teva variable de sessió
		if (currentUsuariTipus != nullptr && currentUsuariTipus == "Administrador") {
			lblEstLligaBuscar->Visible = false;
			txtEstLligaBuscar->Visible = false;
			btnEstLligaExecutarCerca->Visible = false;

			// Passem el correu (o el que tinguis guardat) per buscar la seva lliga
			idLligaFound = ctrl->ObtenirIdLligaAdmin(currentUsuariCorreu);
		}
		// 2. Comprovem si és un Capità
		else if (currentUsuariTipus != nullptr && currentUsuariTipus == "Capita") {
			lblEstLligaBuscar->Visible = false;
			txtEstLligaBuscar->Visible = false;
			btnEstLligaExecutarCerca->Visible = false;

			// Passem el correu per buscar la lliga del seu equip
			idLligaFound = ctrl->ObtenirIdLligaCapita(currentUsuariCorreu);
		}
		// 3. Si és Estudiant (o no hi ha sessió)
		else {
			lblEstLligaBuscar->Visible = true;
			txtEstLligaBuscar->Visible = true;
			btnEstLligaExecutarCerca->Visible = true;

			lblEstLligaTemporada->Visible = false;
			cmbEstLligaTemporades->Visible = false;
			dgvEstLligaClassificacio->Visible = false;

			return; // Parem aquí perquè l'estudiant ha de teclejar i buscar manualment
		}

		// Si hem arribat aquí (sent Admin o Capità), carreguem la taula automàticament
		if (idLligaFound != nullptr) {
			currentIdLligaEstadistiques = idLligaFound;
			CarregarDadesLligaDirecte(ctrl, idLligaFound);
		}
		else {
			MessageBox::Show(L"No s'ha trobat cap lliga vinculada al teu compte.", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	private: void CarregarDadesLligaDirecte(Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl, String^ idLliga) {
		DataTable^ dtTemp = ctrl->ObtenirTemporadesLliga(idLliga);
		cmbEstLligaTemporades->Items->Clear();
       for (int i = 0; i < dtTemp->Rows->Count; i++) {
			DataRow^ row = dtTemp->Rows[i];
			cmbEstLligaTemporades->Items->Add(row["NomTemporada"]->ToString());
		}

		if (cmbEstLligaTemporades->Items->Count > 0) {
			cmbEstLligaTemporades->SelectedIndex = 0;
			cmbEstLligaTemporades->Visible = true;
			lblEstLligaTemporada->Visible = true;
		}

		dgvEstLligaClassificacio->DataSource = ctrl->ObtenirClassificacioLliga(idLliga);
		dgvEstLligaClassificacio->Visible = true;
	}



private: System::Void btnEstLligaExecutarCerca_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ nom = txtEstLligaBuscar->Text->Trim();
	if (nom == "") return;

	Playcampus::Domini::CtrlVeureEstadistiquesLliga^ ctrl = gcnew Playcampus::Domini::CtrlVeureEstadistiquesLliga();
	String^ id = ctrl->ObtenirIdLligaPerNom(nom);

	if (id != nullptr) {
		currentIdLligaEstadistiques = id;
		CarregarDadesLligaDirecte(ctrl, id);
	}
	else {
		MessageBox::Show(L"Lliga no trobada.");
	}
}
		   // 2. SELECCIONAR TEMPORADA -> JORNADES 
	private: System::Void cmbEPTemporades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		cmbEPJornades->Items->Clear();
		epJornadaIds->Clear();
		cmbEPPartits->Items->Clear();
		epPartitIds->Clear();

		if (cmbEPTemporades->SelectedIndex >= 0) {
			String^ idTemporadaStr = epTemporadaIds[cmbEPTemporades->SelectedIndex];

			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				auto jornades = ctrl->ObtenirJornadesPerTemporada(idTemporadaStr);

				for each(auto dict in jornades) {
					// AFEGIM dataFi i estat per Jornada
					String^ display = L"Jornada " + dict["numero"] + L" | " + dict["dataInici"] + L" a " + dict["dataFi"] + L" [" + dict["estat"] + L"]";
					cmbEPJornades->Items->Add(display);
					epJornadaIds->Add(dict["idJornada"]);
				}

				if (cmbEPJornades->Items->Count > 0) cmbEPJornades->SelectedIndex = 0;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar jornades: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	private: System::Void btnEstLligaTornar_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlEstadistiquesLligaDetail->Visible = false;
		pnlEstadistiques->Visible = true;
	}

		   // 3. SELECCIONAR JORNADA -> PARTITS 
	private: System::Void cmbEPJornades_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		cmbEPPartits->Items->Clear();
		epPartitIds->Clear();

		if (cmbEPJornades->SelectedIndex >= 0) {
			String^ idJornadaStr = epJornadaIds[cmbEPJornades->SelectedIndex];

			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				auto partits = ctrl->ObtenirPartitsPerJornada(idJornadaStr);

				for each(auto dict in partits) {
					String^ ubicacio = String::IsNullOrWhiteSpace(dict["ubicacio"]) ? L"Sense ubi" : dict["ubicacio"];
					// AFEGIM Els noms dels equips: local vs visitant
					String^ display = dict["dataHora"] + L" | " + dict["equipLocal"] + L" vs " + dict["equipVisitant"] + L" (Ubi: " + ubicacio + L") [" + dict["estat"] + L"]";
					cmbEPPartits->Items->Add(display);
					epPartitIds->Add(dict["idPartit"]);
				}

				if (cmbEPPartits->Items->Count > 0) cmbEPPartits->SelectedIndex = 0;
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Error al carregar partits: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}

		   // 4. ELIMINAR EL PARTIT A TRAVES DEL CONTROLADOR
	private: System::Void btnEPEsborrarFinal_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cmbEPPartits->SelectedIndex < 0) {
			MessageBox::Show(L"Si us plau, selecciona una temporada, una jornada i finalment un partit per a esborrar.", L"Avís", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		String^ idPartit = epPartitIds[cmbEPPartits->SelectedIndex];
		String^ displayPartit = cmbEPPartits->SelectedItem->ToString();

		System::Windows::Forms::DialogResult confirm = MessageBox::Show(
			L"Estàs segur d'eliminar definitivament el partit: \n\n" + displayPartit + L"?",
			L"Confirmació de Borrat",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Exclamation);

		if (confirm == System::Windows::Forms::DialogResult::Yes) {
			try {
				Playcampus::Domini::CtrlEsborrarPartit^ ctrl = gcnew Playcampus::Domini::CtrlEsborrarPartit();
				ctrl->EsborrarPartit(idPartit);

				MessageBox::Show(L"Partit eliminat de la Base de Dades correctament.", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);

				// Refresquem el desplegable recarregant la jornada seleccionada en comptes de tancar 
				cmbEPJornades_SelectedIndexChanged(nullptr, nullptr);
			}
			catch (Exception^ ex) {
				MessageBox::Show(L"Hi ha hagut una fallada: " + ex->Message, L"Error Crític", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
		   // --- GESTIÓ DEL CAPITÀ ---
	private: System::Void btnGestionarConvocatoria_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlMain->Visible = false;
		pnlConvocatoria->Visible = true;
		pnlConvocatoria->BringToFront();
		CarregarPartitsConvocatoria();
		Form1_Resize(nullptr, nullptr);
	}

	private: System::Void btnTornarConvocatoria_Click(System::Object^ sender, System::EventArgs^ e) {
		pnlConvocatoria->Visible = false;
		pnlMain->Visible = true;
	}

	private: System::Void CarregarPartitsConvocatoria() {
		try {
			cbPartitsConvocatoria->Items->Clear();
			convocatoriaPartitIds->Clear();

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			auto partits = ctrl->ObtenirPartitsCapita(currentUsuariCorreu);

			if (partits != nullptr && partits->Count > 0) {
				for each (auto p in partits) {
					cbPartitsConvocatoria->Items->Add(p["nomMostrar"]);
					convocatoriaPartitIds->Add(p["id_partit"]);
				}
				cbPartitsConvocatoria->SelectedIndex = 0;
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error: " + ex->Message);
		}
	}

	private: System::Void cbPartitsConvocatoria_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (cbPartitsConvocatoria->SelectedIndex < 0) return;

		try {
			String^ idPartit = convocatoriaPartitIds[cbPartitsConvocatoria->SelectedIndex];

			// Necessitem l'equip del capità
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			String^ idEquip = ctrlInici->ObtenirIdEquipDeCapita(currentUsuariCorreu);

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			auto jugadors = ctrl->ObtenirEstatConvocatoria(idPartit, idEquip);

			dgvConvocatoria->Columns->Clear();
			dgvConvocatoria->Columns->Add("ID", "ID Jugador");
			dgvConvocatoria->Columns->Add("Nom", "Nom");
			dgvConvocatoria->Columns->Add("Pos", "Posició");
			dgvConvocatoria->Columns->Add("Estat", "Estat Convocatòria");
			dgvConvocatoria->Columns->Add("Conf", "Confirmació");

			dgvConvocatoria->Columns["ID"]->Visible = false; // Ocultem l'ID

			if (jugadors != nullptr) {
				for each (auto j in jugadors) {
					dgvConvocatoria->Rows->Add(j["id_jugador"], j["nom"], j["posicio"], j["estat_convocatoria"], j["confirmacio"]);
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error taula: " + ex->Message);
		}
	}

		   // Permet al capità fer clic a un jugador per convocar/desconvocar
	private: System::Void dgvConvocatoria_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->RowIndex < 0) return;

		try {
			String^ idJugador = dgvConvocatoria->Rows[e->RowIndex]->Cells["ID"]->Value->ToString();
			String^ estatActual = dgvConvocatoria->Rows[e->RowIndex]->Cells["Estat"]->Value->ToString();
			String^ idPartit = convocatoriaPartitIds[cbPartitsConvocatoria->SelectedIndex];

			bool nouEstat = (estatActual == "No Convocat"); // Invertim l'estat

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			ctrl->ActualitzarConvocatoria(idPartit, idJugador, nouEstat);

			// Recarreguem la taula
			cbPartitsConvocatoria_SelectedIndexChanged(nullptr, nullptr);
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al canviar estat: " + ex->Message);
		}
	}
		   // --- GESTIÓ DEL JUGADOR (CARTELL) ---
	private: System::Void MostrarAvisJugador(String^ missatge) {
		if (pnlAvisJugador != nullptr) pnlMain->Controls->Remove(pnlAvisJugador);

		pnlAvisJugador = gcnew System::Windows::Forms::Panel();
		// 1. FEM EL PANELL MÉS ALT (Abans era 150, ara 220)
		pnlAvisJugador->Size = System::Drawing::Size(500, 220);
		pnlAvisJugador->BackColor = System::Drawing::Color::LightYellow;
		pnlAvisJugador->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

		// 2. EL POSEM A DALT A L'ESQUERRA (Marge de 20 píxels perquè no toqui la vora)
		pnlAvisJugador->Location = System::Drawing::Point(20, 20);

		System::Windows::Forms::Label^ lblMissatge = gcnew System::Windows::Forms::Label();
		lblMissatge->Text = missatge;
		// 3. FEM L'ESPAI DEL TEXT MÉS GRAN (Abans era 80, ara 140)
		lblMissatge->Size = System::Drawing::Size(480, 140);
		lblMissatge->Location = System::Drawing::Point(10, 10); // Una mica més amunt
		lblMissatge->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		lblMissatge->Font = gcnew System::Drawing::Font("Arial", 11, System::Drawing::FontStyle::Bold);

		System::Windows::Forms::Button^ btnSi = gcnew System::Windows::Forms::Button();
		btnSi->Text = L"Sí, hi aniré";
		btnSi->Size = System::Drawing::Size(100, 35);
		// 4. BAIXEM ELS BOTONS PERQUÈ NO TREPITGIN EL TEXT (Abans Y era 100, ara 160)
		btnSi->Location = System::Drawing::Point(140, 160);
		btnSi->BackColor = System::Drawing::Color::LightGreen;
		btnSi->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnConfirmarSi_Click);

		System::Windows::Forms::Button^ btnNo = gcnew System::Windows::Forms::Button();
		btnNo->Text = L"No puc";
		btnNo->Size = System::Drawing::Size(100, 35);
		// BAIXEM TAMBÉ AQUEST BOTÓ (Y = 160)
		btnNo->Location = System::Drawing::Point(260, 160);
		btnNo->BackColor = System::Drawing::Color::Salmon;
		btnNo->Click += gcnew System::EventHandler(this, &PlayCampusLegacyForm::btnConfirmarNo_Click);

		pnlAvisJugador->Controls->Add(lblMissatge);
		pnlAvisJugador->Controls->Add(btnSi);
		pnlAvisJugador->Controls->Add(btnNo);

		pnlMain->Controls->Add(pnlAvisJugador);
		pnlAvisJugador->BringToFront();
	}

	private: System::Void btnConfirmarSi_Click(System::Object^ sender, System::EventArgs^ e) {
		ProcessarConfirmacio(true);
	}

	private: System::Void btnConfirmarNo_Click(System::Object^ sender, System::EventArgs^ e) {
		ProcessarConfirmacio(false);
	}

	private: System::Void ProcessarConfirmacio(bool assisteix) {
		try {
			Playcampus::Domini::CtrlIniciSessio^ ctrlInici = gcnew Playcampus::Domini::CtrlIniciSessio();
			String^ idJugador = ctrlInici->ObtenirIdUsuari(currentUsuariCorreu); // Necessites aquest mètode

			Playcampus::Domini::CtlrConvocarJugadors^ ctrl = gcnew Playcampus::Domini::CtlrConvocarJugadors();
			ctrl->ConfirmarAssistencia(idPartitPendentConfirmar, idJugador, assisteix);

			MessageBox::Show(L"S'ha guardat la teva resposta correctament.");
			pnlMain->Controls->Remove(pnlAvisJugador); // Amaguem el cartell
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al confirmar: " + ex->Message);
		}
	}

	public:
		// Mètodes de navegació inicial per als formularis separats.
		// No canvien el comportament original de l'aplicació; només permeten obrir una pantalla concreta
		// reutilitzant exactament la mateixa interfície i la mateixa lògica que ja existia.
		void MostrarPantallaIniciInicial() {
			OcultarPantallesPrincipalsTask162();
			this->pnlInici->Visible = true;
			Form1_Resize(nullptr, nullptr);
		}

		void MostrarPantallaLoginInicial() {
			OcultarPantallesPrincipalsTask162();
			this->pnlLogin->Visible = true;
			Form1_Resize(nullptr, nullptr);
		}

		void MostrarPantallaRegistreInicial() {
			OcultarPantallesPrincipalsTask162();
			this->pnlRegister->Visible = true;
			Form1_Resize(nullptr, nullptr);
		}

		void MostrarPantallaMenuPrincipalInicial() {
			OcultarPantallesPrincipalsTask162();
			this->pnlMain->Visible = true;
			Form1_Resize(nullptr, nullptr);
		}

		void MostrarPantallaConsultarInicial() { MostrarPanelInicialTask162(this->pnlConsultar); }
		void MostrarPantallaCrearLligaInicial() { MostrarPanelInicialTask162(this->pnlCrearLliga); }
		void MostrarPantallaGestionarLligaInicial() { MostrarPanelInicialTask162(this->pnlGestionarLliga); }
		void MostrarPantallaCrearPartitInicial() { MostrarPanelInicialTask162(this->pnlCrearPartit); }
		void MostrarPantallaEditarPartitInicial() { MostrarPanelInicialTask162(this->pnlCrearPartit); }
		void MostrarPantallaCrearTemporadaInicial() { MostrarPanelInicialTask162(this->pnlCrearTemporada); }
		void MostrarPantallaCrearJornadaInicial() { MostrarPanelInicialTask162(this->pnlCrearJornada); }
		void MostrarPantallaEsborrarPartitInicial() { MostrarPanelInicialTask162(this->pnlEsborrarPartit); }
		void MostrarPantallaEnregistrarEquipInicial() { MostrarPanelInicialTask162(this->pnlEnregistrarEquip); }
		void MostrarPantallaGestionarEquipInicial() { MostrarPanelInicialTask162(this->pnlGestionarEquip); }
		void MostrarPantallaAfegirJugadorInicial() { MostrarPanelInicialTask162(this->pnlAfegirJugador); }
		void MostrarPantallaAssignarJugadorPartitInicial() { MostrarPanelInicialTask162(this->pnlGestionarEquip); }
		void MostrarPantallaUnirEquipLligaInicial() { MostrarPanelInicialTask162(this->pnlUnirEquipLliga); }
		void MostrarPantallaEstadistiquesInicial() { MostrarPanelInicialTask162(this->pnlEstadistiques); }
		void MostrarPantallaEstadistiquesLligaInicial() { MostrarPanelInicialTask162(this->pnlEstadistiquesLligaDetail); }
		void MostrarPantallaConvocatoriaInicial() { MostrarPanelInicialTask162(this->pnlConvocatoria); }

	private:
		void MostrarPanelInicialTask162(System::Windows::Forms::Panel^ panel) {
			OcultarPantallesPrincipalsTask162();
			if (panel != nullptr) {
				panel->Visible = true;
				panel->BringToFront();
			}
			Form1_Resize(nullptr, nullptr);
		}

		void OcultarPantallesPrincipalsTask162() {
			if (this->pnlInici != nullptr) this->pnlInici->Visible = false;
			if (this->pnlLogin != nullptr) this->pnlLogin->Visible = false;
			if (this->pnlRegister != nullptr) this->pnlRegister->Visible = false;
			if (this->pnlMain != nullptr) this->pnlMain->Visible = false;
			if (this->pnlConsultar != nullptr) this->pnlConsultar->Visible = false;
			if (this->pnlCrearLliga != nullptr) this->pnlCrearLliga->Visible = false;
			if (this->pnlGestionarLliga != nullptr) this->pnlGestionarLliga->Visible = false;
			if (this->pnlCrearPartit != nullptr) this->pnlCrearPartit->Visible = false;
			if (this->pnlCrearTemporada != nullptr) this->pnlCrearTemporada->Visible = false;
			if (this->pnlCrearJornada != nullptr) this->pnlCrearJornada->Visible = false;
			if (this->pnlEnregistrarEquip != nullptr) this->pnlEnregistrarEquip->Visible = false;
			if (this->pnlGestionarEquip != nullptr) this->pnlGestionarEquip->Visible = false;
			if (this->pnlAfegirJugador != nullptr) this->pnlAfegirJugador->Visible = false;
			if (this->pnlUnirEquipLliga != nullptr) this->pnlUnirEquipLliga->Visible = false;
			if (this->pnlEsborrarPartit != nullptr) this->pnlEsborrarPartit->Visible = false;
			if (this->pnlEstadistiques != nullptr) this->pnlEstadistiques->Visible = false;
			if (this->pnlEstadistiquesLligaDetail != nullptr) this->pnlEstadistiquesLligaDetail->Visible = false;
			if (this->pnlConvocatoria != nullptr) this->pnlConvocatoria->Visible = false;
		}

};
}

