/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: main.cpp
 * Açıklama: Basit ses tanıma örneği
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#include "plugin/turkish_asr_plugin.h"
#include "monitor/performance_monitor.h"
#include <iostream>
#include <fstream>

using namespace asrpro;

int main() {
    try {
        // Performans izleyici başlat
        auto& perfMonitor = monitor::PerformanceMonitor::getInstance();
        perfMonitor.setThresholds(80, 256); // CPU %80, RAM 256MB
        
        // Plugin oluştur ve yapılandır
        auto plugin = std::unique_ptr<TurkishASRPlugin>(createPlugin());
        
        TurkishASRConfig config;
        config.sampleRate = 16000;
        config.frameSize = 512;
        config.melBands = 40;
        config.mfccCoeffs = 13;
        config.beamWidth = 3.0f;
        
        if (!plugin->init(config)) {
            throw std::runtime_error("Plugin başlatılamadı!");
        }
        
        // Model yükle
        if (!plugin->loadModel("models/turkish_asr_model.bin")) {
            throw std::runtime_error("Model yüklenemedi!");
        }
        
        // Ses dosyasını oku
        std::ifstream audioFile("samples/test.raw", std::ios::binary);
        if (!audioFile) {
            throw std::runtime_error("Ses dosyası açılamadı!");
        }
        
        // Ses verisini oku
        std::vector<int16_t> audioData(16000); // 1 saniyelik ses
        audioFile.read(reinterpret_cast<char*>(audioData.data()), 
                      audioData.size() * sizeof(int16_t));
        
        // Ses tanıma
        char recognizedText[1024];
        perfMonitor.markEvent(monitor::PerformanceEvent::AUDIO_PROCESSING_START);
        
        if (!plugin->recognize(audioData.data(), audioData.size(),
                             recognizedText, sizeof(recognizedText))) {
            throw std::runtime_error("Ses tanıma hatası!");
        }
        
        perfMonitor.markEvent(monitor::PerformanceEvent::PROCESS_COMPLETE);
        
        // Sonuçları göster
        std::cout << "Tanınan Metin: " << recognizedText << std::endl;
        
        // Performans raporu
        auto metrics = perfMonitor.getMetrics();
        std::cout << "\nPerformans Metrikleri:\n";
        std::cout << "İşlem Süresi: " << metrics.processingTime << " ms\n";
        std::cout << "CPU Kullanımı: " << metrics.cpuUsage << "%\n";
        std::cout << "Bellek Kullanımı: " << metrics.memoryUsage / 1024 << " KB\n";
        
        // Optimizasyon önerileri
        auto suggestions = perfMonitor.getOptimizationSuggestions();
        if (!suggestions.empty()) {
            std::cout << "\nOptimizasyon Önerileri:\n";
            for (const auto& suggestion : suggestions) {
                std::cout << "- " << suggestion << std::endl;
            }
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
        return 1;
    }
}