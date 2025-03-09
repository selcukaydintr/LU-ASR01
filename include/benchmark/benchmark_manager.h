/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: benchmark_manager.h
 * Açıklama: Benchmark ve performans test yöneticisi
 * Bağımlılıklar: FreeRTOS.h, performance_metrics.h
 * 
 * Versiyon: 1.3.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_BENCHMARK_MANAGER_H
#define ASRPRO_BENCHMARK_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "FreeRTOS.h"
#include "performance_metrics.h"

namespace asrpro {
namespace benchmark {

// Benchmark yapılandırması
struct BenchmarkConfig {
    uint32_t iterationCount{1000};    // Test tekrar sayısı
    uint32_t warmupCount{100};        // Isınma turu sayısı
    bool enableDetailedLog{true};     // Detaylı log
    std::string outputPath;           // Çıktı dosya yolu
};

// Test senaryosu
struct TestCase {
    std::string name;
    std::string inputAudioPath;
    std::string expectedText;
    float expectedAccuracy;
};

class BenchmarkManager {
public:
    static BenchmarkManager& getInstance();

    // Temel işlemler
    bool init(const BenchmarkConfig& config);
    bool addTestCase(const TestCase& testCase);
    bool runBenchmarks();
    
    // Türkçe ASR testleri
    bool runTurkishASRTests();
    bool validateTurkishOutput(const std::string& actual, 
                             const std::string& expected);
    
    // Performans metrikleri
    bool measureLatency();
    bool measureThroughput();
    bool measureResourceUsage();
    
    // Rapor oluşturma
    bool generateReport(const std::string& outputPath);
    std::string getResultSummary() const;

private:
    BenchmarkManager() = default;
    ~BenchmarkManager() = default;
    BenchmarkManager(const BenchmarkManager&) = delete;
    BenchmarkManager& operator=(const BenchmarkManager&) = delete;

    struct Impl;
    std::unique_ptr<Impl> pImpl;

    // Yardımcı metotlar
    bool validateResults();
    bool logMetrics();
    bool checkThresholds();
};

} // namespace benchmark
} // namespace asrpro

#endif // ASRPRO_BENCHMARK_MANAGER_H