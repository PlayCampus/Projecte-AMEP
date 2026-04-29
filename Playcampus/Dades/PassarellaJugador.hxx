#pragma once
#include <string>

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

namespace Playcampus {
    namespace Dades {
        public ref class PassarellaJugador {
        private:
            String^ connectionString;
            String^ idJugador;
            String^ nom;
            int dorsal;
            String^ posicio;
            DateTime dataNaixement;
            int partitsJugats;
            int anotacions;
            int assistencies;
            int faltesLleus;
            int faltesGreus;
            int minutsJugats;
            String^ idEquip;

        public:
            PassarellaJugador(String^ connStr);
            PassarellaJugador(String^ connStr, String^ id, String^ n, int d, String^ p, DateTime dn);
            PassarellaJugador(String^ connStr, String^ id, String^ n, int d, String^ p, DateTime dn, int pj, int a, int as, int fl, int fg, int mj, String^ ie);

            String^ GetIdJugador();
            String^ GetNom();
            int GetDorsal();
            String^ GetPosicio();
            DateTime GetDataNaixement();
            int GetPartitsJugats();
            int GetAnotacions();
            int GetAssistencies();
            int GetFaltesLleus();
            int GetFaltesGreus();
            int GetMinutsJugats();
            String^ GetIdEquip();

            void SetIdEquip(String^ ie);
            void SetDorsal(int d);

            void Insereix();
            void Modifica();
            void Esborra();
            static PassarellaJugador^ Llegeix(String^ connStr, String^ idJ);
        };
    }
}
