/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: test_suite.h
 * Açıklama: Test ve benchmark modülü
 * Bağımlılıklar: <vector>, <string>, <chrono>
 * 
 * Versiyon: 1.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_TEST_SUITE_H
#define ASRPRO_TEST_SUITE_H

#include <vector>
#include <string>
#include <chrono>
#include <functional>
#include "turkish/turkish_nlp.h"
#include "hardware/uart_controller.h"

namespace asrpro {
namespace test {

// Test sonuç yapısı
struct TestResult {
    std::string name;
    bool passed;
    double duration;
    std::string errorMessage;
    size_t memoryUsage;
};

// Benchmark sonuç yapısı
struct BenchmarkResult {
    std::string name;
    double averageLatency;
    double maxLatency;
    double minLatency;
    size_t totalMemory;
    size_t peakMemory;
};

class TestSuite {
public:
    using TestFunction = std::function<bool(std::string&)>;
    
    // Test yönetimi
    bool registerTest(const std::string& name, TestFunction func);
    bool runAllTests();
    std::vector<TestResult> getResults() const;
    
    // Benchmark testleri
    bool runBenchmark(const std::string& name, size_t iterations);
    BenchmarkResult getBenchmarkResults() const;
    
    // Türkçe ASR testleri
    bool testTurkishASR(const std::string& audioFile, 
                       const std::string& expectedText);
    
    // Hardware testleri
    bool testUARTConnection();
    bool testDMATransfer();
    bool testBNPUProcessor();

private:
    std::vector<std::pair<std::string, TestFunction>> tests;
    std::vector<TestResult> results;
    BenchmarkResult benchmarkResult;
    
    // Yardımcı fonksiyonlar
    bool measurePerformance(const std::string& testName);
    bool validateResults(const std::string& testName);
};

} // namespace test
} // namespace asrpro

#endif // ASRPRO_TEST_SUITE_H