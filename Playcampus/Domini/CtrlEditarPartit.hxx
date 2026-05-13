#include <string>
#include "Partit.hxx"

using namespace System::Collections::Generic;
using namespace System;

namespace Playcampus {
    namespace Domini {
        public ref class CtrlEditarPartit {
        private:
            String^ connectionString;

        public:
            CtrlEditarPartit();
            bool ValidarAdministradorLliga(String^ nomLliga, String^ correuAdmin);
            String^ ObtenirNomLligaAdmin(String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirPartitsPerLliga(String^ nomLliga, String^ correuAdmin);
            Dictionary<String^, String^>^ ObtenirDetallPartit(String^ idPartit, String^ correuAdmin);
            List<Dictionary<String^, String^>^>^ ObtenirJugadorsPartit(String^ idPartit, String^ correuAdmin);
            void ActualitzarPartitIStats(String^ idPartit, String^ nouEstat, int resultatLocal, int resultatVisitant, String^ statsJson, String^ correuAdmin, Nullable<DateTime> novaDataPartit);
        };
    }
}
