project(PartyGFX_tests LANGUAGES CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    "*.cpp"
)

add_executable(PartyGFX_tests ${SOURCES})

target_link_libraries(PartyGFX_tests "PartyGFX")

add_test(NAME PartyGFX_tests COMMAND "PartyGFX_tests")