
cmake_minimum_required(VERSION 3.12)

project(hello_world_custom C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_executable(hello_world_custom "")

target_include_directories(hello_world_custom
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
)

set_target_properties(
  hello_world_custom
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(hello_world_custom
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/constants.cpp
  ${CMAKE_CURRENT_LIST_DIR}/hello_world_float_model_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/hello_world_int8_model_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/picow/output_handler.cpp
  ${CMAKE_CURRENT_LIST_DIR}/constants.h
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.h
  ${CMAKE_CURRENT_LIST_DIR}/output_handler.h
)

target_link_libraries(
  hello_world_custom
  pico-tflmicro
  hardware_pwm
)

pico_enable_stdio_usb(hello_world_custom 1)
pico_enable_stdio_uart(hello_world_custom 0)

pico_add_extra_outputs(hello_world_custom)
