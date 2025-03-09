/**
 * ===========================================================
 * Proje: Zuzu v1 - Türkçe Dil Modeli
 * Dosya: turkish_model.h
 * Açıklama: ASR-PRO için Türkçe dil modeli tanımları
 * ===========================================================
 */

 class TurkishModel {
    public:
        struct PhoneticModel {
            std::vector<std::string> phonemes;
            std::map<std::string, float> phonemeProbs;
            std::map<std::pair<std::string, std::string>, float> transitionProbs;
        } phoneticModel;
    
        struct AcousticModel {
            uint32_t sampleRate = 16000;
            uint16_t frameSize = 512;
            uint16_t hopSize = 256;
            uint8_t melBands = 40;
            uint8_t mfccCoeffs = 13;
        } acousticModel;
    
        struct LanguageModel {
            std::map<std::string, float> unigramProbs;
            std::map<std::string, float> bigramProbs;
            std::map<std::string, float> trigramProbs;
            float grammarWeight = 0.8f;
        } languageModel;
    };
    
    /**
     * ===========================================================
     * Proje: Zuzu v1 - BNPU Çekirdek Modülü
     * Dosya: bnpu_core.h
     * Açıklama: ASR-PRO için BNPU donanım soyutlama katmanı
     * 
     * Versiyon: 1.0.0
     * ===========================================================
     */
    
    #ifndef BNPU_CORE_H
    #define BNPU_CORE_H
    
    #include <cstdint>
    
    // BNPU Donanım Adresleri
    #define BNPU_BASE           0x40000000
    #define BNPU_CTRL           (BNPU_BASE + 0x00)
    #define BNPU_STATUS         (BNPU_BASE + 0x04)
    #define BNPU_CONFIG         (BNPU_BASE + 0x08)
    #define BNPU_WEIGHT_ADDR    (BNPU_BASE + 0x0C)
    #define BNPU_INPUT_ADDR     (BNPU_BASE + 0x10)
    #define BNPU_OUTPUT_ADDR    (BNPU_BASE + 0x14)
    
    // BNPU Durum Bitleri
    #define BNPU_STATUS_READY   0x01
    #define BNPU_STATUS_BUSY    0x02
    #define BNPU_STATUS_ERROR   0x04
    #define BNPU_STATUS_DONE    0x08
    
    // BNPU Yapılandırma Yapısı
    struct BNPU_Config {
        uint32_t inputSize;     // Giriş katmanı boyutu
        uint32_t hiddenSize;    // Gizli katman boyutu
        uint32_t outputSize;    // Çıkış katmanı boyutu
        uint8_t numLayers;      // RNN katman sayısı
        float learningRate;     // Öğrenme oranı
        float dropoutRate;      // Dropout oranı
    };
    
    // BNPU Donanım Sürücüsü
    class BNPUDriver {
    public:
        static bool BNPU_Init(const BNPU_Config* config) {
            // BNPU donanımını başlat
            volatile uint32_t* ctrl = (volatile uint32_t*)BNPU_CTRL;
            volatile uint32_t* status = (volatile uint32_t*)BNPU_STATUS;
            
            // Reset BNPU
            *ctrl = 0x1;
            
            // Hazır olana kadar bekle
            while ((*status & BNPU_STATUS_READY) == 0) {}
            
            // Yapılandırmayı yükle
            return BNPU_Configure(config);
        }
        
        static bool BNPU_Configure(const BNPU_Config* config) {
            volatile uint32_t* bnpuConfig = (volatile uint32_t*)BNPU_CONFIG;
            
            // Yapılandırma verilerini yükle
            *bnpuConfig = (config->inputSize << 24) |
                         (config->hiddenSize << 16) |
                         (config->outputSize << 8) |
                         (config->numLayers);
                         
            return true;
        }
        
        static void BNPU_EnableAcceleration() {
            volatile uint32_t* ctrl = (volatile uint32_t*)BNPU_CTRL;
            *ctrl |= 0x2;  // Hızlandırma biti
        }
        
        static void BNPU_ConfigureCache() {
            volatile uint32_t* ctrl = (volatile uint32_t*)BNPU_CTRL;
            *ctrl |= 0x4;  // Önbellek yapılandırma biti
        }
        
        static bool BNPU_LoadWeights(const void* weights, size_t size) {
            volatile uint32_t* weightAddr = (volatile uint32_t*)BNPU_WEIGHT_ADDR;
            
            // DMA ile ağırlıkları yükle
            return DMA_Transfer(weights, (void*)weightAddr, size);
        }
        
        static bool BNPU_Process(const void* input, void* output) {
            volatile uint32_t* status = (volatile uint32_t*)BNPU_STATUS;
            volatile uint32_t* inputAddr = (volatile uint32_t*)BNPU_INPUT_ADDR;
            volatile uint32_t* outputAddr = (volatile uint32_t*)BNPU_OUTPUT_ADDR;
            
            // Giriş verilerini yükle
            *inputAddr = (uint32_t)input;
            
            // İşlemi başlat
            volatile uint32_t* ctrl = (volatile uint32_t*)BNPU_CTRL;
            *ctrl |= 0x8;
            
            // İşlem tamamlanana kadar bekle
            while ((*status & BNPU_STATUS_DONE) == 0) {
                if (*status & BNPU_STATUS_ERROR) {
                    return false;
                }
            }
            
            // Sonuçları al
            return DMA_Transfer((void*)*outputAddr, output, sizeof(float) * outputSize);
        }
    };
    
    #endif // BNPU_CORE_H