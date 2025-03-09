/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: plugin_integration.cpp
 * Açıklama: Ana sistem entegrasyon modülü
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#include "plugin/plugin_integration.h"
#include "debug/debug_manager.h"
#include "monitor/performance_monitor.h"
#include <vector>
#include <memory>

namespace asrpro {
namespace integration {

class PluginIntegration {
private:
    std::vector<std::unique_ptr<plugin::TurkishASRPlugin>> plugins;
    debug::DebugManager& debugManager;
    monitor::PerformanceMonitor& perfMonitor;
    
    // Entegrasyon yapılandırması
    struct Config {
        uint32_t maxPlugins{5};          // Maksimum plugin sayısı
        uint32_t bufferSize{8192};       // Buffer boyutu
        bool enablePerfMonitoring{true};  // Performans izleme
        bool enableLogging{true};         // Loglama
    } config;

public:
    PluginIntegration()
        : debugManager(debug::DebugManager::getInstance())
        , perfMonitor(monitor::PerformanceMonitor::getInstance())
    {
        debugManager.log(debug::LogLevel::INFO, 
            "Plugin entegrasyon sistemi başlatılıyor...");
    }

    bool loadPlugin(const std::string& pluginPath) {
        if (plugins.size() >= config.maxPlugins) {
            debugManager.log(debug::LogLevel::ERROR, 
                "Maksimum plugin sayısına ulaşıldı!");
            return false;
        }

        try {
            auto plugin = std::make_unique<plugin::TurkishASRPlugin>();
            
            // Plugin başlatma
            plugin::TurkishASRConfig pluginConfig;
            pluginConfig.sampleRate = 16000;
            pluginConfig.frameSize = 512;
            pluginConfig.melBands = 40;
            
            if (!plugin->init(pluginConfig)) {
                throw std::runtime_error("Plugin başlatılamadı!");
            }

            // Model yükleme
            if (!plugin->loadModel(pluginPath.c_str())) {
                throw std::runtime_error("Model yüklenemedi!");
            }

            plugins.push_back(std::move(plugin));
            debugManager.log(debug::LogLevel::INFO, 
                "Plugin başarıyla yüklendi: " + pluginPath);
                
            return true;
        }
        catch (const std::exception& e) {
            debugManager.log(debug::LogLevel::ERROR, 
                "Plugin yükleme hatası: " + std::string(e.what()));
            return false;
        }
    }

    bool processAudio(const int16_t* audio, size_t length, 
                     std::string& recognizedText) {
        if (plugins.empty()) {
            debugManager.log(debug::LogLevel::ERROR, 
                "Yüklenmiş plugin bulunamadı!");
            return false;
        }

        try {
            // Performans izleme başlat
            perfMonitor.markEvent(
                monitor::PerformanceEvent::AUDIO_PROCESSING_START);

            // Ses işleme
            char textBuffer[1024];
            if (!plugins[0]->recognize(audio, length, 
                                     textBuffer, sizeof(textBuffer))) {
                throw std::runtime_error("Ses işleme hatası!");
            }

            recognizedText = textBuffer;
            
            // Performans izleme bitir
            perfMonitor.markEvent(
                monitor::PerformanceEvent::PROCESS_COMPLETE);

            // Performans metrikleri
            if (config.enablePerfMonitoring) {
                auto metrics = perfMonitor.getMetrics();
                debugManager.log(debug::LogLevel::INFO, 
                    "İşlem süresi: " + std::to_string(metrics.processingTime) + "ms");
            }

            return true;
        }
        catch (const std::exception& e) {
            debugManager.log(debug::LogLevel::ERROR, 
                "Ses işleme hatası: " + std::string(e.what()));
            return false;
        }
    }

    void shutdown() {
        for (auto& plugin : plugins) {
            plugin->shutdown();
        }
        plugins.clear();
        
        debugManager.log(debug::LogLevel::INFO, 
            "Plugin entegrasyon sistemi kapatıldı.");
    }
};

} // namespace integration
} // namespace asrpro