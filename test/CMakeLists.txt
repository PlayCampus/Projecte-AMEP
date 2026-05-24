# CMakeLists.txt per a PlayCampus Tests
# ====================================
# Aquesta és una configuració opcional per a qui usi CMake

cmake_minimum_required(VERSION 3.10)
project(PlayCampusTests)

# Configuració de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Afegir Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Habilitar testing
enable_testing()

# Definir executable de tests
file(GLOB TEST_SOURCES "*.cpp")
add_executable(playcampus_tests ${TEST_SOURCES})

# Enllaçar amb Google Test
target_link_libraries(playcampus_tests
  gtest_main
  gtest
)

# Afegir els tests a CTest
add_test(
  NAME PlayCampusTests
  COMMAND playcampus_tests
)

# Opcions de sortida
add_test(
  NAME PlayCampusTests_XML
  COMMAND playcampus_tests --gtest_output="xml:test_results.xml"
)

# Sumarizat
message(STATUS "========================================")
message(STATUS "PlayCampus - Suite de Tests Unitaris")
message(STATUS "========================================")
message(STATUS "")
message(STATUS "Per compilar i executar els tests:")
message(STATUS "  cmake .")
message(STATUS "  cmake --build . --config Debug")
message(STATUS "  ctest")
message(STATUS "")
message(STATUS "O directament:")
message(STATUS "  cmake . && cmake --build . && ctest --verbose")
message(STATUS "")
