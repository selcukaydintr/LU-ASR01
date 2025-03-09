add_executable(asrpro_tests
    test_main.cpp
    plugin_tests.cpp
    audio_tests.cpp
    hardware_tests.cpp
)

target_link_libraries(asrpro_tests PRIVATE
    asrpro_core
    Catch2::Catch2
)

include(CTest)
include(Catch)
catch_discover_tests(asrpro_tests)