#pragma once
#include <string>
#include "Usuari.hxx"

using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class Jugador : public Usuari {
        private:
            int dorsal;
            int edat;
            DateTime antiguitat;
            DateTime dataNaixement;

            // Atributs genèrics d'estadístiques (compatibles amb totes les disciplines)
            int anotacions;    // Futbol: Gols, Bàsquet/Voley: Punts
            int assistencies;
            int faltesLleus;   // Futbol/Voley: Targetes Grogues, Bàsquet: Faltes personals
            int faltesGreus;   // Futbol/Voley: Targetes Vermelles, Bàsquet: Faltes tècniques/expulsió
            int minutsJugats;
            int partitsJugats;
            String^ posicio;

        public:
            Jugador(String^ identificador, String^ nom, String^ contrasenya, DateTime data_registre, String^ correu_electronic, String^ posicio, int dorsal, int edat, DateTime antiguitat, DateTime dataNaixement);

            String^ GetPosicio();
            void SetPosicio(String^ posicio);

            int GetDorsal();
            void SetDorsal(int dorsal);

            int GetEdat();
            void SetEdat(int edat);

            DateTime GetAntiguitat();
            void SetAntiguitat(DateTime antiguitat);

            DateTime GetDataNaixement();
            void SetDataNaixement(DateTime dataNaixement);

            // Getters i Setters Estadístiques
            int GetAnotacions();
            void SetAnotacions(int anotacions);

            int GetAssistencies();
            void SetAssistencies(int assistencies);

            int GetFaltesLleus();
            void SetFaltesLleus(int faltesLleus);

            int GetFaltesGreus();
            void SetFaltesGreus(int faltesGreus);

            int GetMinutsJugats();
            void SetMinutsJugats(int minutsJugats);

            int GetPartitsJugats();
            void SetPartitsJugats(int partitsJugats);

                        // Validacions
                        bool ValidarDorsal();
                        bool ValidarEdat();
                        bool ValidarAntiguitat();
                        bool ValidarDataNaixement();
                        bool ValidarEstadistiques();
                    };
                }
            }
