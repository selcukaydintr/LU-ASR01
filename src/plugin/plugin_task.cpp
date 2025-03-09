/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: plugin_task.cpp
 * Açıklama: Plugin task yönetim implementasyonu
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#include "plugin/plugin_task.h"
#include "debug/error_handler.h"

namespace asrpro {
namespace plugin {

struct PluginTask::Impl {
    TaskHandle_t taskHandle{nullptr};
    QueueHandle_t dataQueue{nullptr};
    SemaphoreHandle_t mutex{nullptr};
    TaskConfig config;
    bool running{false};
    
    void cleanup() {
        if (taskHandle) {
            vTaskDelete(taskHandle);
            taskHandle = nullptr;
        }
        if (dataQueue) {
            vQueueDelete(dataQueue);
            dataQueue = nullptr;
        }
        if (mutex) {
            vSemaphoreDelete(mutex);
            mutex = nullptr;
        }
        running = false;
    }
};

PluginTask& PluginTask::getInstance() {
    static PluginTask instance;
    if (!instance.pImpl) {
        instance.pImpl = std::make_unique<Impl>();
    }
    return instance;
}

void PluginTask::taskFunction(void* params) {
    auto& instance = getInstance();
    
    while (instance.pImpl->running) {
        // Task işlemleri...
        
        // CPU yükünü azaltmak için bekleme
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
    // Task sonlandırma
    instance.pImpl->cleanup();
    vTaskDelete(nullptr);
}

bool PluginTask::createTask(const TaskConfig& config) {
    pImpl->config = config;
    
    // Mutex oluştur
    pImpl->mutex = xSemaphoreCreateMutex();
    if (!pImpl->mutex) {
        debug::LOG_ERROR("Mutex oluşturulamadı", "PluginTask", 1);
        return false;
    }
    
    // Veri kuyruğu oluştur
    pImpl->dataQueue = xQueueCreate(config.queueSize, sizeof(void*));
    if (!pImpl->dataQueue) {
        debug::LOG_ERROR("Kuyruk oluşturulamadı", "PluginTask", 2);
        return false;
    }
    
    // Task oluştur
    pImpl->running = true;
    BaseType_t result = xTaskCreate(
        taskFunction,
        config.name,
        config.stackSize,
        nullptr,
        static_cast<UBaseType_t>(config.priority),
        &pImpl->taskHandle
    );
    
    if (result != pdPASS) {
        debug::LOG_ERROR("Task oluşturulamadı", "PluginTask", 3);
        pImpl->cleanup();
        return false;
    }
    
    return true;
}

bool PluginTask::deleteTask() {
    if (!pImpl->running) return false;
    
    pImpl->running = false;
    pImpl->cleanup();
    return true;
}

bool PluginTask::suspendTask() {
    if (!pImpl->taskHandle) return false;
    
    vTaskSuspend(pImpl->taskHandle);
    return true;
}

bool PluginTask::resumeTask() {
    if (!pImpl->taskHandle) return false;
    
    vTaskResume(pImpl->taskHandle);
    return true;
}

bool PluginTask::sendData(const void* data, uint32_t size) {
    if (!pImpl->dataQueue) return false;
    
    return xQueueSend(pImpl->dataQueue, &data, pdMS_TO_TICKS(100)) == pdTRUE;
}

bool PluginTask::receiveData(void* data, uint32_t size) {
    if (!pImpl->dataQueue) return false;
    
    return xQueueReceive(pImpl->dataQueue, data, pdMS_TO_TICKS(100)) == pdTRUE;
}

bool PluginTask::isRunning() const {
    return pImpl->running;
}

TaskStatus_t PluginTask::getStatus() const {
    TaskStatus_t status;
    if (pImpl->taskHandle) {
        vTaskGetInfo(pImpl->taskHandle, &status, pdTRUE, eInvalid);
    }
    return status;
}

} // namespace plugin
} // namespace asrpro