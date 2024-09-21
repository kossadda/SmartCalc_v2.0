cmake_minimum_required(VERSION 3.5)

project(smartcalc_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/test_modules/calculator_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/test_modules/credit_test.cc
)

set(PROJECT_SOURCES
  ${CMAKE_SOURCE_DIR}/modules/model/calculator_model.cc
  ${CMAKE_SOURCE_DIR}/modules/model/credit_model.cc
  ${CMAKE_SOURCE_DIR}/modules/additional/calendar.cc
)

add_executable(smartcalc_tests ${TEST_SOURCES} ${PROJECT_SOURCES})

target_link_libraries(smartcalc_tests ${GTEST_LIBRARIES} pthread)

target_include_directories(smartcalc_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/modules/include
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GoogleTest)
gtest_discover_tests(smartcalc_tests)
