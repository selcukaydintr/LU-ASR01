cmake_minimum_required(VERSION 3.12)
project(asrpro VERSION 0.1.0 LANGUAGES CXX)

# Compiler flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(ASRPRO_BUILD_TESTS "Build test programs" ON)
option(ASRPRO_ENABLE_LOGGING "Enable logging" ON)

# Dependencies
find_package(Threads REQUIRED)
find_package(Catch2 REQUIRED)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples)
if(ASRPRO_BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Library target
add_library(asrpro_lib
    src/plugin/turkish_asr_plugin.cpp
    src/plugin/plugin_integration.cpp
    src/audio/audio_processor.cpp
    src/hardware/bnpu_driver.cpp
    src/hardware/dma_controller.cpp
    src/monitor/performance_monitor.cpp
)

# Include directories
target_include_directories(asrpro_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Compile definitions
target_compile_definitions(asrpro_lib PRIVATE
    $<$<BOOL:${ASRPRO_ENABLE_LOGGING}>:ASRPRO_LOGGING_ENABLED>
)