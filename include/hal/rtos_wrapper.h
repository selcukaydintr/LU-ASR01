/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: rtos_wrapper.h
 * Açıklama: FreeRTOS sarmalayıcı sınıfı
 * Bağımlılıklar: FreeRTOS.h, task.h, queue.h, semphr.h
 * 
 * Versiyon: 0.8.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_RTOS_WRAPPER_H
#define ASRPRO_RTOS_WRAPPER_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <functional>
#include <string>
#include <memory>

namespace asrpro {
namespace hal {

// Task öncelikleri
enum class TaskPriority {
    IDLE = tskIDLE_PRIORITY,
    LOW = (configMAX_PRIORITIES - 4),
    NORMAL = (configMAX_PRIORITIES - 3),
    HIGH = (configMAX_PRIORITIES - 2),
    CRITICAL = (configMAX_PRIORITIES - 1)
};

// Task yapılandırması
struct TaskConfig {
    std::string name;
    uint32_t stackSize{4096};
    TaskPriority priority{TaskPriority::NORMAL};
    uint16_t queueSize{10};
    bool autoStart{true};
};

class RTOSWrapper {
public:
    using TaskFunction = std::function<void(void*)>;
    
    static RTOSWrapper& getInstance();

    // Task yönetimi
    bool createTask(const TaskConfig& config,
                   TaskFunction function,
                   void* parameter = nullptr);
                   
    bool deleteTask(const std::string& taskName);
    bool suspendTask(const std::string& taskName);
    bool resumeTask(const std::string& taskName);

    // Kuyruk yönetimi
    bool createQueue(const std::string& queueName,
                    uint32_t queueLength,
                    uint32_t itemSize);
                    
    bool sendToQueue(const std::string& queueName,
                    const void* data,
                    uint32_t timeout = portMAX_DELAY);
                    
    bool receiveFromQueue(const std::string& queueName,
                         void* data,
                         uint32_t timeout = portMAX_DELAY);

    // Semafor yönetimi
    bool createSemaphore(const std::string& semName);
    bool takeSemaphore(const std::string& semName,
                      uint32_t timeout = portMAX_DELAY);
    bool giveSemaphore(const std::string& semName);

    // Bellek yönetimi
    void* allocateMemory(size_t size);
    void freeMemory(void* ptr);

    // Sistem bilgisi
    uint32_t getFreeHeapSize() const;
    uint32_t getMinEverFreeHeapSize() const;
    uint32_t getTaskCount() const;

private:
    RTOSWrapper() = default;
    ~RTOSWrapper() = default;
    RTOSWrapper(const RTOSWrapper&) = delete;
    RTOSWrapper& operator=(const RTOSWrapper&) = delete;

    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace hal
} // namespace asrpro

#endif // ASRPRO_RTOS_WRAPPER_H