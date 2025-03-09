/asrpro/
│
├── include/                     # Header dosyaları
│   ├── core/                    # YENİ
│   │   └── system_integrator.h  # YENİ
│   ├── plugin/                 # Plugin sistem header'ları
│   │   ├── plugin_api.h        # Plugin API tanımlamaları
│   │   ├── plugin_manager.h    # Plugin yönetici sınıfı
│   │   └── plugin_types.h      # Ortak tip tanımlamaları
│   │
│   ├── audio/                  # Ses işleme header'ları  
│   │   ├── audio_processor.h   # Ses işleme sınıfı
│   │   └── audio_types.h       # Ses veri tipleri
│   │
│   ├── turkish/                # YENİ - Türkçe dil desteği
│   │   ├── turkish_language_processor.h  # YENİ
│   │   ├── turkish_nlp.h      # YENİ - Doğal dil işleme
│   │   ├── turkish_asr.h      # Konuşma tanıma
│   │   ├── turkish_asr_optimizer.h   # YENİ
│   │   └── turkish_tts.h      # Metin okuma
│   │
│   ├── hal/                    # YENİ - HAL katmanı
│   │   ├── hal_layer.h        # YENİ
│   │   └── rtos_wrapper.h     # YENİ
│   │
│   ├── test/                  # YENİ
│   │   └── test_suite.h      # YENİ
│   │
│   ├── sdk/                  # YENİ
│   │   └── sdk_interface.h   # YENİ
│   │   └── sdk_wrapper.h     # YENİ
│   │
│   ├── benchmark/              # YENİ
│   │   ├── benchmark_manager.h # YENİ
│   │   └── performance_metrics.h # YENİ
│   │
│   └── hardware/              # Donanım sürücü header'ları
│       ├── uart_controller.h  # YENİ
│       ├── bnpu_driver.h      # BNPU sürücüsü
│       ├── dma_controller.h   # DMA kontrolcüsü
│       └── uart_driver.h      # UART sürücüsü
│
├── src/                       # Kaynak dosyalar
│   ├── plugin/               # Plugin sistem implementasyonları
│   │   ├── turkish_asr_plugin.cpp
│   │   └── plugin_integration.cpp
│   ├── audio/               # Ses işleme implementasyonları 
│   │   └── audio_processor.cpp
│   └── hardware/           # Donanım sürücü implementasyonları
│       ├── bnpu_driver.cpp
│       └── dma_controller.cpp
│
├── examples/                # Örnek kullanımlar
│   └── basic_recognition/  # Basit ses tanıma örneği
│
├── tests/                    # YENİ
│   ├── test_framework.h      # YENİ
│   ├── test_framework.cpp    # YENİ
│   └── test_config.json     # YENİ
│
├── tests/                  # Test dosyaları
│   ├── unit/              # Birim testleri
│   └── integration/       # Entegrasyon testleri
│
├── docs/                  # Dokümantasyon
│   ├── api/              # API dokümantasyonu
│   ├── changes.md
│   ├── foldertree.md 
│   ├── plugin_roadmap.md
│   ├── roadmap.md
│   └── talimatlar.md
│
├── scripts/              # Build ve yardımcı scriptler
│   ├── build.sh         # Derleme scripti
│   └── test.sh         # Test scripti
│
└── config/             # Yapılandırma dosyaları
    ├── plugin.json    # Plugin yapılandırması
    └── hardware.json  # Donanım yapılandırması