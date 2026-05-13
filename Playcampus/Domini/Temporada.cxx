#include "pch.h"
#include "Temporada.hxx"

namespace Playcampus {
    namespace Domini {
        Temporada::Temporada(DateTime dataInici, DateTime dataFi, String^ estat) {
            this->dataInici = dataInici;
            this->dataFi = dataFi;
            this->estat = estat;
        }

        DateTime Temporada::GetDataInici() { return dataInici; }
        void Temporada::SetDataInici(DateTime dataInici) { this->dataInici = dataInici; }

        DateTime Temporada::GetDataFi() { return dataFi; }
        void Temporada::SetDataFi(DateTime dataFi) { this->dataFi = dataFi; }

        String^ Temporada::GetEstat() { return estat; }
        void Temporada::SetEstat(String^ estat) { this->estat = estat; }

        bool Temporada::ValidarDates() {
            // RIT25
            return dataInici < dataFi;
        }
    }
}
