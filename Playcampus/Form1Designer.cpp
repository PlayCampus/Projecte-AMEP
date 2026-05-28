#include "pch.h"
#include "Form1Designer.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	void Form1::InitializeComponent(void) {
		this->components = gcnew System::ComponentModel::Container();
		this->Size = System::Drawing::Size(600, 500);
		this->Text = L"Playcampus";
     this->Icon = gcnew System::Drawing::Icon(L"imatges\\logo.ico");
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
		this->pnlInici->Visible = true;

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
		this->pnlLogin->Visible = false;

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
		this->pnlRegister->Visible = false;

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
		this->btnMenuConsultarTelefons = gcnew System::Windows::Forms::Button();
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
		this->pnlMain->Controls->Add(this->btnMenuConsultarTelefons);
		this->pnlMain->Controls->Add(this->picImatge);
		this->pnlMain->Controls->Add(this->lblNoticies);
		this->pnlMain->Controls->Add(this->lstNoticies);
		this->pnlMain->Controls->Add(this->btnLogoutMainMenu);
		this->pnlMain->Controls->Add(this->picLogoMain);
		this->pnlMain->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlMain->Visible = false;

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
		this->btnProgPartits->Click += gcnew System::EventHandler(this, &Form1::btnProgPartits_Click);

		this->btnEstatLligues->Text = L"Estat de les Lligues";
		this->btnEstatLligues->Location = System::Drawing::Point(160, 60);
		this->btnEstatLligues->Size = System::Drawing::Size(130, 40);
		this->btnEstatLligues->Click += gcnew System::EventHandler(this, &Form1::btnEstatLligues_Click);

		this->btnEstadistiques->Text = L"Estadístiques";
		this->btnEstadistiques->Location = System::Drawing::Point(300, 60);
		this->btnEstadistiques->Size = System::Drawing::Size(130, 40);
		this->btnEstadistiques->Click += gcnew System::EventHandler(this, &Form1::btnEstadistiquesMenu_Click);

        this->btnConsultar->Text = L"Consultar calendari";
		this->btnConsultar->Location = System::Drawing::Point(440, 60);
      this->btnConsultar->Size = System::Drawing::Size(160, 40);
		this->btnConsultar->Click += gcnew System::EventHandler(this, &Form1::btnConsultar_Click);

		this->btnMenuConsultarTelefons->Text = L"Consultar telèfons";
		this->btnMenuConsultarTelefons->Location = System::Drawing::Point(610, 60);
		this->btnMenuConsultarTelefons->Size = System::Drawing::Size(160, 40);
		this->btnMenuConsultarTelefons->Visible = false;
		this->btnMenuConsultarTelefons->UseVisualStyleBackColor = true;
		this->btnMenuConsultarTelefons->Click += gcnew System::EventHandler(this, &Form1::btnConsultarTelefons_Click);

		this->picImatge->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->picImatge->Location = System::Drawing::Point(20, 120);
		this->picImatge->Size = System::Drawing::Size(550, 200);

     this->lblNoticies->Text = L"Últims fitxatges";
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
      this->lblAccesRapidCalendari = gcnew System::Windows::Forms::Label();
		this->btnCalendariLligaSeguida = gcnew System::Windows::Forms::Button();
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
       this->pnlConsultar->Controls->Add(this->lblAccesRapidCalendari);
		this->pnlConsultar->Controls->Add(this->btnCalendariLligaSeguida);
		this->pnlConsultar->Controls->Add(this->lblNomLliga);
		this->pnlConsultar->Controls->Add(this->txtNomLliga);
		this->pnlConsultar->Controls->Add(this->btnComprovarLliga);

       this->lblConsultarTitle->Text = L"Consultar calendari";
		this->lblConsultarTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
		this->lblConsultarTitle->AutoSize = true;
		this->lblConsultarTitle->Location = System::Drawing::Point(350, 30);

		this->btnTornarConsultar->Text = L"Tornar";
		this->btnTornarConsultar->Size = System::Drawing::Size(100, 30);
		this->btnTornarConsultar->Location = System::Drawing::Point(30, 30);
		this->btnTornarConsultar->Click += gcnew System::EventHandler(this, &Form1::btnTornarConsultar_Click);

		this->lblAccesRapidCalendari->Text = L"Accés ràpid";
		this->lblAccesRapidCalendari->AutoSize = true;
		this->lblAccesRapidCalendari->Location = System::Drawing::Point(300, 85);
		this->lblAccesRapidCalendari->Visible = false;

		this->btnCalendariLligaSeguida->Text = L"Veure calendari de la lliga seguida";
		this->btnCalendariLligaSeguida->Location = System::Drawing::Point(430, 80);
		this->btnCalendariLligaSeguida->Size = System::Drawing::Size(250, 35);
		this->btnCalendariLligaSeguida->UseVisualStyleBackColor = true;
		this->btnCalendariLligaSeguida->Visible = false;
		this->btnCalendariLligaSeguida->Click += gcnew System::EventHandler(this, &Form1::btnCalendariLligaSeguida_Click);

		this->lblNomLliga->Text = L"Nom de la lliga";
     this->lblNomLliga->Location = System::Drawing::Point(300, 150);
		this->lblNomLliga->Size = System::Drawing::Size(120, 20);
		this->lblNomLliga->Visible = true;

		this->txtNomLliga->Text = L"";
     this->txtNomLliga->Location = System::Drawing::Point(430, 150);
		this->txtNomLliga->Size = System::Drawing::Size(200, 20);
		this->txtNomLliga->Visible = true;

     this->btnComprovarLliga->Text = L"Veure calendari";
		this->btnComprovarLliga->Location = System::Drawing::Point(430, 190);
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



		this->btnEnregistrarEquip = gcnew System::Windows::Forms::Button();
		this->pnlMain->Controls->Add(this->btnEnregistrarEquip);
		this->btnEnregistrarEquip->Text = L"Enregistrar Equip";
		this->btnEnregistrarEquip->Size = System::Drawing::Size(130, 40);
		this->btnEnregistrarEquip->Visible = false;
		this->btnEnregistrarEquip->Click += gcnew System::EventHandler(this, &Form1::btnEnregistrarEquip_Click);

		this->btnUnirEquipLliga = gcnew System::Windows::Forms::Button();
		this->pnlMain->Controls->Add(this->btnUnirEquipLliga);
		this->btnUnirEquipLliga->Text = L"Unir equip a lliga";
		this->btnUnirEquipLliga->Size = System::Drawing::Size(130, 40);
		this->btnUnirEquipLliga->Visible = false;
		this->btnUnirEquipLliga->Click += gcnew System::EventHandler(this, &Form1::btnUnirEquipLligaAct_Click);




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
		this->btnGLConsultarTelefons = gcnew System::Windows::Forms::Button();

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
		this->pnlGestionarLliga->Controls->Add(this->btnGLConsultarTelefons);
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
		this->btnGLAfegirPartit->Click += gcnew System::EventHandler(this, &Form1::btnGLAfegirPartit_Click);

		this->btnGLEditarPartit->Text = L"Editar partit";
		this->btnGLEditarPartit->Size = System::Drawing::Size(220, 60);
		this->btnGLEditarPartit->Font = actionBtnFont;
		this->btnGLEditarPartit->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLEditarPartit->Click += gcnew System::EventHandler(this, &Form1::btnGLEditarPartit_Click);

		this->btnGLMostrarEquips->Text = L"Mostrar equips";
		this->btnGLMostrarEquips->Size = System::Drawing::Size(220, 60);
		this->btnGLMostrarEquips->Font = actionBtnFont;
		this->btnGLMostrarEquips->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLMostrarEquips->Click += gcnew System::EventHandler(this, &Form1::btnGLMostrarEquips_Click);

		this->btnGLEsborrarEquip->Text = L"Esborrar equip";
		this->btnGLEsborrarEquip->Size = System::Drawing::Size(220, 60);
		this->btnGLEsborrarEquip->Font = actionBtnFont;
		this->btnGLEsborrarEquip->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLEsborrarEquip->Click += gcnew System::EventHandler(this, &Form1::btnGLEsborrarEquip_Click);


		this->btnGLCrearJornada->Text = L"Crear jornada";
		this->btnGLCrearJornada->Size = System::Drawing::Size(220, 60);
		this->btnGLCrearJornada->Font = actionBtnFont;
		this->btnGLCrearJornada->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLCrearJornada->Click += gcnew System::EventHandler(this, &Form1::btnGLCrearJornada_Click);


		this->btnGLCrearTemporada->Text = L"Crear temporada";
		this->btnGLCrearTemporada->Size = System::Drawing::Size(220, 60);
		this->btnGLCrearTemporada->Font = actionBtnFont;
		this->btnGLCrearTemporada->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLCrearTemporada->Click += gcnew System::EventHandler(this, &Form1::btnGLCrearTemporada_Click);

		this->btnGLRetirarTemporada = gcnew System::Windows::Forms::Button();
		this->pnlGestionarLliga->Controls->Add(this->btnGLRetirarTemporada);
		this->btnGLRetirarTemporada->Text = L"Retirar temporada";
		this->btnGLRetirarTemporada->Size = System::Drawing::Size(220, 60);
		this->btnGLRetirarTemporada->Font = actionBtnFont;
		this->btnGLRetirarTemporada->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLRetirarTemporada->Click += gcnew System::EventHandler(this, &Form1::btnGLRetirarTemporada_Click);

		this->btnGLConsultarTelefons->Text = L"Consultar telèfons";
		this->btnGLConsultarTelefons->Size = System::Drawing::Size(220, 60);
		this->btnGLConsultarTelefons->Font = actionBtnFont;
		this->btnGLConsultarTelefons->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLConsultarTelefons->UseVisualStyleBackColor = true;
		this->btnGLConsultarTelefons->Click += gcnew System::EventHandler(this, &Form1::btnConsultarTelefons_Click);

		this->btnGLTornar->Text = L"Tornar";
		this->btnGLTornar->Size = System::Drawing::Size(100, 30);
		this->btnGLTornar->Click += gcnew System::EventHandler(this, &Form1::btnGLTornar_Click);

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
		this->btnEstEquips->Click += gcnew System::EventHandler(this, &Form1::btnEstadistiques_Click);

		this->btnEstTornar->Text = L"Tornar";
		this->btnEstTornar->Size = System::Drawing::Size(100, 30);
		this->btnEstTornar->Click += gcnew System::EventHandler(this, &Form1::btnEstTornar_Click);

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
		this->btnGLEsborrarPartit->Click += gcnew System::EventHandler(this, &Form1::btnGLEsborrarPartit_Click);

		this->btnGLEsborrarJornada = gcnew System::Windows::Forms::Button();
		this->pnlGestionarLliga->Controls->Add(this->btnGLEsborrarJornada);
		this->btnGLEsborrarJornada->Text = L"Esborrar jornada";
		this->btnGLEsborrarJornada->Size = System::Drawing::Size(220, 60);
		this->btnGLEsborrarJornada->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
		this->btnGLEsborrarJornada->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLEsborrarJornada->Click += gcnew System::EventHandler(this, &Form1::btnGLEsborrarJornada_Click);

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
		this->lblCPNomLliga->Visible = false;
		this->txtCPNomLliga->Size = System::Drawing::Size(100, 20);
		this->txtCPNomLliga->Visible = false;

		this->btnCPValidarLliga->Text = L"Validar Lliga";
		this->btnCPValidarLliga->Size = System::Drawing::Size(100, 25);
		this->btnCPValidarLliga->Click += gcnew System::EventHandler(this, &Form1::btnCPValidarLliga_Click);
		this->btnCPValidarLliga->Visible = false;

		this->lblCPTemporada->Text = L"Temporada:";
		this->lblCPTemporada->Size = System::Drawing::Size(100, 20);
		this->cmbCPTemporada->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbCPTemporada->Size = System::Drawing::Size(150, 20);
		this->cmbCPTemporada->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbCPTemporada_SelectedIndexChanged);

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
		this->btnCPConfirmar->Click += gcnew System::EventHandler(this, &Form1::btnCPConfirmar_Click);

		this->btnCPCancellar->Text = L"Cancel·lar";
		this->btnCPCancellar->Size = System::Drawing::Size(100, 30);
		this->btnCPCancellar->Click += gcnew System::EventHandler(this, &Form1::btnCPCancellar_Click);

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
		this->lblCTNomLliga->Visible = false;
		this->txtCTNomLliga->Size = System::Drawing::Size(150, 20);
		this->txtCTNomLliga->Visible = false;


		this->lblCTDataInici->Text = L"Data d'Inici:";
		this->dtpCTDataInici->Format = System::Windows::Forms::DateTimePickerFormat::Short;

		this->lblCTDataFi->Text = L"Data de Fi:";
		this->dtpCTDataFi->Format = System::Windows::Forms::DateTimePickerFormat::Short;

		this->btnCTConfirmar->Text = L"Confirmar";
		this->btnCTConfirmar->Click += gcnew System::EventHandler(this, &Form1::btnCTConfirmar_Click);

		this->btnCTCancellar->Text = L"Cancel·lar";
		this->btnCTCancellar->Click += gcnew System::EventHandler(this, &Form1::btnCTCancellar_Click);

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
		this->lblCJNomLliga->Visible = false;
		this->txtCJNomLliga->Visible = false;
		this->btnCJBuscarTemporades->Text = L"Cercar Temporades";
		this->btnCJBuscarTemporades->Click += gcnew System::EventHandler(this, &Form1::btnCJBuscarTemporades_Click);
		this->btnCJBuscarTemporades->Visible = false;

		this->lblCJTemporada->Text = L"Temporada:";
		this->cmbCJTemporada->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

		this->lblCJNumero->Text = L"Número Jornada:";

		this->lblCJDataInici->Text = L"Data d'Inici:";
		this->dtpCJDataInici->Format = System::Windows::Forms::DateTimePickerFormat::Short;

		this->lblCJDataFi->Text = L"Data de Fi:";
		this->dtpCJDataFi->Format = System::Windows::Forms::DateTimePickerFormat::Short;

		this->btnCJConfirmar->Text = L"Confirmar";
		this->btnCJConfirmar->Click += gcnew System::EventHandler(this, &Form1::btnCJConfirmar_Click);

		this->btnCJCancellar->Text = L"Cancel·lar";
		this->btnCJCancellar->Click += gcnew System::EventHandler(this, &Form1::btnCJCancellar_Click);

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
		this->btnEEEnregistrar->Click += gcnew System::EventHandler(this, &Form1::btnEEEnregistrar_Click);

		this->btnEETornar->Text = L"Tornar";
		this->btnEETornar->Size = System::Drawing::Size(100, 30);
		this->btnEETornar->Click += gcnew System::EventHandler(this, &Form1::btnEETornar_Click);

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
			// pnlGestionarEquip
			this->pnlGestionarEquip = gcnew System::Windows::Forms::Panel();
			this->lblGETitle = gcnew System::Windows::Forms::Label();
			this->dgvPlantilla = gcnew System::Windows::Forms::DataGridView();
			this->btnGEEsborrarEquip = gcnew System::Windows::Forms::Button();
			this->btnGEAfegirJugador = gcnew System::Windows::Forms::Button();
			this->btnGEEliminarJugador = gcnew System::Windows::Forms::Button();
			this->btnGEAssignarJugador = gcnew System::Windows::Forms::Button();
			this->btnGEEditarJugador = gcnew System::Windows::Forms::Button();
			this->btnGEConsultarTelefons = gcnew System::Windows::Forms::Button();
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
			this->pnlGestionarEquip->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlGestionarEquip->Visible = false;
			this->pnlGestionarEquip->Controls->Add(this->lblGETitle);
			this->pnlGestionarEquip->Controls->Add(this->dgvPlantilla);
			this->pnlGestionarEquip->Controls->Add(this->btnGEEsborrarEquip);
			this->pnlGestionarEquip->Controls->Add(this->btnGEAfegirJugador);
		 this->pnlGestionarEquip->Controls->Add(this->btnGEEliminarJugador);
			this->pnlGestionarEquip->Controls->Add(this->btnGEAssignarJugador);
			this->pnlGestionarEquip->Controls->Add(this->btnGEEditarJugador);
			this->pnlGestionarEquip->Controls->Add(this->btnGEConsultarTelefons);
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
		this->btnGEEsborrarEquip->Click += gcnew System::EventHandler(this, &Form1::btnGEEsborrarEquip_Click);

		this->btnGEAfegirJugador->Text = L"Afegir jugador";
		this->btnGEAfegirJugador->Size = System::Drawing::Size(220, 60);
		this->btnGEAfegirJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
		this->btnGEAfegirJugador->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGEAfegirJugador->Click += gcnew System::EventHandler(this, &Form1::btnGEAfegirJugador_Click);

		this->btnGEEliminarJugador->Text = L"Eliminar jugador";
		this->btnGEEliminarJugador->Size = System::Drawing::Size(220, 60);
		this->btnGEEliminarJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
		this->btnGEEliminarJugador->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGEEliminarJugador->Click += gcnew System::EventHandler(this, &Form1::btnGEEliminarJugador_Click);

		this->btnGEAssignarJugador->Text = L"Assignar jugador a partit";
		this->btnGEAssignarJugador->Size = System::Drawing::Size(220, 60);
		this->btnGEAssignarJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
		this->btnGEAssignarJugador->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGEAssignarJugador->Click += gcnew System::EventHandler(this, &Form1::btnGEAssignarJugador_Click);

			this->btnGEEditarJugador->Text = L"Editar Jugador";
			this->btnGEEditarJugador->Size = System::Drawing::Size(220, 60);
			this->btnGEEditarJugador->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGEEditarJugador->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGEEditarJugador->Click += gcnew System::EventHandler(this, &Form1::btnGEEditarJugador_Click);

			this->btnGEConsultarTelefons->Text = L"Consultar telèfons";
			this->btnGEConsultarTelefons->Size = System::Drawing::Size(220, 60);
			this->btnGEConsultarTelefons->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
			this->btnGEConsultarTelefons->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGEConsultarTelefons->UseVisualStyleBackColor = true;
			this->btnGEConsultarTelefons->Click += gcnew System::EventHandler(this, &Form1::btnConsultarTelefons_Click);

			this->btnGETornar->Text = L"Tornar";
			this->btnGETornar->Size = System::Drawing::Size(100, 30);
			this->btnGETornar->Click += gcnew System::EventHandler(this, &Form1::btnGETornar_Click);

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
		this->lblAJDataNaixement = gcnew System::Windows::Forms::Label();
		this->dtpAJDataNaixement = gcnew System::Windows::Forms::DateTimePicker();
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
		this->pnlAfegirJugador->Controls->Add(this->lblAJDataNaixement);
		this->pnlAfegirJugador->Controls->Add(this->dtpAJDataNaixement);
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

		this->lblAJDataNaixement->Text = L"Data Naixement:";
		this->lblAJDataNaixement->Size = System::Drawing::Size(120, 20);

		this->dtpAJDataNaixement->Size = System::Drawing::Size(200, 20);
		this->dtpAJDataNaixement->Format = System::Windows::Forms::DateTimePickerFormat::Short;
		this->dtpAJDataNaixement->Value = System::DateTime::Now.AddYears(-20);

		this->btnAJConfirmar->Text = L"Confirmar";
		this->btnAJConfirmar->Size = System::Drawing::Size(100, 30);
		this->btnAJConfirmar->Click += gcnew System::EventHandler(this, &Form1::btnAJConfirmar_Click);

		this->btnAJCancellar->Text = L"Cancel·lar";
		this->btnAJCancellar->Size = System::Drawing::Size(100, 30);
		this->btnAJCancellar->Click += gcnew System::EventHandler(this, &Form1::btnAJCancellar_Click);

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
		this->btnUELComprovar->Click += gcnew System::EventHandler(this, &Form1::btnUELComprovar_Click);

		this->lblUELPass->Text = L"Contrasenya:";
		this->lblUELPass->Size = System::Drawing::Size(100, 20);
		this->lblUELPass->Visible = false;

		this->txtUELPass->UseSystemPasswordChar = true;
		this->txtUELPass->Size = System::Drawing::Size(150, 20);
		this->txtUELPass->Visible = false;

		this->btnUELUnir->Text = L"Unir";
		this->btnUELUnir->Size = System::Drawing::Size(100, 30);
		this->btnUELUnir->Visible = false;
		this->btnUELUnir->Click += gcnew System::EventHandler(this, &Form1::btnUELUnir_Click);

		this->btnUELTornar->Text = L"Tornar";
		this->btnUELTornar->Size = System::Drawing::Size(100, 30);
		this->btnUELTornar->Click += gcnew System::EventHandler(this, &Form1::btnUELTornar_Click);

		this->Controls->Add(this->pnlUnirEquipLliga);

		this->btnGLEsborrarPartit->Text = L"Esborrar partit";
		this->btnGLEsborrarPartit->Size = System::Drawing::Size(220, 60);
		this->btnGLEsborrarPartit->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
		this->btnGLEsborrarPartit->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnGLEsborrarPartit->Click += gcnew System::EventHandler(this, &Form1::btnGLEsborrarPartit_Click);

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
		this->btnEPTornar->Click += gcnew System::EventHandler(this, &Form1::btnEPTornar_Click);

		// Config Temporades
		this->lblEPTemporada->Text = L"Tria una Temporada:";
		this->lblEPTemporada->AutoSize = true;
		this->cmbEPTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEPTemporades->Size = System::Drawing::Size(450, 24);
		this->cmbEPTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEPTemporades_SelectedIndexChanged);

		// Config Jornades
		this->lblEPJornada->Text = L"Tria una Jornada:";
		this->lblEPJornada->AutoSize = true;
		this->cmbEPJornades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEPJornades->Size = System::Drawing::Size(450, 24);
		this->cmbEPJornades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEPJornades_SelectedIndexChanged);

		// Config Partits
		this->lblEPPartit->Text = L"Tria el Partit a esborrar:";
		this->lblEPPartit->AutoSize = true;
		this->cmbEPPartits->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEPPartits->Size = System::Drawing::Size(550, 24);

		this->btnEPEsborrarFinal->Text = L"Esborrar Partit Seleccionat";
		this->btnEPEsborrarFinal->BackColor = System::Drawing::Color::Red;
		this->btnEPEsborrarFinal->ForeColor = System::Drawing::Color::White;
		this->btnEPEsborrarFinal->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold);
		this->btnEPEsborrarFinal->Click += gcnew System::EventHandler(this, &Form1::btnEPEsborrarFinal_Click);

		this->Controls->Add(this->pnlEsborrarPartit);

		// pnlEsborrarJornada
		this->pnlEsborrarJornada = gcnew System::Windows::Forms::Panel();
		this->lblEJTitle = gcnew System::Windows::Forms::Label();
		this->btnEJTornar = gcnew System::Windows::Forms::Button();
		this->lblEJTemporada = gcnew System::Windows::Forms::Label();
		this->cmbEJTemporades = gcnew System::Windows::Forms::ComboBox();
		this->ejTemporadaIds = gcnew System::Collections::Generic::List<String^>();
		this->lblEJJornada = gcnew System::Windows::Forms::Label();
		this->cmbEJJornades = gcnew System::Windows::Forms::ComboBox();
		this->ejJornadaIds = gcnew System::Collections::Generic::List<String^>();
		this->btnEJEsborrarFinal = gcnew System::Windows::Forms::Button();

		this->pnlEsborrarJornada->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlEsborrarJornada->Visible = false;
		this->pnlEsborrarJornada->Controls->Add(this->lblEJTitle);
		this->pnlEsborrarJornada->Controls->Add(this->btnEJTornar);
		this->pnlEsborrarJornada->Controls->Add(this->lblEJTemporada);
		this->pnlEsborrarJornada->Controls->Add(this->cmbEJTemporades);
		this->pnlEsborrarJornada->Controls->Add(this->lblEJJornada);
		this->pnlEsborrarJornada->Controls->Add(this->cmbEJJornades);
		this->pnlEsborrarJornada->Controls->Add(this->btnEJEsborrarFinal);

		this->lblEJTitle->Text = L"Esborrar Jornada - Selecció";
		this->lblEJTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold);
		this->lblEJTitle->AutoSize = true;

		this->btnEJTornar->Text = L"Tornar";
		this->btnEJTornar->Click += gcnew System::EventHandler(this, &Form1::btnEJTornar_Click);

		this->lblEJTemporada->Text = L"Tria una Temporada:";
		this->lblEJTemporada->AutoSize = true;
		this->cmbEJTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEJTemporades->Size = System::Drawing::Size(450, 24);
		this->cmbEJTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEJTemporades_SelectedIndexChanged);

		this->lblEJJornada->Text = L"Tria la Jornada a esborrar:";
		this->lblEJJornada->AutoSize = true;
		this->cmbEJJornades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEJJornades->Size = System::Drawing::Size(450, 24);

		this->btnEJEsborrarFinal->Text = L"Esborrar Jornada";
		this->btnEJEsborrarFinal->BackColor = System::Drawing::Color::Red;
		this->btnEJEsborrarFinal->ForeColor = System::Drawing::Color::White;
		this->btnEJEsborrarFinal->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold);
		this->btnEJEsborrarFinal->Click += gcnew System::EventHandler(this, &Form1::btnEJEsborrarFinal_Click);

		this->Controls->Add(this->pnlEsborrarJornada);

		// Panel detallat d'estadístiques d'equips
		this->pnlEstadistiquesEquipDetail = gcnew System::Windows::Forms::Panel();
		this->lblEstEquipTitle = gcnew System::Windows::Forms::Label();
		this->lblEstEquipBuscar = gcnew System::Windows::Forms::Label();
		this->txtEstEquipBuscar = gcnew System::Windows::Forms::TextBox();
		this->btnEstEquipCercar = gcnew System::Windows::Forms::Button();
		this->lblEstEquipLliga = gcnew System::Windows::Forms::Label();
		this->cmbEstEquipLligues = gcnew System::Windows::Forms::ComboBox();
		this->lblEstEquipTemporada = gcnew System::Windows::Forms::Label();
		this->cmbEstEquipTemporades = gcnew System::Windows::Forms::ComboBox();
		this->dgvEstEquipStats = gcnew System::Windows::Forms::DataGridView();
		this->btnEstEquipTornar = gcnew System::Windows::Forms::Button();
		this->estEquipLligaIds = gcnew System::Collections::Generic::List<String^>();
		this->estEquipTemporadaIds = gcnew System::Collections::Generic::List<String^>();

		this->pnlEstadistiquesEquipDetail->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlEstadistiquesEquipDetail->Visible = false;
		this->pnlEstadistiquesEquipDetail->BackColor = System::Drawing::Color::White;

		this->lblEstEquipTitle->Text = L"Estadístiques d'equip";
		this->lblEstEquipTitle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.0F, System::Drawing::FontStyle::Bold);
		this->lblEstEquipTitle->AutoSize = true;

		this->lblEstEquipBuscar->Text = L"Nom de l'equip:";
		this->lblEstEquipBuscar->AutoSize = true;

		this->txtEstEquipBuscar->Size = System::Drawing::Size(260, 22);

		this->btnEstEquipCercar->Text = L"Cercar";
		this->btnEstEquipCercar->Size = System::Drawing::Size(90, 28);
		this->btnEstEquipCercar->Click += gcnew System::EventHandler(this, &Form1::btnEstEquipCercar_Click);

		this->lblEstEquipLliga->Text = L"Lliga:";
		this->lblEstEquipLliga->AutoSize = true;
		this->lblEstEquipLliga->Visible = false;

		this->cmbEstEquipLligues->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstEquipLligues->Size = System::Drawing::Size(300, 24);
		this->cmbEstEquipLligues->Visible = false;
		this->cmbEstEquipLligues->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstEquipLligues_SelectedIndexChanged);

		this->lblEstEquipTemporada->Text = L"Temporada:";
		this->lblEstEquipTemporada->AutoSize = true;
		this->lblEstEquipTemporada->Visible = false;

		this->cmbEstEquipTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstEquipTemporades->Size = System::Drawing::Size(300, 24);
		this->cmbEstEquipTemporades->Visible = false;
		this->cmbEstEquipTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstEquipTemporades_SelectedIndexChanged);

		this->dgvEstEquipStats->Visible = false;
		this->dgvEstEquipStats->AllowUserToAddRows = false;
		this->dgvEstEquipStats->ReadOnly = true;
		this->dgvEstEquipStats->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dgvEstEquipStats->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
		this->dgvEstEquipStats->BackgroundColor = System::Drawing::Color::White;

		this->btnEstEquipTornar->Text = L"Tornar";
		this->btnEstEquipTornar->Size = System::Drawing::Size(100, 30);
		this->btnEstEquipTornar->Click += gcnew System::EventHandler(this, &Form1::btnEstEquipTornar_Click);

		this->pnlEstadistiquesEquipDetail->Controls->Add(this->lblEstEquipTitle);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->lblEstEquipBuscar);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->txtEstEquipBuscar);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->btnEstEquipCercar);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->lblEstEquipLliga);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->cmbEstEquipLligues);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->lblEstEquipTemporada);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->cmbEstEquipTemporades);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->dgvEstEquipStats);
		this->pnlEstadistiquesEquipDetail->Controls->Add(this->btnEstEquipTornar);
		this->Controls->Add(this->pnlEstadistiquesEquipDetail);

		this->btnEstLliga = gcnew System::Windows::Forms::Button();
		this->btnEstLliga->Text = L"Estadístiques Lliga";
		this->btnEstLliga->Size = System::Drawing::Size(220, 60);
		this->btnEstLliga->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular);
		this->btnEstLliga->Cursor = System::Windows::Forms::Cursors::Hand;

		// Posición inicial fija
		this->btnEstLliga->Location = System::Drawing::Point(190, 230);

		this->btnEstLliga->Click += gcnew System::EventHandler(this, &Form1::btnEstLliga_Click);
		this->pnlEstadistiques->Controls->Add(this->btnEstLliga);

		// 2. Panel de detalle de estadísticas de liga
		this->pnlEstadistiquesLligaDetail = gcnew System::Windows::Forms::Panel();
		this->pnlEstadistiquesLligaDetail->Dock = System::Windows::Forms::DockStyle::Fill;
		this->pnlEstadistiquesLligaDetail->Visible = false;
		this->pnlEstadistiquesLligaDetail->BackColor = System::Drawing::Color::White;

		this->estLligaIds = gcnew System::Collections::Generic::List<String^>();
		this->estLligaTemporadaIds = gcnew System::Collections::Generic::List<String^>();

		this->lblEstLligaInfo = gcnew System::Windows::Forms::Label();
		this->lblEstLligaInfo->Visible = false;

		this->lblEstLligaBuscar = gcnew System::Windows::Forms::Label();
		this->lblEstLligaBuscar->Text = L"Cercar lliga:";
		this->lblEstLligaBuscar->Location = System::Drawing::Point(50, 25);
		this->lblEstLligaBuscar->AutoSize = true;

		this->txtEstLligaBuscar = gcnew System::Windows::Forms::TextBox();
		this->txtEstLligaBuscar->Location = System::Drawing::Point(170, 22);
		this->txtEstLligaBuscar->Size = System::Drawing::Size(230, 20);

		this->btnEstLligaExecutarCerca = gcnew System::Windows::Forms::Button();
		this->btnEstLligaExecutarCerca->Text = L"Cercar";
		this->btnEstLligaExecutarCerca->Location = System::Drawing::Point(415, 20);
		this->btnEstLligaExecutarCerca->Size = System::Drawing::Size(90, 26);
		this->btnEstLligaExecutarCerca->Click += gcnew System::EventHandler(this, &Form1::btnEstLligaExecutarCerca_Click);

		this->lblEstLligaSeleccionar = gcnew System::Windows::Forms::Label();
		this->lblEstLligaSeleccionar->Text = L"Selecciona una lliga:";
		this->lblEstLligaSeleccionar->Location = System::Drawing::Point(50, 65);
		this->lblEstLligaSeleccionar->AutoSize = true;

		this->cmbEstLligaLligues = gcnew System::Windows::Forms::ComboBox();
		this->cmbEstLligaLligues->Location = System::Drawing::Point(170, 62);
		this->cmbEstLligaLligues->Size = System::Drawing::Size(335, 24);
		this->cmbEstLligaLligues->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstLligaLligues->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstLligaLligues_SelectedIndexChanged);

		this->lblEstLligaTemporada = gcnew System::Windows::Forms::Label();
		this->lblEstLligaTemporada->Text = L"Temporada:";
		this->lblEstLligaTemporada->Location = System::Drawing::Point(50, 105);
		this->lblEstLligaTemporada->AutoSize = true;
		this->lblEstLligaTemporada->Visible = false;

		this->cmbEstLligaTemporades = gcnew System::Windows::Forms::ComboBox();
		this->cmbEstLligaTemporades->Location = System::Drawing::Point(170, 102);
		this->cmbEstLligaTemporades->Size = System::Drawing::Size(335, 24);
		this->cmbEstLligaTemporades->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstLligaTemporades->Visible = false;
		this->cmbEstLligaTemporades->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstLligaTemporades_SelectedIndexChanged);

		this->dgvEstLligaClassificacio = gcnew System::Windows::Forms::DataGridView();
		this->dgvEstLligaClassificacio->Location = System::Drawing::Point(50, 145);
		this->dgvEstLligaClassificacio->Size = System::Drawing::Size(760, 290);
		this->dgvEstLligaClassificacio->Visible = false;
		this->dgvEstLligaClassificacio->AllowUserToAddRows = false;
		this->dgvEstLligaClassificacio->ReadOnly = true;
		this->dgvEstLligaClassificacio->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dgvEstLligaClassificacio->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

		this->btnEstLligaTornar = gcnew System::Windows::Forms::Button();
		this->btnEstLligaTornar->Text = L"<- Tornar";
		this->btnEstLligaTornar->Location = System::Drawing::Point(50, 450);
		this->btnEstLligaTornar->Size = System::Drawing::Size(100, 30);
		this->btnEstLligaTornar->Click += gcnew System::EventHandler(this, &Form1::btnEstLligaTornar_Click);

		this->pnlEstadistiquesLligaDetail->Controls->Add(this->lblEstLligaBuscar);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->txtEstLligaBuscar);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->btnEstLligaExecutarCerca);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->lblEstLligaSeleccionar);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->cmbEstLligaLligues);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->lblEstLligaTemporada);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->cmbEstLligaTemporades);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->dgvEstLligaClassificacio);
		this->pnlEstadistiquesLligaDetail->Controls->Add(this->btnEstLligaTornar);

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
		this->cmbPartitsAEditar->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbPartitsAEditar_SelectedIndexChanged);

		// Resultats i Estat
		this->lblResultatLocal->Text = L"Marcador local:";
		this->txtResultatLocal->Size = System::Drawing::Size(50, 20);
		this->lblResultatVisitant->Text = L"Marcador visitant:";
		this->txtResultatVisitant->Size = System::Drawing::Size(50, 20);
		this->lblEstatPartit->Text = L"Estat:";
		this->cmbEstatPartit->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbEstatPartit->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Pendent", L"En joc", L"Finalitzat", L"Aplaçat", L"Cancel·lat" });
		this->cmbEstatPartit->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cmbEstatPartit_SelectedIndexChanged);

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
		this->btnGuardarEstadistiques->Click += gcnew System::EventHandler(this, &Form1::btnGuardarEstadistiques_Click);
		this->btnTornarEditarPartit->Text = L"Tornar";
		this->btnTornarEditarPartit->Click += gcnew System::EventHandler(this, &Form1::btnTornarEditarPartit_Click);

		this->Controls->Add(this->pnlEditarPartit);
		this->pnlEditarPartit->ResumeLayout(false);
		this->pnlEditarPartit->PerformLayout();
		this->ResumeLayout(false);

	}

}
