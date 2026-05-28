#include "pch.h"
#include "Form1Layout.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	System::Void Form1::Form1_Resize(System::Object^ sender, System::EventArgs^ e) {
		// Comprobar que no estamos procesando el resize demasiado pronto u ocultos
		if (this->ClientSize.Width == 0 || this->ClientSize.Height == 0) return;

		// Prevenir problemas si el Resize se dispara antes de terminar InitializeComponent
		if (this->lblEPTitle == nullptr || this->btnEPEsborrarFinal == nullptr || this->lblEJTitle == nullptr || this->btnEJEsborrarFinal == nullptr) return;

		int cw = this->ClientSize.Width;
		int ch = this->ClientSize.Height;
		int centerX = cw / 2;
		int centerY = ch / 2;

		// 1. DISSENY DEL MENÚ PRINCIPAL (Botó del Capità)
		int startBtnX = (this->ClientSize.Width - 800) / 2; // Punt de partida centrat

		if (this->btnGestionarConvocatoria != nullptr && pnlMain->Visible) {
			// El posem al costat dels altres botons del capità. Ajusta el '600' i '80' si se superposen.
         this->btnGestionarConvocatoria->Location = System::Drawing::Point(startBtnX + 750, 80);
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
		if (this->pnlAvisJugador != nullptr && this->Controls->Contains(pnlAvisJugador)) {
			// El centrem just al mig de la finestra
			int ax = (this->ClientSize.Width - pnlAvisJugador->Width) / 2;
			int ay = (this->ClientSize.Height - pnlAvisJugador->Height) / 2;
			if (ax < 0) ax = 0;
			if (ay < 0) ay = 0;
			this->pnlAvisJugador->Location = System::Drawing::Point(ax, ay);
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

       // Botons del menú principal: els centrem segons els que estiguin visibles (per tipus d'usuari)
		{
			const int menuBtnY = 80;
			const int menuBtnH = 40;
			const int gap = 15;

         System::Collections::Generic::List<System::Windows::Forms::Button^>^ btns =
				gcnew System::Collections::Generic::List<System::Windows::Forms::Button^>();
			cli::array<System::Windows::Forms::Button^>^ candidates = gcnew cli::array<System::Windows::Forms::Button^>(10) {
				this->btnUnirEquipLliga,
				this->btnEnregistrarEquip,
				this->btnProgPartits,
				this->btnEstatLligues,
				this->btnEstadistiques,
				this->btnConsultar,
				this->btnMenuConsultarTelefons,
				this->btnSeguirLligaMainMenu,
				this->btnCrearLligaMainMenu,
				this->btnGestionarConvocatoria
			};
			for each (auto b in candidates) {
				if (b != nullptr && b->Visible) btns->Add(b);
			}

			int totalW = 0;
			for (int i = 0; i < btns->Count; i++) {
				auto b = btns[i];
				b->Height = menuBtnH;
				totalW += b->Width;
				if (i < btns->Count - 1) totalW += gap;
			}

			int x = System::Math::Max(20, (cw - totalW) / 2);
			for each (auto b in btns) {
				b->Location = System::Drawing::Point(x, menuBtnY);
				x += b->Width + gap;
			}
		}

		int picY = 140;
		int picBottomMargin = 160;
		int picH = System::Math::Max(10, ch - picY - picBottomMargin);
		this->picImatge->Location = System::Drawing::Point(50, picY);
		this->picImatge->Size = System::Drawing::Size(cw - 100, picH);
		if (this->pnlDashboardLliga != nullptr) {
			this->pnlDashboardLliga->Location = this->picImatge->Location;
			this->pnlDashboardLliga->Size = this->picImatge->Size;
			this->pnlDashboardLliga->BringToFront();

			int pad = 12;
			int titleY = pad;
			if (this->lblDashboardLliga != nullptr) {
				this->lblDashboardLliga->Location = System::Drawing::Point(pad, titleY);
			}
			int y = titleY + 30;
			int w = this->pnlDashboardLliga->Width - pad * 2;
			int hTotal = this->pnlDashboardLliga->Height - y - pad;
			int hEach = System::Math::Max(60, (hTotal - 40 * 3) / 3);

			if (this->lblDashboardClassificacio != nullptr) {
				this->lblDashboardClassificacio->Location = System::Drawing::Point(pad, y);
			}
			y += 20;
			if (this->dgvDashboardClassificacio != nullptr) {
				this->dgvDashboardClassificacio->Location = System::Drawing::Point(pad, y);
				this->dgvDashboardClassificacio->Size = System::Drawing::Size(w, hEach);
			}
			y += hEach + 20;

			if (this->lblDashboardProximsPartits != nullptr) {
				this->lblDashboardProximsPartits->Location = System::Drawing::Point(pad, y);
			}
			y += 20;
			if (this->dgvDashboardProximsPartits != nullptr) {
				this->dgvDashboardProximsPartits->Location = System::Drawing::Point(pad, y);
				this->dgvDashboardProximsPartits->Size = System::Drawing::Size(w, hEach);
			}
			y += hEach + 20;

			if (this->lblDashboardUltimsResultats != nullptr) {
				this->lblDashboardUltimsResultats->Location = System::Drawing::Point(pad, y);
			}
			y += 20;
			if (this->dgvDashboardUltimsResultats != nullptr) {
				this->dgvDashboardUltimsResultats->Location = System::Drawing::Point(pad, y);
				this->dgvDashboardUltimsResultats->Size = System::Drawing::Size(w, System::Math::Max(60, this->pnlDashboardLliga->Height - y - pad));
			}
		}

       int dashboardBottom = this->picImatge->Bottom;
		if (this->pnlDashboardLliga != nullptr && this->pnlDashboardLliga->Visible) {
			dashboardBottom = this->pnlDashboardLliga->Bottom;
		}
		int noticiesY = dashboardBottom + 20;
		this->lblNoticies->Location = System::Drawing::Point(50, noticiesY);
		this->lstNoticies->Location = System::Drawing::Point(50, noticiesY + 25);
		this->lstNoticies->Size = System::Drawing::Size(cw - 100, ch - (noticiesY + 25) - 20);

      // --- PANEL CONSULTAR ---
		this->lblConsultarTitle->Location = System::Drawing::Point(centerX - this->lblConsultarTitle->Width / 2, 30);
		this->btnTornarConsultar->Location = System::Drawing::Point(30, 30);
        int quickY = centerY - 110;
		if (quickY < 80) quickY = 80;
		if (this->lblAccesRapidCalendari != nullptr) {
			this->lblAccesRapidCalendari->Location = System::Drawing::Point(centerX - 170, quickY);
		}
		if (this->btnCalendariLligaSeguida != nullptr) {
			this->btnCalendariLligaSeguida->Location = System::Drawing::Point(centerX - 30, quickY - 5);
		}
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

		// --- PANEL ESTADISTIQUES EQUIP ---
		if (this->pnlEstadistiquesEquipDetail != nullptr && this->pnlEstadistiquesEquipDetail->Visible) {
			int eeStartX = centerX - 330;
			if (eeStartX < 40) eeStartX = 40;

			this->btnEstEquipTornar->Location = System::Drawing::Point(30, 30);
			this->lblEstEquipTitle->Location = System::Drawing::Point(centerX - (this->lblEstEquipTitle->Width / 2), 40);

			this->lblEstEquipBuscar->Location = System::Drawing::Point(eeStartX, 105);
			this->txtEstEquipBuscar->Location = System::Drawing::Point(eeStartX + 130, 102);
			this->btnEstEquipCercar->Location = System::Drawing::Point(eeStartX + 405, 99);

			this->lblEstEquipLliga->Location = System::Drawing::Point(eeStartX, 150);
			this->cmbEstEquipLligues->Location = System::Drawing::Point(eeStartX + 130, 147);

			this->lblEstEquipTemporada->Location = System::Drawing::Point(eeStartX, 195);
			this->cmbEstEquipTemporades->Location = System::Drawing::Point(eeStartX + 130, 192);

			int dgvW = cw - 100;
			if (dgvW < 700) dgvW = 700;
			int dgvH = ch - 270;
			if (dgvH < 180) dgvH = 180;
			this->dgvEstEquipStats->Location = System::Drawing::Point(50, 240);
			this->dgvEstEquipStats->Size = System::Drawing::Size(dgvW, dgvH);
		}



		// --- PANEL GESTIONAR LLIGA ---
		this->lblGLTitle->Location = System::Drawing::Point(centerX - this->lblGLTitle->Width / 2, 40);
		this->btnGLTornar->Location = System::Drawing::Point(30, 30);

		int glSpacingX = 25;
		int glSpacingY = 20;
		int btnGLW = this->btnGLAfegirPartit->Width;
		int btnGLH = this->btnGLAfegirPartit->Height;
		int glTotalW = (btnGLW * 3) + (glSpacingX * 2);
		int glStartX = centerX - (glTotalW / 2);
		int glStartY = centerY - 110;
		int glStepY = btnGLH + glSpacingY;

		this->btnGLAfegirPartit->Location = System::Drawing::Point(glStartX, glStartY);
		this->btnGLEditarPartit->Location = System::Drawing::Point(glStartX + btnGLW + glSpacingX, glStartY);
		this->btnGLMostrarEquips->Location = System::Drawing::Point(glStartX + (btnGLW + glSpacingX) * 2, glStartY);
		this->btnGLEsborrarEquip->Location = System::Drawing::Point(glStartX, glStartY + glStepY);
		this->btnGLCrearJornada->Location = System::Drawing::Point(glStartX + btnGLW + glSpacingX, glStartY + glStepY);
		this->btnGLCrearTemporada->Location = System::Drawing::Point(glStartX + (btnGLW + glSpacingX) * 2, glStartY + glStepY);
		this->btnGLEsborrarPartit->Location = System::Drawing::Point(glStartX, glStartY + glStepY * 2);
		if (this->btnGLEsborrarJornada != nullptr) {
			this->btnGLEsborrarJornada->Location = System::Drawing::Point(glStartX + btnGLW + glSpacingX, glStartY + glStepY * 2);
		}
		if (this->btnGLRetirarTemporada != nullptr) {
			this->btnGLRetirarTemporada->Location = System::Drawing::Point(glStartX + (btnGLW + glSpacingX) * 2, glStartY + glStepY * 2);
		}
		if (this->btnGLConsultarTelefons != nullptr) {
			this->btnGLConsultarTelefons->Location = System::Drawing::Point(glStartX + btnGLW + glSpacingX, glStartY + glStepY * 3);
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
		int btnGEH = this->btnGEEsborrarEquip->Height;
		int geSpacingX = 30;
		int geSpacingY = 15;
		int geLeftX = centerX - btnGEW - (geSpacingX / 2);
		int geRightX = centerX + (geSpacingX / 2);
		int geStepY = btnGEH + geSpacingY;

		this->btnGEEsborrarEquip->Location = System::Drawing::Point(geLeftX, geStartY);
		this->btnGEAfegirJugador->Location = System::Drawing::Point(geRightX, geStartY);
		this->btnGEEliminarJugador->Location = System::Drawing::Point(geLeftX, geStartY + geStepY);
		this->btnGEAssignarJugador->Location = System::Drawing::Point(geRightX, geStartY + geStepY);
		this->btnGEEditarJugador->Location = System::Drawing::Point(geLeftX, geStartY + geStepY * 2);
		if (this->btnGEConsultarTelefons != nullptr) {
			this->btnGEConsultarTelefons->Location = System::Drawing::Point(geRightX, geStartY + geStepY * 2);
		}

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

		// --- PANEL ESBORRAR JORNADA ---
		this->lblEJTitle->Location = System::Drawing::Point(centerX - this->lblEJTitle->Width / 2, 30);
		this->btnEJTornar->Location = System::Drawing::Point(30, 30);

		int ejStartX = centerX - 250;
		int ejStartY = centerY - 80;

		this->lblEJTemporada->Location = System::Drawing::Point(ejStartX, ejStartY);
		this->cmbEJTemporades->Location = System::Drawing::Point(ejStartX + 170, ejStartY - 3);

		this->lblEJJornada->Location = System::Drawing::Point(ejStartX, ejStartY + 50);
		this->cmbEJJornades->Location = System::Drawing::Point(ejStartX + 170, ejStartY + 47);

		this->btnEJEsborrarFinal->Location = System::Drawing::Point(centerX - 100, ejStartY + 130);
		this->btnEJEsborrarFinal->Size = System::Drawing::Size(200, 40);

		// --- PANEL AFEGIR JUGADOR ---
		this->lblAJTitle->Location = System::Drawing::Point(centerX - this->lblAJTitle->Width / 2, 30);
		this->btnAJCancellar->Location = System::Drawing::Point(30, 30);

		int ajStartX = centerX - 125;
		int ajStartY = centerY - 50;
		this->lblAJCorreu->Location = System::Drawing::Point(ajStartX, ajStartY);
		this->txtAJCorreu->Location = System::Drawing::Point(ajStartX + 140, ajStartY);
		this->lblAJDorsal->Location = System::Drawing::Point(ajStartX, ajStartY + 40);
		this->txtAJDorsal->Location = System::Drawing::Point(ajStartX + 140, ajStartY + 40);
		this->lblAJDataNaixement->Location = System::Drawing::Point(ajStartX, ajStartY + 80);
		this->dtpAJDataNaixement->Location = System::Drawing::Point(ajStartX + 140, ajStartY + 80);
		this->lblAJPosicio->Location = System::Drawing::Point(ajStartX, ajStartY + 120);
		this->txtAJPosicio->Location = System::Drawing::Point(ajStartX + 140, ajStartY + 120);
		this->btnAJConfirmar->Location = System::Drawing::Point(ajStartX + 20, ajStartY + 170);
		this->btnAJCancellar->Location = System::Drawing::Point(ajStartX + 150, ajStartY + 170);

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
		if (this->btnEstPartit != nullptr && this->btnEstLliga != nullptr) {
			// Posicionamos exactamente debajo del botón de Estadísticas Liga
			this->btnEstPartit->Location = System::Drawing::Point(this->btnEstLliga->Location.X, this->btnEstLliga->Location.Y + this->btnEstLliga->Height + 20);

			// Copiamos el tamaño y la fuente EXACTA del botón anterior
			this->btnEstPartit->Size = this->btnEstLliga->Size;
			this->btnEstPartit->Font = this->btnEstLliga->Font;
		}

		if (this->btnEstJugadors != nullptr && this->btnEstPartit != nullptr) {
			// Posicionamos exactamente debajo del botón de Estadísticas Partit
			this->btnEstJugadors->Location = System::Drawing::Point(this->btnEstPartit->Location.X, this->btnEstPartit->Location.Y + this->btnEstPartit->Height + 20);

			// Copiamos el tamaño y la fuente EXACTA del botón anterior
			this->btnEstJugadors->Size = this->btnEstPartit->Size;
			this->btnEstJugadors->Font = this->btnEstPartit->Font;
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
		// --- PANEL ESTADISTIQUES PARTIT ---
		if (this->pnlEstadistiquesPartitDetail != nullptr && this->pnlEstadistiquesPartitDetail->Visible) {
			this->pnlEstadistiquesPartitDetail->Location = System::Drawing::Point(0, 0);
			this->pnlEstadistiquesPartitDetail->Size = System::Drawing::Size(cw, ch);

			this->btnEstPartitTornar->Location = System::Drawing::Point(30, 30);
			this->lblEstPartitTitle->Location = System::Drawing::Point(centerX - (this->lblEstPartitTitle->Width / 2), 40);

			int estpStartX = centerX - 300;
			int estpStartY = 100;

			this->lblEstPartitLliga->Location = System::Drawing::Point(estpStartX, estpStartY);
			this->cmbEstPartitLligues->Location = System::Drawing::Point(estpStartX + 150, estpStartY - 3);
			this->cmbEstPartitLligues->Size = System::Drawing::Size(200, 25);

			this->lblEstPartitTemporada->Location = System::Drawing::Point(estpStartX, estpStartY + 40);
			this->cmbEstPartitTemporades->Location = System::Drawing::Point(estpStartX + 150, estpStartY + 37);
			this->cmbEstPartitTemporades->Size = System::Drawing::Size(300, 25);

			this->lblEstPartitPartits->Location = System::Drawing::Point(estpStartX, estpStartY + 80);
			this->cmbEstPartitPartits->Location = System::Drawing::Point(estpStartX + 150, estpStartY + 77);
			this->cmbEstPartitPartits->Size = System::Drawing::Size(400, 25);

			this->lblEstPartitResultat->Location = System::Drawing::Point(estpStartX, estpStartY + 120);

			int dgvH = ch - (estpStartY + 160) - 40;
			if (dgvH < 150) dgvH = 150;
			this->dgvEstPartitDetalls->Location = System::Drawing::Point(50, estpStartY + 160);
			this->dgvEstPartitDetalls->Size = System::Drawing::Size(cw - 100, dgvH);
		}

	}

	System::Void Form1::MostrarPantallaEditarPartit() {
		pnlGestionarLliga->Visible = false;
		pnlEditarPartit->Visible = true;
		pnlEditarPartit->BringToFront();

		ConfigurarLabelsEditarPartitSegonsEsport(L"");
		txtResultatLocal->Text = L"";
		txtResultatVisitant->Text = L"";
		cmbEstatPartit->SelectedIndex = -1;
		dgvEstadistiquesJugadors->DataSource = nullptr;
		dgvEstadistiquesJugadors->Columns->Clear();

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

			if (cmbPartitsAEditar->Items->Count > 0) {
				cmbPartitsAEditar->SelectedIndex = 0;
			}
			else {
				MessageBox::Show(L"No s'han trobat partits per editar en aquesta lliga.", L"Informació", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show(L"Error al carregar els partits: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::MostrarPantallaIniciInicial() {
		OcultarPantallesPrincipalsTask162();
		this->pnlInici->Visible = true;
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::MostrarPantallaLoginInicial() {
		OcultarPantallesPrincipalsTask162();
		this->pnlLogin->Visible = true;
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::MostrarPantallaRegistreInicial() {
		OcultarPantallesPrincipalsTask162();
		this->pnlRegister->Visible = true;
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::MostrarPantallaMenuPrincipalInicial() {
		OcultarPantallesPrincipalsTask162();
		this->pnlMain->Visible = true;
		Form1_Resize(nullptr, nullptr);
	}

   void Form1::MostrarPantallaConsultarInicial() {
		MostrarPanelInicialTask162(this->pnlConsultar);
		ActualitzarAccesRapidCalendariLligaSeguida();
	}

	void Form1::MostrarPantallaCrearLligaInicial() { MostrarPanelInicialTask162(this->pnlCrearLliga); }

	void Form1::MostrarPantallaGestionarLligaInicial() { MostrarPanelInicialTask162(this->pnlGestionarLliga); }

	void Form1::MostrarPantallaCrearPartitInicial() { MostrarPanelInicialTask162(this->pnlCrearPartit); }

	void Form1::MostrarPantallaEditarPartitInicial() { MostrarPanelInicialTask162(this->pnlCrearPartit); }

	void Form1::MostrarPantallaCrearTemporadaInicial() { MostrarPanelInicialTask162(this->pnlCrearTemporada); }

	void Form1::MostrarPantallaCrearJornadaInicial() { MostrarPanelInicialTask162(this->pnlCrearJornada); }

	void Form1::MostrarPantallaEsborrarPartitInicial() { MostrarPanelInicialTask162(this->pnlEsborrarPartit); }

	void Form1::MostrarPantallaEnregistrarEquipInicial() { MostrarPanelInicialTask162(this->pnlEnregistrarEquip); }

	void Form1::MostrarPantallaGestionarEquipInicial() { MostrarPanelInicialTask162(this->pnlGestionarEquip); }

	void Form1::MostrarPantallaAfegirJugadorInicial() { MostrarPanelInicialTask162(this->pnlAfegirJugador); }

	void Form1::MostrarPantallaAssignarJugadorPartitInicial() { MostrarPanelInicialTask162(this->pnlGestionarEquip); }

	void Form1::MostrarPantallaUnirEquipLligaInicial() { MostrarPanelInicialTask162(this->pnlUnirEquipLliga); }

	void Form1::MostrarPantallaEstadistiquesInicial() { MostrarPanelInicialTask162(this->pnlEstadistiques); }

	void Form1::MostrarPantallaEstadistiquesLligaInicial() { MostrarPanelInicialTask162(this->pnlEstadistiquesLligaDetail); }

	void Form1::MostrarPantallaConvocatoriaInicial() { MostrarPanelInicialTask162(this->pnlConvocatoria); }

	void Form1::MostrarPanelInicialTask162(System::Windows::Forms::Panel^ panel) {
		OcultarPantallesPrincipalsTask162();
		if (panel != nullptr) {
			panel->Visible = true;
			panel->BringToFront();
		}
		Form1_Resize(nullptr, nullptr);
	}

	void Form1::OcultarPantallesPrincipalsTask162() {
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
		if (this->pnlEsborrarJornada != nullptr) this->pnlEsborrarJornada->Visible = false;
		if (this->pnlEstadistiques != nullptr) this->pnlEstadistiques->Visible = false;
		if (this->pnlEstadistiquesEquipDetail != nullptr) this->pnlEstadistiquesEquipDetail->Visible = false;
		if (this->pnlEstadistiquesLligaDetail != nullptr) this->pnlEstadistiquesLligaDetail->Visible = false;
		if (this->pnlConvocatoria != nullptr) this->pnlConvocatoria->Visible = false;
		
		if (this->pnlEstadistiquesPartitDetail != nullptr) this->pnlEstadistiquesPartitDetail->Visible = false;
	}

}
