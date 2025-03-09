/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: plugin_interface.h
 * Açıklama: Plugin sistem arayüzü
 * Bağımlılıklar: cstdint, string
 * 
 * Versiyon: 0.5.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_PLUGIN_INTERFACE_H
#define ASRPRO_PLUGIN_INTERFACE_H

#include <cstdint>
#include <string>

namespace asrpro {
namespace plugin {

// Plugin API versiyonu
#define ASRPRO_PLUGIN_API_VERSION 0x0500

// Plugin durum kodları
enum class PluginStatus {
    SUCCESS = 0,
    ERROR_INIT = -1,
    ERROR_PROCESS = -2,
    ERROR_CONFIG = -3,
    ERROR_MEMORY = -4
};

// Plugin yapılandırma
struct PluginConfig {
    std::string name;           // Plugin adı
    std::string version;        // Plugin versiyonu
    uint32_t apiVersion;        // API versiyonu
    bool useTurkishASR;        // Türkçe ASR kullanımı
    bool useTurkishTTS;        // Türkçe TTS kullanımı
    std::string modelPath;      // Model dosya yolu
};

// Plugin arayüzü
class IPlugin {
public:
    virtual ~IPlugin() = default;
    
    // Temel işlemler
    virtual PluginStatus init(const PluginConfig& config) = 0;
    virtual PluginStatus deinit() = 0;
    virtual PluginStatus process(const void* input, void* output) = 0;
    
    // Türkçe dil desteği
    virtual PluginStatus processTurkish(const void* input, void* output) = 0;
    virtual PluginStatus setTurkishConfig(const void* config) = 0;
    
    // Durum kontrolü
    virtual bool isInitialized() const = 0;
    virtual const char* getVersion() const = 0;
    virtual const char* getError() const = 0;
};

} // namespace plugin
} // namespace asrpro

#endif // ASRPRO_PLUGIN_INTERFACE_H