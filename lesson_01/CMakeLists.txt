##############################################################
#
# Description: lesson_01 CMakeLists.txt
# 
# Lesson 01 is basic verilator/cmake/g++/clang++ integration
# with a very simple SystemVerilog module.
#
# SPDX-FileCopyrightText: 2026 Cade Weinberg
# SPDX-License-Identifier: CC0-1.0
#
##############################################################

cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0144 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(lesson_01)

# in order to properly use the OSS CAD SUITE we are going to need to source their environment file.
# normally, I am used to having a c/c++ environment, where the global OS environment has been set 
# up to provide the c/c++ build tools and libraries. via pkg_config, and cmake packages. etc.
# in this case we also need a properly set up python environment. as many of the tools in OSS CAD
# are python3 based. This is more than acceptable, my question is only, how do I want to source 
# the oss cad environment for hardware build sessions, without sourcing it by default for every user 
# session. (though by those lines, why is the global environment set up for c/c++ development?
# I think it's actually mostly the python venv that is being used that is the concern, though that 
# is a guess based on the way the terminal changes when sourcing the env. We dont want to always 
# be operating the OSS CAD python venv. sometimes we want other venvs. and for Linux tools that 
# are tightly integrated with the OS, we want those to run in the global env.)
# we could write a simple makefile whose sole purpose was to set up the environment, just before 
# we invoke cmake.
# we could manually set up the environment before running cmake each time we wanted to do
# hardware development.
#

find_package(verilator HINTS $ENV{VERILATOR_ROOT} ${VERILATOR_ROOT})
if (NOT verilator_FOUND)
message(FATAL_ERROR "Verilator was not found, make sure the environment is set up with VERILATOR_ROOT")
endif ()


add_executable(lesson_01)

target_compile_options(lesson_01 PUBLIC
    -Wall
    -Wextra
    -Wconversion
)

target_sources(lesson_01 PRIVATE 
    ${PROJECT_SOURCE_DIR}/source/cxx/main.cpp
)

# verilator acts like bison/flex/etc where it takes the source Verilog/SystemVerilog
# and translates (verilates) it into C++, This C++ is then compiled into our executable.
# We in essence need to provide a main subroutine which does setup, eval, and teardown.
# along the way we also provide tracing and formal verification.

# the verilate call is the main function which "verilates" our source SystemVerilog into
# C++. So we need to verilate -> add the generated files to our target executable,
# then run the compile step.
verilate(lesson_01
    INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/source/systemverilog
    SOURCES ${PROJECT_SOURCE_DIR}/source/systemverilog/top.sv
)

target_compile_definitions(lesson_01 PRIVATE
    VL_TIME_CONTEXT # disable legacy vl_time_stamp symbol
)





