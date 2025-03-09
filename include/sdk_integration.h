/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: sdk_integration.h
 * Açıklama: SDK entegrasyon katmanı
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#include "asrpro_system.h"
#include "asrpro_core_eclic.h"
#include "voice_module_uart_protocol.h"
#include "command_info.h"

namespace asrpro {
namespace sdk {

struct SDKConfig {
    uint32_t sampleRate{16000};
    uint16_t frameSize{512};
    bool useVAD{true};
    std::string modelPath;
};

class SDKIntegration {
public:
    bool init(const SDKConfig& config);
    bool process(const AudioData& audio);
    
private:
    VADProcessor vadProcessor;
    FeatureExtractor featureExtractor;
    ASRDecoder decoder;
};

}} // namespace asrpro::sdk