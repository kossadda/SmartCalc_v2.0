cmake_minimum_required(VERSION 3.5)

project(smartcalc VERSION 2.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(MODELS
  ${CMAKE_SOURCE_DIR}/model/calculator_model.cc
  ${CMAKE_SOURCE_DIR}/model/credit_model.cc
  ${CMAKE_SOURCE_DIR}/model/deposit_model.cc
)

set(VIEWS
  ${CMAKE_SOURCE_DIR}/view/calculator_view.cc
  ${CMAKE_SOURCE_DIR}/view/credit_view.cc
  ${CMAKE_SOURCE_DIR}/view/deposit_view.cc
  ${CMAKE_SOURCE_DIR}/view/main_window.cc
)

set(CONTROLLERS
  ${CMAKE_SOURCE_DIR}/controller/calculator_controller.cc
  ${CMAKE_SOURCE_DIR}/controller/credit_controller.cc
  ${CMAKE_SOURCE_DIR}/controller/deposit_controller.cc
)

set(ADDITIONAL
  ${CMAKE_SOURCE_DIR}/additional/plot.cc
  ${CMAKE_SOURCE_DIR}/additional/qcustomplot.cc
  ${CMAKE_SOURCE_DIR}/additional/top_menu.cc
  ${CMAKE_SOURCE_DIR}/additional/date.cc
  ${CMAKE_SOURCE_DIR}/additional/table.cc
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/include/model/calculator_model.h
  ${CMAKE_SOURCE_DIR}/include/model/credit_model.h
  ${CMAKE_SOURCE_DIR}/include/model/deposit_model.h
  ${CMAKE_SOURCE_DIR}/include/view/calculator_view.h
  ${CMAKE_SOURCE_DIR}/include/view/credit_view.h
  ${CMAKE_SOURCE_DIR}/include/view/deposit_view.h
  ${CMAKE_SOURCE_DIR}/include/view/main_window.h
  ${CMAKE_SOURCE_DIR}/include/controller/calculator_controller.h
  ${CMAKE_SOURCE_DIR}/include/controller/credit_controller.h
  ${CMAKE_SOURCE_DIR}/include/controller/deposit_controller.h
  ${CMAKE_SOURCE_DIR}/include/additional/qcustomplot.h
  ${CMAKE_SOURCE_DIR}/include/additional/plot.h
  ${CMAKE_SOURCE_DIR}/include/additional/top_menu.h
  ${CMAKE_SOURCE_DIR}/include/additional/date.h
  ${CMAKE_SOURCE_DIR}/include/additional/table.h
)

set(MAIN
  ${CMAKE_SOURCE_DIR}/main/main.cc
)

set(PROJECT_SOURCES
  ${MODELS}
  ${CONTROLLERS}
  ${VIEWS}
  ${ADDITIONAL}
  ${HEADERS}
  ${MAIN}
  ${CMAKE_SOURCE_DIR}/resources/resource.qrc
)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -g)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/modules/include
)

qt_finalize_executable(${PROJECT_NAME})

# enable_testing()
# add_subdirectory(tests)