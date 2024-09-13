cmake_minimum_required(VERSION 3.5)

project(smartcalc VERSION 2.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(MODELS
  ${CMAKE_SOURCE_DIR}/modules/include/calculator_model.h
  ${CMAKE_SOURCE_DIR}/modules/model/calculator_model.cc
)

set(VIEWS
  ${CMAKE_SOURCE_DIR}/modules/include/calculator_view.h
  ${CMAKE_SOURCE_DIR}/modules/view/calculator_view.cc
  ${CMAKE_SOURCE_DIR}/modules/view/calculator_view.ui
  ${CMAKE_SOURCE_DIR}/modules/include/mainwindow.h
  ${CMAKE_SOURCE_DIR}/modules/view/mainwindow.cc
  ${CMAKE_SOURCE_DIR}/modules/view/mainwindow.ui
)

set(CONTROLLERS
  ${CMAKE_SOURCE_DIR}/modules/include/calculator_controller.h
  ${CMAKE_SOURCE_DIR}/modules/controller/calculator_controller.cc
)

set(ADDITIONAL
  ${CMAKE_SOURCE_DIR}/modules/additional/qcustomplot.cc
  ${CMAKE_SOURCE_DIR}/modules/include/qcustomplot.h
  ${CMAKE_SOURCE_DIR}/modules/include/plot.h
  ${CMAKE_SOURCE_DIR}/modules/view/plot.cc
  ${CMAKE_SOURCE_DIR}/modules/view/plot.ui
  ${CMAKE_SOURCE_DIR}/modules/include/top_menu.h
)

set(MAIN
  ${CMAKE_SOURCE_DIR}/modules/main.cc
)

set(PROJECT_SOURCES
  ${MODELS} ${CONTROLLERS} ${VIEWS} ${ADDITIONAL} ${MAIN}
  ${CMAKE_SOURCE_DIR}/resources/resource.qrc
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/modules/include
)

qt_finalize_executable(${PROJECT_NAME})
