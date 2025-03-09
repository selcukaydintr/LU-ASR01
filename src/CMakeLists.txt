add_library(asrpro_core
    plugin/turkish_asr_plugin.cpp
    plugin/plugin_integration.cpp
    audio/audio_processor.cpp
    hardware/bnpu_driver.cpp
    hardware/dma_controller.cpp
    monitor/performance_monitor.cpp
)

target_include_directories(asrpro_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(asrpro_core PRIVATE
    Threads::Threads
)