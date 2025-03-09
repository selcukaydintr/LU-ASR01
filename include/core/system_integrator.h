/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: system_integrator.h
 * Açıklama: Ana sistem entegrasyon modülü
 * Bağımlılıklar: FreeRTOS, hal_layer.h, sdk_wrapper.h
 * 
 * Versiyon: 1.2.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_SYSTEM_INTEGRATOR_H
#define ASRPRO_SYSTEM_INTEGRATOR_H

#include "FreeRTOS.h"
#include "hal/hal_layer.h"
#include "sdk/sdk_wrapper.h"
#include "turkish/turkish_nlp.h"
#include <memory>

namespace asrpro {
namespace core {

// Sistem yapılandırması
struct SystemConfig {
    // Donanım yapılandırması
    struct {
        uint32_t uartBaudRate{115200};
        uint32_t dmaBufferSize{4096};
        bool useCache{true};
    } hardware;

    // ASR yapılandırması
    struct {
        std::string modelPath;
        std::string configPath;
        float threshold{0.75f};
        uint32_t maxLatency{100};
    } asr;

    // FreeRTOS yapılandırması
    struct {
        uint32_t stackSize{4096};
        uint8_t priority{5};
        uint16_t queueSize{10};
    } rtos;
};

class SystemIntegrator {
public:
    static SystemIntegrator& getInstance();

    // Sistem yönetimi
    bool init(const SystemConfig& config);
    bool start();
    bool stop();
    bool configure(const SystemConfig& config);

    // Ses işleme
    bool processAudio(const void* audioData, size_t size);
    bool getRecognitionResult(std::string& text);

    // Durum kontrolü
    bool isRunning() const;
    bool isProcessing() const;
    const char* getErrorString() const;

    // Plugin yönetimi
    bool loadPlugin(const std::string& path);
    bool unloadPlugin(const std::string& name);

    // Örnek kullanımlar
    void runBasicExample();
    void runTurkishASRExample();
    void runPerformanceTest();

private:
    SystemIntegrator() = default;
    ~SystemIntegrator() = default;
    SystemIntegrator(const SystemIntegrator&) = delete;
    SystemIntegrator& operator=(const SystemIntegrator&) = delete;

    struct Impl;
    std::unique_ptr<Impl> pImpl;

    // FreeRTOS task işlevleri
    static void mainTask(void* params);
    static void processingTask(void* params);
    static void monitoringTask(void* params);
};

} // namespace core
} // namespace asrpro

#endif // ASRPRO_SYSTEM_INTEGRATOR_H