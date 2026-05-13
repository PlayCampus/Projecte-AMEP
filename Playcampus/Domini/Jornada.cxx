#include "pch.h"
#include "Jornada.hxx"

namespace Playcampus {
    namespace Domini {
        Jornada::Jornada(String^ idJornada, int numero, DateTime dataInici, DateTime dataFi) {
            this->idJornada = idJornada;
            this->numero = numero;
            this->dataInici = dataInici;
            this->dataFi = dataFi;
        }

        String^ Jornada::GetIdJornada() { return idJornada; }
        void Jornada::SetIdJornada(String^ idJornada) { this->idJornada = idJornada; }

        int Jornada::GetNumero() { return numero; }
        void Jornada::SetNumero(int numero) { this->numero = numero; }

        DateTime Jornada::GetDataInici() { return dataInici; }
        void Jornada::SetDataInici(DateTime dataInici) { this->dataInici = dataInici; }

        DateTime Jornada::GetDataFi() { return dataFi; }
        void Jornada::SetDataFi(DateTime dataFi) { this->dataFi = dataFi; }

        bool Jornada::ValidarDates() {
            // RIT7
            return dataInici < dataFi;
        }

        bool Jornada::ValidarNumero() {
            // RIT26
            return numero > 0;
        }
    }
}
