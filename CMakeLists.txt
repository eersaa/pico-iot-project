# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# Pull in SDK (must be before project)
# set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

project(pico-iot-project C CXX ASM)


include(FetchContent)

# Pull in FreeRTOS-kernel port for pi pico
FetchContent_Declare(
  FreeRTOS-Kernel
  GIT_REPOSITORY https://github.com/raspberrypi/FreeRTOS-Kernel.git
  GIT_TAG 4f7299d
)

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
# Select the native compile PORT
set( FREERTOS_PORT "GCC_POSIX" CACHE STRING "" FORCE)
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
  set(FREERTOS_PORT "GCC_ARM_CM0" CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(FreeRTOS-Kernel)

set(FREERTOS_KERNEL_PATH ${freertos-kernel_SOURCE_DIR})

FetchContent_Declare(
  FreeRTOS
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS.git
  GIT_TAG e62f739
  )
  
  FetchContent_MakeAvailable(FreeRTOS)
  
set(FREERTOS_DEMO_PATH ${freertos_SOURCE_DIR}/FreeRTOS/Demo)

# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

if (NOT FREERTOS_DEMO_PATH)
        if (DEFINED ENV{FREERTOS_DEMO_PATH})
                set(FREERTOS_DEMO_PATH $ENV{FREERTOS_DEMO_PATH})
                message("Using FREERTOS_DEMO_PATH from environment ('${FREERTOS_DEMO_PATH}')")
        elseif(EXISTS ${FREERTOS_KERNEL_PATH}/../Demo)
                set(FREERTOS_DEMO_PATH ${FREERTOS_KERNEL_PATH}/../Demo)
        else ()
                message(FATAL_ERROR "FreeRTOS demo path was not specified. Please set FREERTOS_DEMO_PATH.")
        endif ()
endif ()


set(PICO_BOARD pico_w CACHE STRING "Board type" FORCE)

pico_sdk_init()

add_executable(main_full
        main.c
        main_full.c
        IntQueueTimer.c
        RegTest.s
        ${FREERTOS_DEMO_PATH}/Common/Minimal/blocktim.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/countsem.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/dynamic.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/recmutex.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/QueueOverwrite.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/EventGroupsDemo.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/IntSemTest.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/IntQueue.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/TaskNotify.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/TimerDemo.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/GenQTest.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/death.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/semtest.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/BlockQ.c
        ${FREERTOS_DEMO_PATH}/Common/Minimal/flop.c
        )

target_compile_definitions(main_full PRIVATE
        mainCREATE_SIMPLE_BLINKY_DEMO_ONLY=0
        )

target_include_directories(main_full PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${FREERTOS_DEMO_PATH}/Common/include)

target_compile_definitions(main_full PRIVATE
        PICO_STDIO_STACK_BUFFER_SIZE=64 # use a small printf on stack buffer
)

target_link_libraries(main_full
                        pico_stdlib 
                        FreeRTOS-Kernel 
                        FreeRTOS-Kernel-Heap4
                        pico_cyw43_arch_none
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(main_full 1)
pico_enable_stdio_usb(main_full 1)

pico_add_extra_outputs(main_full)

add_executable(main_blinky
        main.c
        main_blinky.c
        )

target_compile_definitions(main_blinky PRIVATE
        mainCREATE_SIMPLE_BLINKY_DEMO_ONLY=1
        )

target_include_directories(main_blinky PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${FREERTOS_DEMO_PATH}/Common/include)

target_link_libraries(main_blinky 
                        pico_stdlib
                        FreeRTOS-Kernel 
                        FreeRTOS-Kernel-Heap1
                        pico_cyw43_arch_none
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(main_blinky 1)
pico_enable_stdio_usb(main_blinky 1)

pico_add_extra_outputs(main_blinky)


# Add executable. Default name is the project name, version 0.1

add_executable(pico-iot-project 
        pico-iot-project.c
        )

pico_set_program_name(pico-iot-project "pico-iot-project")
pico_set_program_version(pico-iot-project "0.1")

# Generate PIO header
# pico_generate_pio_header(pico-iot-project ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico-iot-project 1)
pico_enable_stdio_usb(pico-iot-project 1)

# Add the standard library to the build
target_link_libraries(pico-iot-project
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(pico-iot-project PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(pico-iot-project 
        pico_stdlib
        FreeRTOS-Kernel 
        FreeRTOS-Kernel-Heap1
        pico_cyw43_arch_none
        freertos_config
        )

pico_add_extra_outputs(pico-iot-project)
