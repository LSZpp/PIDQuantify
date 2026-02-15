

# CMakeLists.txt for PIDQuantify
# LSZ 15 Feb 26

# Creates a shared library for PIDQuantify

cmake_minimum_required (VERSION 3.14 FATAL_ERROR)

project(PIDQuantify VERSION 1 LANGUAGES CXX)

# Using C++14 in this software
set(CMAKE_CXX_STANDARD 14           )
set(CMAKE_CXX_STANDARD_REQUIRED ON  )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting the paths for any executable(s) made
set(PIDQuantify_INSTALLED_EXE "${CMAKE_INSTALL_PREFIX}/bin/PIDQuantify")

# Make installed executables find installed libraries
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# The package requires ROOT and an external yaml-cpp parsing tool to compile
find_package(ROOT REQUIRED    )
include     (${ROOT_USE_FILE} )

# Setting the directories for the header and source files
file(GLOB_RECURSE HEADERS include/*.hh)
file(GLOB_RECURSE SOURCES     src/*.cc)

# Now compiling the code to a shared library exposed to the user
add_library               (PIDQuantify SHARED  ${HEADERS} ${SOURCES}          )
target_compile_options    (PIDQuantify PRIVATE -O3                            )
target_include_directories(PIDQuantify PUBLIC  include                        )
target_link_libraries     (PIDQuantify PUBLIC  ROOT::Core ROOT::Hist ROOT::RIO)

# Installing the software
include(GNUInstallDirs)
install(TARGETS PIDQuantify
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Creating the PIDQuantify-config script, so users can use it in a way of adding `PIDQuantify-config`
# after they use their g++ command for compilation
# (exactly the way the user interacts with ROOT)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/PIDQuantify-config.in
    ${CMAKE_CURRENT_BINARY_DIR}/PIDQuantify-config
    @ONLY
)

install(PROGRAMS    ${CMAKE_CURRENT_BINARY_DIR}/PIDQuantify-config
        DESTINATION ${CMAKE_INSTALL_BINDIR})
