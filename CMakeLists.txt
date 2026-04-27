
cmake_minimum_required(VERSION 3.20)

project(
    AlgoSmith
    VERSION 1.0.0
    DESCRIPTION "A professional C++ DSA library"
    LANGUAGES CXX
)

# ── Language Standard ────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Compiler Warnings ────────────────────────────────────────────────────────
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
)

# ── Interface Library (header + .tpp template library) ──────────────────────
add_library(algosmith INTERFACE)

target_include_directories(algosmith
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# ── Sub-projects ─────────────────────────────────────────────────────────────
add_subdirectory(examples)
add_subdirectory(tests)

