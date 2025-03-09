/**
 * ===========================================================
 * Proje: ASR-PRO Türkçe Plugin Sistemi
 * Dosya: plugin_types.h
 * Açıklama: Plugin sistem tipleri ve sabitleri
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_PLUGIN_TYPES_H
#define ASRPRO_PLUGIN_TYPES_H

#include <cstdint>

namespace asrpro {

// Plugin API versiyonu
constexpr uint32_t PLUGIN_API_VERSION = 0x00000100; // v1.0.0

// Plugin durum kodları
enum class PluginStatus {
    SUCCESS = 0,
    ERROR_INIT = -1,
    ERROR_CONFIG = -2,
    ERROR_PROCESS = -3,
    ERROR_MEMORY = -4,
    ERROR_HARDWARE = -5
};

// Plugin yapılandırma yapısı
struct PluginConfig {
    uint32_t sampleRate;     // Örnekleme hızı (16000 Hz)
    uint16_t frameSize;      // Çerçeve boyutu (512 samples)
    uint8_t channels;        // Kanal sayısı
    bool useGPU;            // GPU kullanımı
    
    // Varsayılan değerler
    PluginConfig() 
        : sampleRate(16000)
        , frameSize(512)
        , channels(1)
        , useGPU(false)
    {}
};

} // namespace asrpro

#endif // ASRPRO_PLUGIN_TYPES_H