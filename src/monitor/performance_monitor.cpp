#include "monitor/performance_monitor.h"
#include "hardware/bnpu_driver.h"
#include <fstream>
#include <sstream>

namespace asrpro {
namespace monitor {

struct PerformanceMonitor::Impl {
    std::chrono::high_resolution_clock::time_point startTime;
    std::map<PerformanceEvent, double> eventTimings;
    
    uint32_t maxCpuThreshold{80};    // %80 CPU limiti
    uint32_t maxMemoryThreshold{256}; // 256MB bellek limiti
    
    PerformanceMetrics currentMetrics{};
    
    void updateMetrics() {
        // CPU kullanımı hesapla
        currentMetrics.cpuUsage = getCPUUsage();
        
        // Bellek kullanımı hesapla
        currentMetrics.memoryUsage = getMemoryUsage();
        
        // BNPU kullanımı al
        auto& bnpu = hardware::BNPUDriver::getInstance();
        currentMetrics.bnpuUtilization = bnpu.getUtilization();
        
        // İşlem süresini hesapla
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                       (now - startTime);
        currentMetrics.processingTime = duration.count();
    }
    
    std::vector<std::string> analyzePerformance() {
        std::vector<std::string> suggestions;
        
        // CPU kullanımı yüksekse
        if (currentMetrics.cpuUsage > maxCpuThreshold) {
            suggestions.push_back("CPU kullanımı çok yüksek. "
                                "Batch işleme boyutunu artırmayı deneyin.");
        }
        
        // Bellek kullanımı yüksekse
        if (currentMetrics.memoryUsage > maxMemoryThreshold * 1024 * 1024) {
            suggestions.push_back("Bellek kullanımı yüksek. "
                                "Buffer boyutlarını optimize edin.");
        }
        
        // BNPU kullanımı düşükse
        if (currentMetrics.bnpuUtilization < 50) {
            suggestions.push_back("BNPU kullanımı düşük. "
                                "Paralel işleme sayısını artırın.");
        }
        
        return suggestions;
    }
};

// Changes.md dosyasını güncelle
void updateChangesLog(const std::string& message) {
    std::ofstream changes("changes.md", std::ios::app);
    if (changes.is_open()) {
        changes << "\n# [" << getCurrentDateTime() << "] Performans İyileştirme\n";
        changes << "- " << message << "\n";
        changes.close();
    }
}

PerformanceMonitor& PerformanceMonitor::getInstance() {
    static PerformanceMonitor instance;
    if (!instance.pImpl) {
        instance.pImpl = std::make_unique<Impl>();
    }
    return instance;
}

void PerformanceMonitor::markEvent(PerformanceEvent event) {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                   (now - pImpl->startTime);
    
    pImpl->eventTimings[event] = duration.count();
    
    if (event == PerformanceEvent::PROCESS_COMPLETE) {
        pImpl->updateMetrics();
        
        // Performans raporunu güncelle
        auto suggestions = pImpl->analyzePerformance();
        if (!suggestions.empty()) {
            updateChangesLog("Performans optimizasyon önerileri: " + 
                           suggestions[0]);
        }
    }
}

PerformanceMetrics PerformanceMonitor::getMetrics() const {
    return pImpl->currentMetrics;
}

std::vector<std::string> PerformanceMonitor::getOptimizationSuggestions() const {
    return pImpl->analyzePerformance();
}

void PerformanceMonitor::setThresholds(uint32_t maxCpu, uint32_t maxMemory) {
    pImpl->maxCpuThreshold = maxCpu;
    pImpl->maxMemoryThreshold = maxMemory;
}

} // namespace monitor
} // namespace asrpro