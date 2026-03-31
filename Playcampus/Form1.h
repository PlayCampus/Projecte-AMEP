#pragma once
#include "Domini/CtrlIniciSessio.hxx"
#include "Domini/CtrlTancarSessio.hxx"
#include "Domini/CtrlRegistrarUsuari.hxx"
#include "Domini/CtrlCrearLliga.hxx"

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
		Form1(void)
		{
			InitializeComponent();

			pnlInici->Visible = true;
			pnlLogin->Visible = false;
			pnlRegister->Visible = false;
			pnlMain->Visible = false;
			pnlConsultar->Visible = false;

			Form1_Resize(nullptr, nullptr);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
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

		String^ currentUsuariTipus;
		String^ currentUsuariCorreu;

		System::Windows::Forms::Panel^ pnlGestionarLliga;
		System::Windows::Forms::Label^ lblGLTitle;
		System::Windows::Forms::Button^ btnGLAfegirPartit;
		System::Windows::Forms::Button^ btnGLEditarPartit;
		System::Windows::Forms::Button^ btnGLMostrarEquips;
		System::Windows::Forms::Button^ btnGLEsborrarEquip;
		System::Windows::Forms::Button^ btnGLTornar;
		System::Windows::Forms::PictureBox^ picLogoGL;

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
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);

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
			this->btnShowLogin->Click += gcnew System::EventHandler(this, &Form1::btnShowLogin_Click);

			this->btnShowRegister->Text = L"Registrar-se";
			this->btnShowRegister->Location = System::Drawing::Point(100, 160);
			this->btnShowRegister->Size = System::Drawing::Size(200, 40);
			this->btnShowRegister->Click += gcnew System::EventHandler(this, &Form1::btnShowRegister_Click);

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
			this->btnLoginAct->Click += gcnew System::EventHandler(this, &Form1::btnLoginAct_Click);

			this->btnLoginBack->Text = L"Registrar-se";
			this->btnLoginBack->Location = System::Drawing::Point(150, 130);
			this->btnLoginBack->Click += gcnew System::EventHandler(this, &Form1::btnShowRegisterFromLogin_Click);

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
			this->cmbRegTipus->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbRegTipus_SelectedIndexChanged);

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
			this->btnRegAct->Click += gcnew System::EventHandler(this, &Form1::btnRegAct_Click);

			this->btnRegBack->Text = L"Tornar";
			this->btnRegBack->Location = System::Drawing::Point(150, 230);
			this->btnRegBack->Click += gcnew System::EventHandler(this, &Form1::btnBack_Click);

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

			this->btnEstatLligues->Text = L"Estat de les Lligues";
			this->btnEstatLligues->Location = System::Drawing::Point(160, 60);
			this->btnEstatLligues->Size = System::Drawing::Size(130, 40);

			this->btnEstadistiques->Text = L"Estadístiques de partits";
			this->btnEstadistiques->Location = System::Drawing::Point(300, 60);
			this->btnEstadistiques->Size = System::Drawing::Size(130, 40);

			this->btnConsultar->Text = L"Consultar";
			this->btnConsultar->Location = System::Drawing::Point(440, 60);
			this->btnConsultar->Size = System::Drawing::Size(130, 40);
			this->btnConsultar->Click += gcnew System::EventHandler(this, &Form1::btnConsultar_Click);

			this->picImatge->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picImatge->Location = System::Drawing::Point(20, 120);
			this->picImatge->Size = System::Drawing::Size(550, 200);

			this->lblNoticies->Text = L"Noticies Generals";
			this->lblNoticies->Location = System::Drawing::Point(20, 330);
			this->lblNoticies->AutoSize = true;

			this->lstNoticies->Location = System::Drawing::Point(20, 350);
			this->lstNoticies->Size = System::Drawing::Size(550, 80);

			this->btnLogoutMainMenu->Text = L"Tancar Sessió";
			this->btnLogoutMainMenu->Location = System::Drawing::Point(470, 20);
			this->btnLogoutMainMenu->Size = System::Drawing::Size(100, 25);
			this->btnLogoutMainMenu->Click += gcnew System::EventHandler(this, &Form1::btnLogout_Click);

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
			this->btnCrearLligaMainMenu->Click += gcnew System::EventHandler(this, &Form1::btnCrearLligaMainMenu_Click);

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
			this->btnTornarConsultar->Click += gcnew System::EventHandler(this, &Form1::btnTornarConsultar_Click);

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
			this->btnComprovarLliga->Click += gcnew System::EventHandler(this, &Form1::btnComprovarLliga_Click);

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
			this->btnCLGuarda->Click += gcnew System::EventHandler(this, &Form1::btnCLGuarda_Click);

			this->btnCLTornar->Text = L"Tornar";
			this->btnCLTornar->Size = System::Drawing::Size(100, 30);
			this->btnCLTornar->Click += gcnew System::EventHandler(this, &Form1::btnCLTornar_Click);

			// pnlGestionarLliga
			this->pnlGestionarLliga = gcnew System::Windows::Forms::Panel();
			this->lblGLTitle = gcnew System::Windows::Forms::Label();
			this->btnGLAfegirPartit = gcnew System::Windows::Forms::Button();
			this->btnGLEditarPartit = gcnew System::Windows::Forms::Button();
			this->btnGLMostrarEquips = gcnew System::Windows::Forms::Button();
			this->btnGLEsborrarEquip = gcnew System::Windows::Forms::Button();
			this->btnGLTornar = gcnew System::Windows::Forms::Button();
			this->picLogoGL = gcnew System::Windows::Forms::PictureBox();

			this->pnlGestionarLliga->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlGestionarLliga->Visible = false;
			this->pnlGestionarLliga->Controls->Add(this->lblGLTitle);
			this->pnlGestionarLliga->Controls->Add(this->btnGLAfegirPartit);
			this->pnlGestionarLliga->Controls->Add(this->btnGLEditarPartit);
			this->pnlGestionarLliga->Controls->Add(this->btnGLMostrarEquips);
			this->pnlGestionarLliga->Controls->Add(this->btnGLEsborrarEquip);
			this->pnlGestionarLliga->Controls->Add(this->btnGLTornar);
			this->pnlGestionarLliga->Controls->Add(this->picLogoGL);

			this->picLogoGL->ImageLocation = L"imatges\\logo.png";
			this->picLogoGL->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picLogoGL->Size = System::Drawing::Size(150, 150);

			this->lblGLTitle->Text = L"Gestionar Lliga";
			this->lblGLTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Bold);
			this->lblGLTitle->AutoSize = true;

			System::Drawing::Font^ actionBtnFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);

			this->btnGLAfegirPartit->Text = L"Crear partit";
			this->btnGLAfegirPartit->Size = System::Drawing::Size(220, 60);
			this->btnGLAfegirPartit->Font = actionBtnFont;
			this->btnGLAfegirPartit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLAfegirPartit->Click += gcnew System::EventHandler(this, &Form1::btnGL_EnDesenvolupament_Click);

			this->btnGLEditarPartit->Text = L"Editar partit";
			this->btnGLEditarPartit->Size = System::Drawing::Size(220, 60);
			this->btnGLEditarPartit->Font = actionBtnFont;
			this->btnGLEditarPartit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLEditarPartit->Click += gcnew System::EventHandler(this, &Form1::btnGL_EnDesenvolupament_Click);

			this->btnGLMostrarEquips->Text = L"Mostrar equips";
			this->btnGLMostrarEquips->Size = System::Drawing::Size(220, 60);
			this->btnGLMostrarEquips->Font = actionBtnFont;
			this->btnGLMostrarEquips->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLMostrarEquips->Click += gcnew System::EventHandler(this, &Form1::btnGL_EnDesenvolupament_Click);

			this->btnGLEsborrarEquip->Text = L"Esborrar equip";
			this->btnGLEsborrarEquip->Size = System::Drawing::Size(220, 60);
			this->btnGLEsborrarEquip->Font = actionBtnFont;
			this->btnGLEsborrarEquip->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGLEsborrarEquip->Click += gcnew System::EventHandler(this, &Form1::btnGL_EnDesenvolupament_Click);

			this->btnGLTornar->Text = L"Tornar";
			this->btnGLTornar->Size = System::Drawing::Size(100, 30);
			this->btnGLTornar->Click += gcnew System::EventHandler(this, &Form1::btnGLTornar_Click);

			// Form
			this->Controls->Add(this->pnlInici);
			this->Controls->Add(this->pnlLogin);
			this->Controls->Add(this->pnlRegister);
			this->Controls->Add(this->pnlMain);
			this->Controls->Add(this->pnlConsultar);
			this->Controls->Add(this->pnlCrearLliga);
			this->Controls->Add(this->pnlGestionarLliga);

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
			}
		}
#pragma endregion

	private: System::Void Form1_Resize(System::Object^ sender, System::EventArgs^ e) {
		if (this->ClientSize.Width == 0 || this->ClientSize.Height == 0) return;

		int cw = this->ClientSize.Width;
		int ch = this->ClientSize.Height;
		int centerX = cw / 2;
		int centerY = ch / 2;

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

		int totalBtnWidth = 130 * 4 + 20 * 3;
		int startBtnX = centerX - totalBtnWidth / 2;
		this->btnProgPartits->Location = System::Drawing::Point(startBtnX, 80);
		this->btnEstatLligues->Location = System::Drawing::Point(startBtnX + 150, 80);
		this->btnEstadistiques->Location = System::Drawing::Point(startBtnX + 300, 80);
		this->btnConsultar->Location = System::Drawing::Point(startBtnX + 450, 80);
		this->btnCrearLligaMainMenu->Location = System::Drawing::Point(startBtnX + 600, 80);

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

		this->picLogoGL->Location = System::Drawing::Point(centerX - (this->picLogoGL->Width / 2), glStartY - this->picLogoGL->Height - 40);
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
		if (tipus == L"Capita" || tipus == L"Administrador") {
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
				pnlConsultar->Visible = false;
				pnlCrearLliga->Visible = false;
				pnlGestionarLliga->Visible = false;

				if (currentUsuariTipus->ToLower() == "administrador") {
					btnCrearLligaMainMenu->Visible = true;
					Playcampus::Domini::CtrlCrearLliga^ ctrlCrear = gcnew Playcampus::Domini::CtrlCrearLliga();
					if (ctrlCrear->TeLligaActiva(currentUsuariCorreu)) {
						btnCrearLligaMainMenu->Text = L"Gestionar Lliga";
					}
					else {
						btnCrearLligaMainMenu->Text = L"Crear Lliga";
					}
				} else {
					btnCrearLligaMainMenu->Visible = false;
				}

				txtLoginCorreu->Text = "";
				txtLoginPass->Text = "";
			}
			else {
				MessageBox::Show(L"Credencials incorrectes.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error en iniciar sessió: " + ex->Message, L"Error BD", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
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
			// El mètode CrearLliga requereix: idLliga, nom, disciplina, descripcio, estat, contrasenya, tipusUsuari
			// Generem un ID aleatori o utilitzem el nom com a ID base per fer-ho simple.
			String^ idLliga = "L-" + Guid::NewGuid().ToString()->Substring(0, 8);
			
			ctrlCrear->CrearLliga(idLliga, nom, disc, L"Nova Lliga " + nom, L"en_curs", pass, currentUsuariTipus, currentUsuariCorreu);
			MessageBox::Show(L"Lliga creada correctament!", L"Èxit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			
			btnCrearLligaMainMenu->Text = L"Gestionar Lliga";

			pnlCrearLliga->Visible = false;
			pnlMain->Visible = true;
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al crear lliga: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
};
}
