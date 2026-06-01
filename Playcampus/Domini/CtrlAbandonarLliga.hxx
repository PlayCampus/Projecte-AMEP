#pragma once
#include <string>

using namespace System;

namespace Playcampus {
	namespace Domini {
		public ref class CtrlAbandonarLliga {
		private:
			String^ connectionString;
		public:
			CtrlAbandonarLliga();

			String^ AbandonarLliga(String^ correuCapita);
		};
	}
}
