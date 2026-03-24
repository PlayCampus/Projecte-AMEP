#pragma once
#include "Dades/UsuariTx.hxx"

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
			//
			//TODO: Add the constructor code here
			//
			usuariTx = gcnew Playcampus::Dades::UsuariTx("Server=localhost;Database=playcampus_db;Uid=root;Pwd=;");
			pnlInici->Visible = true;
			pnlLogin->Visible = false;
			pnlRegister->Visible = false;
			pnlMain->Visible = false;
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
		Playcampus::Dades::UsuariTx^ usuariTx;
		System::Windows::Forms::Panel^ pnlInici;
		System::Windows::Forms::Button^ btnShowLogin;
		System::Windows::Forms::Button^ btnShowRegister;

		System::Windows::Forms::Panel^ pnlLogin;
		System::Windows::Forms::Label^ lblLoginUsuari;
		System::Windows::Forms::Label^ lblLoginPass;
		System::Windows::Forms::TextBox^ txtLoginCorreu;
		System::Windows::Forms::TextBox^ txtLoginPass;
		System::Windows::Forms::Button^ btnLoginAct;
		System::Windows::Forms::Button^ btnLoginBack;
		System::Windows::Forms::Label^ lblLoginTitle;

		System::Windows::Forms::Panel^ pnlRegister;
		System::Windows::Forms::Label^ lblRegId;
		System::Windows::Forms::Label^ lblRegNom;
		System::Windows::Forms::Label^ lblRegCorreu;
		System::Windows::Forms::Label^ lblRegPass;
		System::Windows::Forms::TextBox^ txtRegId;
		System::Windows::Forms::TextBox^ txtRegNom;
		System::Windows::Forms::TextBox^ txtRegCorreu;
		System::Windows::Forms::TextBox^ txtRegPass;
		System::Windows::Forms::Button^ btnRegAct;
		System::Windows::Forms::Button^ btnRegBack;
		System::Windows::Forms::Label^ lblRegTitle;

		System::Windows::Forms::Panel^ pnlMain;
		System::Windows::Forms::Label^ lblWelcome;
		System::Windows::Forms::Button^ btnLogout;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(400,350);
			this->Text = L"Playcampus";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			// pnlInici
			this->pnlInici = gcnew System::Windows::Forms::Panel();
			this->btnShowLogin = gcnew System::Windows::Forms::Button();
			this->btnShowRegister = gcnew System::Windows::Forms::Button();
			this->pnlInici->Controls->Add(this->btnShowLogin);
			this->pnlInici->Controls->Add(this->btnShowRegister);
			this->pnlInici->Dock = System::Windows::Forms::DockStyle::Fill;

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

			this->pnlLogin->Controls->Add(this->lblLoginUsuari);
			this->pnlLogin->Controls->Add(this->lblLoginPass);
			this->pnlLogin->Controls->Add(this->txtLoginCorreu);
			this->pnlLogin->Controls->Add(this->txtLoginPass);
			this->pnlLogin->Controls->Add(this->btnLoginAct);
			this->pnlLogin->Controls->Add(this->btnLoginBack);
			this->pnlLogin->Controls->Add(this->lblLoginTitle);
			this->pnlLogin->Dock = System::Windows::Forms::DockStyle::Fill;

			this->lblLoginTitle->Text = L"Iniciar Sessió";
			this->lblLoginTitle->Location = System::Drawing::Point(150, 20);

			this->lblLoginUsuari->Text = L"Usuari";
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
			this->txtRegId = gcnew System::Windows::Forms::TextBox();
			this->txtRegNom = gcnew System::Windows::Forms::TextBox();
			this->txtRegCorreu = gcnew System::Windows::Forms::TextBox();
			this->txtRegPass = gcnew System::Windows::Forms::TextBox();
			this->btnRegAct = gcnew System::Windows::Forms::Button();
			this->btnRegBack = gcnew System::Windows::Forms::Button();
			this->lblRegTitle = gcnew System::Windows::Forms::Label();

			this->pnlRegister->Controls->Add(this->lblRegId);
			this->pnlRegister->Controls->Add(this->lblRegNom);
			this->pnlRegister->Controls->Add(this->lblRegCorreu);
			this->pnlRegister->Controls->Add(this->lblRegPass);
			this->pnlRegister->Controls->Add(this->txtRegId);
			this->pnlRegister->Controls->Add(this->txtRegNom);
			this->pnlRegister->Controls->Add(this->txtRegCorreu);
			this->pnlRegister->Controls->Add(this->txtRegPass);
			this->pnlRegister->Controls->Add(this->btnRegAct);
			this->pnlRegister->Controls->Add(this->btnRegBack);
			this->pnlRegister->Controls->Add(this->lblRegTitle);
			this->pnlRegister->Dock = System::Windows::Forms::DockStyle::Fill;

			this->lblRegTitle->Text = L"Registrar-se";
			this->lblRegTitle->Location = System::Drawing::Point(150, 10);

			this->lblRegId->Text = L"Id";
			this->lblRegId->Location = System::Drawing::Point(50, 40);
			this->lblRegId->Size = System::Drawing::Size(100, 20);

			this->txtRegId->Text = L"";
			this->txtRegId->Location = System::Drawing::Point(150, 40);
			this->txtRegId->Size = System::Drawing::Size(150, 20);

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

			this->btnRegAct->Text = L"Registrar";
			this->btnRegAct->Location = System::Drawing::Point(50, 170);
			this->btnRegAct->Click += gcnew System::EventHandler(this, &Form1::btnRegAct_Click);

			this->btnRegBack->Text = L"Tornar";
			this->btnRegBack->Location = System::Drawing::Point(150, 170);
			this->btnRegBack->Click += gcnew System::EventHandler(this, &Form1::btnBack_Click);

			// pnlMain
			this->pnlMain = gcnew System::Windows::Forms::Panel();
			this->lblWelcome = gcnew System::Windows::Forms::Label();
			this->btnLogout = gcnew System::Windows::Forms::Button();

			this->pnlMain->Controls->Add(this->lblWelcome);
			this->pnlMain->Controls->Add(this->btnLogout);
			this->pnlMain->Dock = System::Windows::Forms::DockStyle::Fill;

			this->lblWelcome->Text = L"Sessió Iniciada!";
			this->lblWelcome->Location = System::Drawing::Point(50, 50);
			this->lblWelcome->Size = System::Drawing::Size(200, 20);

			this->btnLogout->Text = L"Tancar Sessió";
			this->btnLogout->Location = System::Drawing::Point(50, 100);
			this->btnLogout->Click += gcnew System::EventHandler(this, &Form1::btnLogout_Click);

			// Form
			this->Controls->Add(this->pnlInici);
			this->Controls->Add(this->pnlLogin);
			this->Controls->Add(this->pnlRegister);
			this->Controls->Add(this->pnlMain);
		}
#pragma endregion

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

		private: System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlLogin->Visible = false;
			pnlRegister->Visible = false;
			pnlInici->Visible = true;
		}

		private: System::Void btnLoginAct_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ correu = txtLoginCorreu->Text;
			String^ pass = txtLoginPass->Text;

			bool valid = usuariTx->IniciarSessio(correu, pass);
			if (valid) {
				pnlLogin->Visible = false;
				pnlMain->Visible = true;
				txtLoginCorreu->Text = "";
				txtLoginPass->Text = "";
			} else {
				MessageBox::Show("Credencials incorrectes.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		private: System::Void btnRegAct_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ id = txtRegId->Text;
			String^ nom = txtRegNom->Text;
			String^ correu = txtRegCorreu->Text;
			String^ pass = txtRegPass->Text;
			String^ tipus = L"Estudiant";

			if (String::IsNullOrEmpty(id) || String::IsNullOrEmpty(nom) || String::IsNullOrEmpty(correu) || String::IsNullOrEmpty(pass)) {
				MessageBox::Show("Omple tots els camps.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			usuariTx->CrearUsuari(id, nom, pass, DateTime::Now, correu, tipus, "", "");
			MessageBox::Show("Usuari registrat correctament!", "Exit", MessageBoxButtons::OK, MessageBoxIcon::Information);

			pnlRegister->Visible = false;
			pnlInici->Visible = true;

			txtRegId->Text = "";
			txtRegNom->Text = "";
			txtRegCorreu->Text = "";
			txtRegPass->Text = "";
		}

		private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
			pnlMain->Visible = false;
			pnlInici->Visible = true;
		}
	};
}
