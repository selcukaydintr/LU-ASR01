/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: error_handler.h
 * Açıklama: Hata yönetimi ve loglama sistemi
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_ERROR_HANDLER_H
#define ASRPRO_ERROR_HANDLER_H

#include <string>
#include <queue>
#include <fstream>
#include <memory>
#include <chrono>

namespace asrpro {
namespace debug {

// Hata seviyeleri
enum class ErrorLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

// Hata bilgisi
struct ErrorInfo {
    ErrorLevel level;
    std::string message;
    std::string source;
    std::string timestamp;
    uint32_t errorCode;
    
    ErrorInfo(ErrorLevel lvl, 
             const std::string& msg,
             const std::string& src,
             uint32_t code) 
        : level(lvl)
        , message(msg)
        , source(src)
        , errorCode(code) {
        // Zaman damgası ekle
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        timestamp = std::ctime(&time);
    }
};

class ErrorHandler {
public:
    static ErrorHandler& getInstance();
    
    // Hata kayıt
    void logError(const ErrorInfo& error);
    
    // Hata yakalama
    void handleError(ErrorLevel level, 
                    const std::string& message,
                    const std::string& source,
                    uint32_t errorCode);
    
    // Log dosyası yönetimi
    void setLogFile(const std::string& filename);
    void enableConsoleOutput(bool enable);
    
    // Hata istatistikleri
    uint32_t getTotalErrors() const;
    uint32_t getErrorCount(ErrorLevel level) const;
    
private:
    ErrorHandler() = default;
    ~ErrorHandler() = default;
    
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

// Makrolar
#define LOG_DEBUG(msg, source) \
    ErrorHandler::getInstance().handleError(ErrorLevel::DEBUG, msg, source, 0)

#define LOG_INFO(msg, source) \
    ErrorHandler::getInstance().handleError(ErrorLevel::INFO, msg, source, 0)

#define LOG_WARNING(msg, source) \
    ErrorHandler::getInstance().handleError(ErrorLevel::WARNING, msg, source, 0)

#define LOG_ERROR(msg, source, code) \
    ErrorHandler::getInstance().handleError(ErrorLevel::ERROR, msg, source, code)

#define LOG_CRITICAL(msg, source, code) \
    ErrorHandler::getInstance().handleError(ErrorLevel::CRITICAL, msg, source, code)

} // namespace debug
} // namespace asrpro

#endif // ASRPRO_ERROR_HANDLER_H