/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: plugin_task.h
 * Açıklama: Plugin task yönetim sistemi
 * Bağımlılıklar: FreeRTOS, plugin_types.h, error_handler.h
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_PLUGIN_TASK_H
#define ASRPRO_PLUGIN_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "plugin_types.h"
#include <memory>

namespace asrpro {
namespace plugin {

// Task öncelikleri
enum class TaskPriority {
    CRITICAL = configMAX_PRIORITIES - 1,  // En yüksek öncelik
    HIGH = configMAX_PRIORITIES - 2,
    MEDIUM = configMAX_PRIORITIES - 3,
    LOW = configMAX_PRIORITIES - 4,
    IDLE = tskIDLE_PRIORITY
};

// Task yapılandırması
struct TaskConfig {
    const char* name;           // Task adı
    uint32_t stackSize;         // Stack boyutu
    TaskPriority priority;      // Öncelik
    uint32_t queueSize;         // Kuyruk boyutu
    bool useGPU;               // GPU kullanımı
    
    TaskConfig() 
        : name("ASRTask")
        , stackSize(4096)
        , priority(TaskPriority::MEDIUM)
        , queueSize(10)
        , useGPU(false)
    {}
};

class PluginTask {
public:
    static PluginTask& getInstance();
    
    // Task yönetimi
    bool createTask(const TaskConfig& config);
    bool deleteTask();
    bool suspendTask();
    bool resumeTask();
    
    // Veri iletişimi
    bool sendData(const void* data, uint32_t size);
    bool receiveData(void* data, uint32_t size);
    
    // Durum kontrolü
    bool isRunning() const;
    TaskStatus_t getStatus() const;

private:
    PluginTask() = default;
    ~PluginTask() = default;
    
    // Task callback
    static void taskFunction(void* params);
    
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace plugin
} // namespace asrpro

#endif // ASRPRO_PLUGIN_TASK_H