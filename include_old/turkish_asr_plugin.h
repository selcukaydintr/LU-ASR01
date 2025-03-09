/**
 * ===========================================================
 * Proje: ASR-PRO Türkçe Konuşma Tanıma Plugini
 * Dosya: turkish_asr_plugin.h
 * Açıklama: ASR-PRO için Türkçe dil desteği plugin çerçevesi
 * 
 * Versiyon: 1.0.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef TURKISH_ASR_PLUGIN_H
#define TURKISH_ASR_PLUGIN_H

#include <cstdint>
#include "bnpu_core.h"
#include "asr_pro_defines.h"

// Plugin API sürümü
#define PLUGIN_API_VERSION 0x0100

// Plugin yapılandırma yapısı
struct TurkishASRConfig {
    uint32_t sampleRate;        // Örnekleme hızı (16000 Hz)
    uint16_t frameSize;         // Çerçeve boyutu (512 samples)
    uint8_t melBands;          // Mel filtre bankası sayısı (40)
    uint8_t mfccCoeffs;        // MFCC katsayı sayısı (13)
    float beamWidth;           // Işın genişliği (3.0)
    bool useGPU;               // GPU kullanımı
};

// Plugin arayüz sınıfı
class TurkishASRPlugin {
public:
    // Plugin başlatma
    virtual bool init(const TurkishASRConfig& config) = 0;
    
    // Model yükleme
    virtual bool loadModel(const char* modelPath) = 0;
    
    // Ses tanıma
    virtual bool recognize(const int16_t* audio, 
                         size_t length,
                         char* text,
                         size_t maxLength) = 0;
    
    // Plugin bilgisi
    virtual const char* getPluginInfo() = 0;
    
    // Plugin sürümü
    virtual uint32_t getVersion() = 0;
    
    // Plugin API sürümü
    virtual uint32_t getAPIVersion() = 0;
    
    // Plugin durumu
    virtual bool getStatus() = 0;
    
    // Plugin kapatma
    virtual void shutdown() = 0;
    
    // Sanal yıkıcı
    virtual ~TurkishASRPlugin() {}

protected:
    TurkishASRConfig config;
    BNPUDriver* bnpu;
};

// Plugin oluşturucu fonksiyon prototipi
extern "C" TurkishASRPlugin* createPlugin();

// Plugin yok edici fonksiyon prototipi  
extern "C" void destroyPlugin(TurkishASRPlugin* plugin);

#endif // TURKISH_ASR_PLUGIN_H