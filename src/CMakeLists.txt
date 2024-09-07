cmake_minimum_required(VERSION 3.5)

project(smartcalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(MODEL_LIB ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.a)

set(PROJECT_SOURCES
  ./modules/calculator/include/calculator_model.h
  ./modules/calculator/calculator_model.cc
  ./debug/debug.cc
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE ${MODEL_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE
  ./modules/calculator/include
)

qt_finalize_executable(${PROJECT_NAME})
