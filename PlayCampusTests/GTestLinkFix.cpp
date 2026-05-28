#include "pch.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"

namespace testing {
	namespace internal {

		Mutex g_linked_ptr_mutex(Mutex::kStaticMutex);

	}
}