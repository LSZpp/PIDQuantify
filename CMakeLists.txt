cmake_minimum_required (VERSION 3.15 FATAL_ERROR) 

project(PIDQuantify VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14           )
set(CMAKE_CXX_STANDARD_REQUIRED ON  )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ROOT REQUIRED   ) 
include     (${ROOT_USE_FILE}) 

add_executable            (performance src/101_performance.cc                 )
target_compile_options    (performance PRIVATE -O3                            )
target_include_directories(performance PUBLIC  ${PROJECT_SOURCE_DIR}/include  )
target_link_libraries     (performance PRIVATE ${ROOT_LIBRARIES}              )

add_executable            (ROC src/102_ROC.cc                         )
target_compile_options    (ROC PRIVATE -O3                            )
target_include_directories(ROC PUBLIC  ${PROJECT_SOURCE_DIR}/include  )
target_link_libraries     (ROC PRIVATE ${ROOT_LIBRARIES}              )
