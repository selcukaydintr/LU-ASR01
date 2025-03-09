/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: test_main.cpp
 * Açıklama: Ana test dosyası
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "plugin/turkish_asr_plugin.h"
#include "audio/audio_processor.h"
#include "hardware/bnpu_driver.h"

// Mock sınıfları
class MockBNPUDriver : public hardware::BNPUDriver {
public:
    MOCK_METHOD(bool, init, (const BNPUConfig&), (override));
    MOCK_METHOD(bool, process, (const void*, void*), (override));
};

class MockAudioProcessor : public audio::AudioProcessor {
public:
    MOCK_METHOD(bool, init, (const Config&), (override));
    MOCK_METHOD(bool, process, (const AudioBuffer&, MFCCFeatures&), (override));
};

// Plugin testleri
TEST_CASE("TurkishASRPlugin Tests", "[plugin]") {
    TurkishASRPluginImpl plugin;
    
    SECTION("Plugin Initialization") {
        TurkishASRConfig config;
        config.sampleRate = 16000;
        config.frameSize = 512;
        config.melBands = 40;
        
        REQUIRE(plugin.init(config) == true);
        REQUIRE(plugin.getStatus() == true);
    }
    
    SECTION("Model Loading") {
        REQUIRE(plugin.loadModel("models/turkish_asr_model.bin") == true);
    }
    
    SECTION("Audio Recognition") {
        std::vector<int16_t> audioData(16000, 0); // 1 saniyelik boş ses
        std::string text;
        REQUIRE(plugin.recognize(audioData.data(), audioData.size(), 
                               &text[0], text.size()) == true);
    }
}

// Audio işleme testleri
TEST_CASE("Audio Processing Tests", "[audio]") {
    audio::AudioProcessor processor;
    
    SECTION("Audio Pre-processing") {
        audio::AudioBuffer buffer(1024);
        REQUIRE(processor.applyPreEmphasis(buffer) == true);
    }
    
    SECTION("MFCC Extraction") {
        audio::AudioBuffer buffer(1024);
        audio::MFCCFeatures features;
        REQUIRE(processor.extractMFCC(buffer, features) == true);
        REQUIRE(features.coeffCount == 13);
    }
}

// BNPU testleri
TEST_CASE("BNPU Driver Tests", "[hardware]") {
    MockBNPUDriver bnpu;
    
    SECTION("BNPU Initialization") {
        hardware::BNPUConfig config;
        config.inputSize = 13;
        config.hiddenSize = 256;
        config.outputSize = 29;
        
        EXPECT_CALL(bnpu, init(config))
            .Times(1)
            .WillOnce(Return(true));
            
        REQUIRE(bnpu.init(config) == true);
    }
    
    SECTION("Neural Network Processing") {
        std::vector<float> input(13, 0.0f);
        std::vector<float> output(29, 0.0f);
        
        EXPECT_CALL(bnpu, process(input.data(), output.data()))
            .Times(1)
            .WillOnce(Return(true));
            
        REQUIRE(bnpu.process(input.data(), output.data()) == true);
    }
}