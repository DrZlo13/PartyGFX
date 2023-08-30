cmake_minimum_required(VERSION 3.9)

project("PartyGFX")

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(
    ${INCLUDES}
)

file(GLOB_RECURSE SOURCES
    "*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${INCLUDES}
)