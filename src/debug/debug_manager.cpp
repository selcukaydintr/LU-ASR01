#include "debug/debug_manager.h"
#include <fstream>
#include <chrono>
#include <ctime>

namespace asrpro {
namespace debug {

struct DebugManager::Impl {
    std::ofstream logFile;
    bool fileLoggingEnabled;
    
    std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time));
        return std::string(buffer);
    }
};

DebugManager& DebugManager::getInstance() {
    static DebugManager instance;
    if (!instance.pImpl) {
        instance.pImpl = std::make_unique<Impl>();
    }
    return instance;
}

bool DebugManager::runUnitTests() {
    // TODO: Implement unit tests
    return true;
}

bool DebugManager::runPerformanceTests() {
    // TODO: Implement performance tests
    return true;
}

bool DebugManager::runIntegrationTests() {
    // TODO: Implement integration tests
    return true;
}

PerformanceMetrics DebugManager::measurePerformance(const audio::AudioBuffer& input) {
    PerformanceMetrics metrics;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Test işlemleri...
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    metrics.processingTime = duration.count();
    // TODO: Diğer metrikleri hesapla
    
    return metrics;
}

void DebugManager::log(LogLevel level, const std::string& message) {
    std::string levelStr;
    switch (level) {
        case LogLevel::DEBUG:   levelStr = "DEBUG"; break;
        case LogLevel::INFO:    levelStr = "INFO"; break;
        case LogLevel::WARNING: levelStr = "WARNING"; break;
        case LogLevel::ERROR:   levelStr = "ERROR"; break;
    }
    
    std::string logMessage = 
        "[" + pImpl->getTimestamp() + "][" + levelStr + "] " + message + "\n";
    
    if (pImpl->fileLoggingEnabled && pImpl->logFile.is_open()) {
        pImpl->logFile << logMessage;
        pImpl->logFile.flush();
    }
    
    // Konsola da yaz
    std::cout << logMessage;
}

void DebugManager::enableFileLogging(const std::string& filename) {
    pImpl->logFile.open(filename, std::ios::app);
    pImpl->fileLoggingEnabled = true;
}

void DebugManager::disableFileLogging() {
    if (pImpl->logFile.is_open()) {
        pImpl->logFile.close();
    }
    pImpl->fileLoggingEnabled = false;
}

} // namespace debug
} // namespace asrpro