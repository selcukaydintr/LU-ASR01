#ifndef ASR_PRO_BNPU_DRIVER_H
#define ASR_PRO_BNPU_DRIVER_H

#include <cstdint>

namespace asrpro {
namespace hardware {

struct BNPUConfig {
    uint32_t inputSize;      // Giriş katmanı boyutu
    uint32_t hiddenSize;     // Gizli katman boyutu
    uint32_t outputSize;     // Çıkış katmanı boyutu
    uint8_t numLayers;       // RNN katman sayısı
};

class BNPUDriver {
public:
    static BNPUDriver& getInstance();
    
    bool init(const BNPUConfig& config);
    bool process(const void* input, void* output);
    void shutdown();

private:
    BNPUDriver() = default;
    ~BNPUDriver() = default;
    BNPUDriver(const BNPUDriver&) = delete;
    BNPUDriver& operator=(const BNPUDriver&) = delete;
};

} // namespace hardware
} // namespace asrpro

#endif // ASR_PRO_BNPU_DRIVER_H