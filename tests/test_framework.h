/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: test_framework.h
 * Açıklama: Test çerçevesi header dosyası
 * 
 * Versiyon: 0.1.1
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_TEST_FRAMEWORK_H
#define ASRPRO_TEST_FRAMEWORK_H

#include <string>
#include <vector>
#include <functional>
#include "debug/error_handler.h"
#include "monitor/performance_monitor.h"

namespace asrpro {
namespace test {

// Test sonuç yapısı
struct TestResult {
    std::string testName;
    bool passed;
    std::string errorMessage;
    double executionTime;
    monitor::PerformanceMetrics perfMetrics;
};

class TestFramework {
public:
    using TestFunction = std::function<bool(std::string&)>;

    // Test kayıt
    void registerTest(const std::string& name, TestFunction func);
    
    // Test çalıştırma
    std::vector<TestResult> runAllTests();
    TestResult runSingleTest(const std::string& name);
    
    // Rapor oluşturma
    void generateReport(const std::string& filename);
    
    // Yapılandırma
    void setConfig(const std::string& configFile);

private:
    struct TestCase {
        std::string name;
        TestFunction func;
    };
    
    std::vector<TestCase> tests;
};

} // namespace test
} // namespace asrpro

#endif // ASRPRO_TEST_FRAMEWORK_H