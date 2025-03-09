#ifndef ASR_PRO_PLUGIN_API_H
#define ASR_PRO_PLUGIN_API_H

#include <cstdint>
#include "plugin_types.h"

namespace asrpro {
namespace plugin {

// Plugin API versiyonu
#define PLUGIN_API_VERSION 0x0100

// Plugin durum kodları
enum class PluginStatus {
    SUCCESS = 0,
    ERROR_INIT = -1,
    ERROR_CONFIG = -2,
    ERROR_PROCESS = -3
};

// Plugin yapılandırma yapısı  
struct PluginConfig {
    uint32_t sampleRate;      // Örnekleme hızı
    uint16_t frameSize;       // Çerçeve boyutu
    uint8_t channels;         // Kanal sayısı
    bool useGPU;             // GPU kullanımı
};

// Plugin arayüzü
class IPlugin {
public:
    virtual ~IPlugin() = default;
    
    // Temel fonksiyonlar
    virtual PluginStatus init(const PluginConfig& config) = 0;
    virtual PluginStatus process(const void* input, void* output) = 0;
    virtual PluginStatus shutdown() = 0;
    
    // Plugin bilgileri
    virtual const char* getName() const = 0;
    virtual const char* getVersion() const = 0;
    virtual uint32_t getApiVersion() const = 0;
};

// Plugin oluşturucu/yok edici
extern "C" {
    IPlugin* createPlugin();
    void destroyPlugin(IPlugin* plugin);
}

} // namespace plugin
} // namespace asrpro

#endif // ASR_PRO_PLUGIN_API_H