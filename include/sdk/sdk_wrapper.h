/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: sdk_wrapper.h
 * Açıklama: SDK entegrasyon katmanı
 * Bağımlılıklar: asrpro_sdk.h, hal_layer.h
 * 
 * Versiyon: 1.0.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_SDK_WRAPPER_H
#define ASRPRO_SDK_WRAPPER_H

#include "asrpro_sdk.h"
#include "hal/hal_layer.h"
#include "turkish/turkish_nlp.h"
#include <memory>

namespace asrpro {
namespace sdk {

// SDK yapılandırma yapısı
struct SDKConfig {
    // Temel ayarlar
    struct {
        uint32_t sampleRate{16000};
        uint16_t frameSize{512};
        uint8_t channels{1};
    } audio;

    // VAD ayarları
    struct {
        float threshold{0.5f};
        uint16_t silenceMs{500};
    } vad;

    // ASR ayarları
    struct {
        std::string modelPath;
        std::string configPath;
        bool useTurkishASR{true};
    } asr;

    // Test ayarları
    struct {
        bool enableUnitTests{true};
        bool enablePerfTests{true};
        std::string testDataPath;
    } test;
};

class SDKWrapper {
public:
    static SDKWrapper& getInstance();

    // SDK yönetimi
    bool init(const SDKConfig& config);
    bool deinit();
    bool isInitialized() const;

    // ASR işlemleri
    bool startRecognition();
    bool stopRecognition();
    bool getResult(std::string& text);

    // Test ve doğrulama
    bool runTests();
    bool validateConfig();
    const char* getErrorString() const;

private:
    SDKWrapper() = default;
    ~SDKWrapper() = default;
    SDKWrapper(const SDKWrapper&) = delete;
    SDKWrapper& operator=(const SDKWrapper&) = delete;

    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace sdk
} // namespace asrpro

#endif // ASRPRO_SDK_WRAPPER_H