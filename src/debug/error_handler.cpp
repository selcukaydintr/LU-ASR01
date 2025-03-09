#include "debug/error_handler.h"
#include <iostream>
#include <map>

namespace asrpro {
namespace debug {

struct ErrorHandler::Impl {
    std::ofstream logFile;
    bool consoleOutput{true};
    std::map<ErrorLevel, uint32_t> errorCounts;
    uint32_t totalErrors{0};
    
    std::string getLevelString(ErrorLevel level) {
        switch (level) {
            case ErrorLevel::DEBUG: return "DEBUG";
            case ErrorLevel::INFO: return "INFO";
            case ErrorLevel::WARNING: return "WARNING";
            case ErrorLevel::ERROR: return "ERROR";
            case ErrorLevel::CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }
    
    void writeToLog(const ErrorInfo& error) {
        std::string logMessage = 
            "[" + error.timestamp + "][" + 
            getLevelString(error.level) + "][" +
            error.source + "] " + error.message;
            
        if (error.errorCode != 0) {
            logMessage += " (Code: " + std::to_string(error.errorCode) + ")";
        }
        
        if (logFile.is_open()) {
            logFile << logMessage << std::endl;
        }
        
        if (consoleOutput) {
            std::cout << logMessage << std::endl;
        }
        
        // İstatistikleri güncelle
        errorCounts[error.level]++;
        totalErrors++;
    }
};

ErrorHandler& ErrorHandler::getInstance() {
    static ErrorHandler instance;
    if (!instance.pImpl) {
        instance.pImpl = std::make_unique<Impl>();
    }
    return instance;
}

void ErrorHandler::logError(const ErrorInfo& error) {
    pImpl->writeToLog(error);
}

void ErrorHandler::handleError(ErrorLevel level,
                             const std::string& message,
                             const std::string& source,
                             uint32_t errorCode) {
    ErrorInfo error(level, message, source, errorCode);
    logError(error);
}

void ErrorHandler::setLogFile(const std::string& filename) {
    if (pImpl->logFile.is_open()) {
        pImpl->logFile.close();
    }
    pImpl->logFile.open(filename, std::ios::app);
}

void ErrorHandler::enableConsoleOutput(bool enable) {
    pImpl->consoleOutput = enable;
}

uint32_t ErrorHandler::getTotalErrors() const {
    return pImpl->totalErrors;
}

uint32_t ErrorHandler::getErrorCount(ErrorLevel level) const {
    return pImpl->errorCounts[level];
}

} // namespace debug
} // namespace asrpro