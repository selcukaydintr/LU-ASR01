/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: performance_monitor.h
 * Açıklama: Performans izleme ve optimizasyon modülü
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_PERFORMANCE_MONITOR_H
#define ASRPRO_PERFORMANCE_MONITOR_H

#include <cstdint>
#include <string>
#include <vector>
#include <chrono>

namespace asrpro {
namespace monitor {

// Performans metrikleri
struct PerformanceMetrics {
    double processingTime;      // İşlem süresi (ms)
    uint32_t cpuUsage;         // CPU kullanımı (%)
    uint32_t memoryUsage;      // Bellek kullanımı (bytes)
    uint32_t bnpuUtilization;  // BNPU kullanımı (%)
    double recognitionRate;     // Tanıma oranı (%)
};

// Performans olayları
enum class PerformanceEvent {
    AUDIO_PROCESSING_START,
    FEATURE_EXTRACTION_START,
    NEURAL_PROCESSING_START,
    TEXT_GENERATION_START,
    PROCESS_COMPLETE
};

class PerformanceMonitor {
public:
    static PerformanceMonitor& getInstance();

    // Olay işaretçileri
    void markEvent(PerformanceEvent event);
    
    // Performans ölçümleri
    PerformanceMetrics getMetrics() const;
    
    // Optimizasyon önerileri
    std::vector<std::string> getOptimizationSuggestions() const;
    
    // Raporlama
    void generateReport(const std::string& filename) const;
    
    // Ayarlar
    void setThresholds(uint32_t maxCpu, uint32_t maxMemory);
    
private:
    PerformanceMonitor() = default;
    ~PerformanceMonitor() = default;
    
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace monitor
} // namespace asrpro

#endif // ASRPRO_PERFORMANCE_MONITOR_H