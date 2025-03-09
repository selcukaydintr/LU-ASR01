cmake_minimum_required(VERSION 3.12)
project(asrpro_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Kaynak dosyaları
add_executable(asrpro_example
    main.cpp
)

# Include dizinleri
target_include_directories(asrpro_example PRIVATE
    ${PROJECT_SOURCE_DIR}/../../include
)

# Kütüphane bağlantıları
target_link_libraries(asrpro_example PRIVATE
    asrpro_plugin
    asrpro_audio
    asrpro_hardware
)