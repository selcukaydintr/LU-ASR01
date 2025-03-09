/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: debug_manager.h
 * Açıklama: Debug ve test yönetim sınıfı
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_DEBUG_MANAGER_H
#define ASRPRO_DEBUG_MANAGER_H

#include <memory>
#include <string>
#include "audio/audio_types.h"
#include "hardware/bnpu_driver.h"

namespace asrpro {
namespace debug {

class DebugManager {
public:
    // Performans test yapıları
    struct PerformanceMetrics {
        double processingTime;      // İşlem süresi (ms)
        size_t memoryUsage;        // Bellek kullanımı (bytes)
        uint32_t cpuLoad;          // CPU kullanımı (%)
        uint32_t bnpuLoad;         // BNPU kullanımı (%)
    };

    // Hata ayıklama seviyeleri
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static DebugManager& getInstance();

    // Test fonksiyonları
    bool runUnitTests();
    bool runPerformanceTests();
    bool runIntegrationTests();
    
    // Performans ölçüm
    PerformanceMetrics measurePerformance(const audio::AudioBuffer& input);
    
    // Log yönetimi
    void log(LogLevel level, const std::string& message);
    void enableFileLogging(const std::string& filename);
    void disableFileLogging();

private:
    DebugManager() = default;
    ~DebugManager() = default;
    DebugManager(const DebugManager&) = delete;
    DebugManager& operator=(const DebugManager&) = delete;

    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace debug
} // namespace asrpro

#endif // ASRPRO_DEBUG_MANAGER_H