# ASR-PRO Plugin Sistemi Değişiklik Kayıtları

## [2025-03-09] Proje Başlangıcı
- [0.1.0] Temel proje yapısı oluşturuldu
- [0.1.0] Plugin tipleri tanımlandı (plugin_types.h)

# [2025-03-09] Audio İşleme Modülleri Eklendi
- [0.1.0] Temel ses veri tipleri tanımlandı (audio_types.h)
- [0.1.0] Ses işleme sınıfı oluşturuldu (audio_processor.h)
- [0.1.0] MFCC öznitelik çıkarımı eklendi

# [2025-03-09] DMA Kontrolcü Eklendi
- [0.1.0] DMA kontrolcü sınıfı oluşturuldu
- [0.1.0] Temel DMA işlevleri eklendi
- [0.1.0] Kanal yönetimi implementasyonu tamamlandı

# [2025-03-09] DMA Kontrolcü Modülü Eklendi
- [0.1.0] DMA kontrolcü header dosyası oluşturuldu (dma_controller.h)
- [0.1.0] DMA kontrolcü implementasyonu eklendi (dma_controller.cpp)
- [0.1.0] Bellek yönetimi optimizasyonları yapıldı

# [2025-03-09] UART Arayüzü Eklendi
- [0.1.0] UART iletişim arayüzü tanımlandı
- [0.1.0] ASR-PRO UART implementasyonu eklendi
- [0.1.0] DMA desteği eklendi

# [2025-03-09] Ses İşleme Modülü Eklendi
- [0.1.0] AudioProcessor sınıfı implementasyonu
- [0.1.0] MFCC öznitelik çıkarımı temel yapısı
- [0.1.0] DMA entegrasyonu eklendi

# [2025-03-09] BNPU Sürücü İmplementasyonu
- [0.1.0] BNPU sürücüsü temel yapısı oluşturuldu
- [0.1.0] DMA entegrasyonu tamamlandı
- [0.1.0] Sinir ağı işlem desteği eklendi

# [2025-03-09] Plugin İmplementasyonu
- [0.1.0] TurkishASRPlugin sınıfı implementasyonu
- [0.1.0] Audio işleme ve BNPU entegrasyonu
- [0.1.0] Model yükleme ve tanıma işlevleri

# [2025-03-09] Debug Sistemi Eklendi
- [0.1.0] DebugManager sınıfı oluşturuldu
- [0.1.0] Performans ölçüm sistemi eklendi
- [0.1.0] Loglama sistemi implementasyonu

# [2025-03-09] Test Sistemi Eklendi
- [0.1.0] Ana test yapısı oluşturuldu
- [0.1.0] Mock sınıfları eklendi
- [0.1.0] Birim testleri eklendi
- [0.1.0] Performans testleri eklendi

# [2025-03-09] Performans İzleme Modülü Eklendi
- [0.1.0] PerformanceMonitor sınıfı oluşturuldu
- [0.1.0] Performans metrik takibi eklendi
- [0.1.0] Optimizasyon önerileri sistemi eklendi

# [2025-03-09] Entegrasyon Modülü Eklendi
- [0.1.0] PluginIntegration sınıfı oluşturuldu
- [0.1.0] Plugin yükleme ve ses işleme fonksiyonları eklendi
- [0.1.0] Performans izleme entegrasyonu yapıldı

# [2025-03-09] Örnek Kullanım Eklendi
- [0.1.0] Basit ses tanıma örneği oluşturuldu
- [0.1.0] Performans izleme entegrasyonu eklendi
- [0.1.0] Hata yönetimi ve raporlama eklendi

# [2025-03-09] Build Sistemi Eklendi
- [0.1.0] CMake build sistemi oluşturuldu
- [0.1.0] Test entegrasyonu yapıldı
- [0.1.0] Windows build script eklendi

# [2025-03-09] Proje Yapısı Güncelleme
- [0.1.0] Eksik dizin yapısı oluşturuldu
- [0.1.0] Yol haritası dökümanları eklendi
- [0.1.0] Plugin sistemi ana yapısı tanımlandı

# [2025-03-09] Doküman Güncellemeleri
- [0.1.0] Plugin yol haritası oluşturuldu
- [0.1.0] Akademik ve teknik yol haritası eklendi
- [0.1.0] Dizin yapısı güncellendi

# [2025-03-09] Test ve Hata Yakalama Sistemi
- [0.1.1] Test altyapısı oluşturuldu
- [0.1.1] Hata yakalama mekanizması eklendi
- [0.1.1] Loglama sistemi entegre edildi

# [2025-03-09] FreeRTOS Task Sistemi Eklendi
- [0.1.0] PluginTask sınıfı oluşturuldu (plugin_task.h)
- [0.1.0] Task yönetimi implementasyonu eklendi (plugin_task.cpp)
- [0.1.0] FreeRTOS entegrasyonu tamamlandı

# [2025-03-09] Türkçe Dil Desteği Eklendi
- [0.1.0] Türkçe ASR modülü eklendi
- [0.1.0] Türkçe TTS modülü eklendi
- [0.1.0] Fonem seti ve telaffuz kuralları tanımlandı

# [2025-03-09] Türkçe Dil Desteği Entegrasyonu
- [0.2.0] Türkçe ASR modülü eklendi (include/turkish/turkish_asr.h)
- [0.2.1] Türkçe TTS modülü eklendi (include/turkish/turkish_tts.h)
- [0.2.2] Türkçe fonem ve akustik model entegrasyonu tamamlandı

# [2025-03-09] Türkçe Dil Desteği ve Ses İşleme
### include/turkish/turkish_nlp.h
- [0.3.0] Türkçe doğal dil işleme sınıfı eklendi
- [0.3.1] Türkçe morfolojik analiz desteği eklendi

### src/turkish/turkish_nlp.cpp
- [0.3.0] Türkçe dil işleme implementasyonu
- [0.3.1] Fonetik analiz ve sentez eklendi

# [2025-03-09] Türkçe Dil Desteği ve Ses İşleme - v0.3.2
- [0.3.2] Türkçe ASR performans optimizasyonu yapıldı
- [0.3.2] BNPU entegrasyonu iyileştirildi
- [0.3.2] DMA transfer yönetimi güncellendi

# [2025-03-09] Türkçe ASR İyileştirmeleri
### include/turkish/turkish_language_processor.h
- [0.4.0] Türkçe dil işleme sınıfı güncellendi
- [0.4.1] Dialect desteği eklendi
- [0.4.2] BNPU optimizasyonları yapıldı

# [2025-03-09] Sistem Entegrasyonu Güncellemesi
### src/plugin/plugin_manager.cpp
- [0.5.0] Plugin yönetim sistemi güncellendi
- [0.5.1] Dinamik yükleme desteği eklendi

### include/plugin/plugin_interface.h
- [0.5.0] Plugin arayüzü genişletildi
- [0.5.1] Türkçe dil desteği entegrasyonu

# [2025-03-09] Yol Haritası ve Plugin Sistemi Güncellemesi
### docs/roadmap.md
- [0.5.0] Akademik hedefler güncellendi
- [0.5.0] FreeRTOS entegrasyon planı eklendi

### docs/plugin_roadmap.md
- [0.5.0] Plugin sistemi kilometre taşları güncellendi
- [0.5.0] Türkçe ASR hedefleri detaylandırıldı

# [2025-03-09] HAL Katmanı Entegrasyonu
### include/hal/hal_layer.h
- [0.6.0] HAL katmanı arayüzü oluşturuldu
- [0.6.1] UART ve DMA soyutlaması eklendi

### src/hal/hal_layer.cpp
- [0.6.0] HAL katmanı implementasyonu
- [0.6.1] Donanım soyutlama katmanı eklendi

# [2025-03-09] UART ve DMA Entegrasyonu
### include/hardware/uart_controller.h
- [0.7.0] UART kontrolcü sınıfı oluşturuldu
- [0.7.1] ESP32 ve RPi Pico protokol desteği eklendi

# [2025-03-09] FreeRTOS ve HAL Katmanı Entegrasyonu
### include/hal/rtos_wrapper.h
- [0.8.0] FreeRTOS sarmalayıcı sınıfı oluşturuldu
- [0.8.1] Task ve kuyruk yönetimi eklendi

### src/hal/rtos_wrapper.cpp
- [0.8.0] FreeRTOS entegrasyonu tamamlandı
- [0.8.1] UART ve DMA için thread-safe işlemler eklendi

# [2025-03-09] ESP32 ve RPi Pico Entegrasyonu
### include/hardware/esp32_interface.h
- [0.9.0] ESP32 Cam iletişim arayüzü oluşturuldu
- [0.9.1] Kamera veri akışı yönetimi eklendi

### include/hardware/rpi_pico_interface.h
- [0.9.0] RPi Pico iletişim arayüzü oluşturuldu
- [0.9.1] UART protokol yönetimi eklendi

# [2025-03-09] SDK Entegrasyonu ve Test Altyapısı
### include/sdk/sdk_wrapper.h
- [1.0.0] SDK sarmalayıcı sınıfı oluşturuldu
- [1.0.1] SDK test altyapısı eklendi

### src/sdk/sdk_wrapper.cpp
- [1.0.0] SDK entegrasyon katmanı implementasyonu
- [1.0.1] Birim testleri eklendi

# [2025-03-09] SDK ve Test Modülleri Entegrasyonu
### include/test/test_suite.h
- [1.1.0] Test suite sınıfı oluşturuldu
- [1.1.1] Benchmark testleri eklendi

### include/sdk/sdk_interface.h
- [1.1.0] SDK arayüz sınıfı eklendi
- [1.1.1] SDK performans optimizasyonları yapıldı

# [2025-03-09] Ana Sistem Entegrasyonu ve Örnek Uygulamalar
### include/core/system_integrator.h
- [1.2.0] Sistem entegrasyon sınıfı oluşturuldu
- [1.2.1] SDK ve Plugin entegrasyonu eklendi