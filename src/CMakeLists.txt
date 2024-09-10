cmake_minimum_required(VERSION 3.5)

project(smartcalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(MODEL_LIB STATIC ${MODELS})

set(MODELS
  ./modules/include/calculator_model.h
  ./modules/model/calculator_model.cc
)

set(VIEWS
  ./modules/include/calculator_view.h
  ./modules/view/calculator_view.cc
  ./modules/view/calculator_view.ui
  ./modules/include/mainwindow.h
  ./modules/view/mainwindow.cc
  ./modules/view/mainwindow.ui
)

set(ADDITIONAL
  ./modules/additional/qcustomplot.cc
  ./modules/include/qcustomplot.h
  ./modules/include/plot.h
  ./modules/view/plot.cc
  ./modules/view/plot.ui
)

set(MAIN
  ./modules/main.cc
)

set(PROJECT_SOURCES
  ${MODELS} ${VIEWS} ${MAIN} ${ADDITIONAL}
  ./resources/resource.qrc
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE ${MODEL_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE
  ./modules/include
)

qt_finalize_executable(${PROJECT_NAME})
