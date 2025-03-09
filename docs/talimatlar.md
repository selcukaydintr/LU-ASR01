### Kodlama ve Proje Yönetimi İlkeleri
1. öncelik ./docs/changes.md
2. öncelik ./docs/talimatlar.md
3. öncelik ./docs/plugin_roadmap.md
4. öncelik ./docs/roadmap.md
5. öncelik ./docs/foldertree.md
---

#### 1️⃣ **Genel Kodlama İlkeleri**
- ✅ **Temiz ve Anlaşılır Kod:** Kodlar temiz, anlaşılır ve yorumlarla desteklenmelidir.
- ✅ **En İyi Uygulamalar:** Kod yazarken mümkünse en iyi uygulamalar (best practices) kullanılmalıdır.
- ✅ **Gereksiz Tekrardan Kaçınma:** Gereksiz tekrar (redundancy) ve kod karmaşasından kaçınılmalıdır.
- ✅ **Optimizasyon:** Her yazılan kod, belirli bir görev için optimize edilmelidir.
- ✅ **Hata Ayıklama Kolaylığı:** Hata ayıklama (debugging) kolaylığı için gerektiğinde log mesajları eklenmelidir.

---

#### 2️⃣ **Kodlama Stili ve Formatlama**
- ✅ **Dil Bağımsız Kurallar:**
  - Düzgün girintileme (indentation) kullanılmalıdır (Python için 4 boşluk, diğer diller için proje standardına uygun).
  - Kod satırları 80-120 karakter arasında olmalıdır.
  - Fonksiyon ve değişken adları anlamlı olmalıdır.
  - Tek satırda okunması zor ifadeler, birden fazla satıra bölünmelidir.
  - Gereksiz boşluk ve satır eklememelidir.
- ✅ **Dil Bazlı Formatlama:**
  - **Python:** `black` veya `autopep8` kullanılmalıdır.
  - **JavaScript/TypeScript:** `Prettier` veya `ESLint` aktif olmalıdır.
  - **C/C++:** `clang-format` standartları takip edilmelidir.
  - **HTML/CSS:** `Beautify` veya `Prettier` kullanılmalıdır.

---

#### 3️⃣ **Hata Ayıklama ve Uygun Kod Önerileri**
- ✅ **VS Code Entegrasyonu:** VS Code’un hata yakalama (Linting) araçları ile entegre olmalıdır.
  - **Python:** `pylint`, `flake8` veya `mypy`
  - **JavaScript:** `ESLint`
  - **C/C++:** `cppcheck`
  - **HTML/CSS:** `stylelint`
- ✅ **Hata Tespiti ve Çözüm:**
  - Hatanın sebebi açıklanmalıdır.
  - Mümkünse çözüm önerisi sunulmalıdır.
  - Alternatif kod örneği verilmelidir.
- ✅ **Hata Mesajları:** Hata mesajları mümkün olduğunca açık olmalıdır.
  - **Yanlış:** `SyntaxError: Unexpected token`
  - **Doğru:** `SyntaxError: Beklenmedik bir karakter bulundu. Muhtemelen eksik bir kapanış parantezi var.`

---

#### 4️⃣ **Yorum Satırları ve Dokümantasyon**
- ✅ **Yorumlar:** Kodun ne yaptığını açıklayan yorumlar eklenmelidir.
- ✅ **Dokümantasyon:** Fonksiyonlar ve sınıflar için dokümantasyon yazılmalıdır.
- ✅ **Örnekler:**
  - **Python:**
    ```python
    def hesapla_faiz(anapara: float, oran: float, yil: int) -> float:
        """
        Belirtilen yıllık faiz oranına göre toplam miktarı hesaplar.
        
        Args:
            anapara (float): Başlangıç miktarı.
            oran (float): Yıllık faiz oranı (% cinsinden).
            yil (int): Faizin uygulanacağı yıl sayısı.
        
        Returns:
            float: Hesaplanan toplam miktar.
        """
        return anapara * (1 + oran / 100) ** yil
    ```
  - **JavaScript:**
    ```javascript
    /**
     * Belirtilen yıllık faiz oranına göre toplam miktarı hesaplar.
     * @param {number} anapara - Başlangıç miktarı.
     * @param {number} oran - Yıllık faiz oranı (% cinsinden).
     * @param {number} yil - Faizin uygulanacağı yıl sayısı.
     * @returns {number} Hesaplanan toplam miktar.
     */
    function hesaplaFaiz(anapara, oran, yil) {
        return anapara * Math.pow(1 + oran / 100, yil);
    }
    ```

---

#### 5️⃣ **Otomatik Tamamlama ve Akıllı Öneriler**
- ✅ **IntelliSense:** VS Code’un IntelliSense özelliğinden faydalanmalıdır.
- ✅ **Filtreleme:** Kütüphaneler ve fonksiyonlar önerilirken, gereksiz olanlar filtrelenmelidir.
- ✅ **Geçersiz Fonksiyon Çağrıları:** Yanlış veya geçersiz fonksiyon çağrıları önlenmelidir.
- ✅ **Örnek:**
  - **Yanlış:**
    ```python
    import pandas
    df = pandas.DataFrame()
    ```
  - **Doğru:**
    ```python
    import pandas as pd
    df = pd.DataFrame()
    ```

---

#### 6️⃣ **VS Code Terminal ve Git Kullanımı**
- ✅ **Terminal Komutları:** Terminalde çalıştırılacak komutlar önerilirken:
  - Mevcut işletim sistemi (Windows, macOS, Linux) dikkate alınmalıdır.
  - Mevcut çalışma ortamı (Python, Node.js, C++) göz önüne alınmalıdır.
- ✅ **Python Sanal Ortam Örneği:**
  ```sh
  python -m venv venv
  source venv/bin/activate  # (Linux/macOS)
  venv\Scripts\activate     # (Windows)
  ```
- ✅ **Git Entegrasyonu:**
  ```sh
  git init
  git add .
  git commit -m "İlk commit"
  git push origin main
  ```
- ✅ **.gitignore:** Eğer `.gitignore` yoksa, oluşturulması önerilmelidir.

---

#### 7️⃣ **Kod Güvenliği ve Performans Optimizasyonu**
- ✅ **Kod Güvenliği:**
  - SQL injection önlenmelidir.
  - Kullanıcı girişleri (input validation) kontrol edilmelidir.
  - Hassas veriler (şifre, API anahtarları) açıkta bırakılmamalıdır.
- ✅ **Performans Optimizasyonu:**
  - Gereksiz döngüler ve pahalı işlemler azaltılmalıdır.
  - Bellek tüketimi optimize edilmelidir.
  - Mümkünse önbellekleme (caching) önerilmelidir.
- ✅ **Örnek:**
  - **Kötü Performans:**
    ```python
    def remove_duplicates(lst):
        new_list = []
        for item in lst:
            if item not in new_list:
                new_list.append(item)
        return new_list
    ```
  - **Daha İyi Performans:**
    ```python
    def remove_duplicates(lst):
        return list(set(lst))
    ```

---

#### 8️⃣ **Yapay Zekanın Kodlama Davranışları**
- ✅ **Açıklamalı Kod:** Kodlar açıklamalarla birlikte sunulmalıdır.
- ✅ **En Uygun Çözüm:** Eğer birden fazla çözüm varsa, en uygun olan önerilmelidir.
- ✅ **Basitlik:** Gereksiz ve aşırı karmaşık kodlardan kaçınılmalıdır.
- ✅ **Belirsizlik:** Eğer bir konu belirsizse, ek bilgi istenmelidir.
  - **Örnek:** "Kullandığınız çerçeve nedir? Flask mı, Django mu?"

---

### Dosya ve Değişiklik Yönetimi

---

#### 1️⃣ **Dosya Oluşturma Kuralları**
- ✅ **foldertree.md Kontrolü:** Yeni bir dosya oluşturulmadan önce `./docs/foldertree.md` dosyası kontrol edilmelidir.
- ✅ **Dosya İsmi Kontrolü:** Eğer aynı isimde bir dosya varsa, tekrar oluşturulmaz.
- ✅ **foldertree.md Güncelleme:** Yeni oluşturulan her dosyanın ismi `./docs/foldertree.md` dosyasına eklenmelidir.
- ✅ **Örnek `./docs/foldertree.md` Formatı:**
  ```plaintext
  /robot_project/
  │── src/
  │   ├── main.cpp
  │   ├── motor_control.cpp
  │   ├── sensor_read.cpp
  │
  │── include/
  │   ├── motor_control.h
  │   ├── sensor_read.h
  │── config/
  │   ├── settings.json
  │
  │── logs/
  │   ├── system.log
  ```

---

#### 2️⃣ **Değişikliklerin `./docs/changes.md` Dosyasına Kaydedilmesi**
- ✅ **Değişiklik Kaydı:** Her değişiklik `./docs/changes.md` dosyasına kaydedilmelidir.
- ✅ **Değişiklik Formatı:** Değişiklikler, dosya başlığı ile birlikte kayıt edilmelidir.
- ✅ **Örnek `./docs/changes.md` Formatı:**
  ```plaintext
  # [2025-03-01] motor_controller.py Güncelleme
  - [1.3.0] PID algoritması eklendi. (Sebep: Daha stabil hız kontrolü)
  - [1.2.1] Hata giderildi. (Sebep: Motor yönlendirmesinde terslik vardı)

  # [2025-03-02] settings.json Değiştirildi
  - `log_level` parametresi "DEBUG" olarak değiştirildi.
  ```

---

#### 3️⃣ **Dosya Başlığı ve Versiyon Bilgisi**
- ✅ **Dosya Başlığı:** Her dosyanın başında dosyanın içeriği, bağımlılıkları ve versiyon bilgisi bulunmalıdır.
- ✅ **Versiyon Takibi:** Her dosyada bir versiyon numarası ve değişikliklerin kaydı bulunmalıdır.
- ✅ **Örnek Python Dosya Başlığı:**

/**
 * ===========================================================
 * # Proje: ASR-PRO Plugin Sistemi
 * # Dosya: dma_controller.h
 * # Açıklama: DMA kontrolcü sınıfı header dosyası
 * # Bağımlılıklar: stdint.h, memory
 * # Bağlı Dosyalar: bnpu_driver.h, uart_driver.h
 * 
 * # Versiyon: 0.1.0
 * # Değişiklikler:
 * # - [0.1.0] DMA kontrol sınıfı oluşturuldu
 * # - [0.1.0] Temel DMA işlevleri eklendi
 * #
 * # Yazar: Github Copilot
 * # Tarih: 2025-03-09
 * ===========================================================
 */



---

#### 4️⃣ **Kod Modülerliği ve Bağımlılık Yönetimi**
- ✅ **Modülerlik:** Kod parçaları mümkün olduğunca fonksiyonlara bölünmelidir.
- ✅ **Bağımlılık Yönetimi:** Bağımlılıklar, merkezi bir yapılandırma dosyasından yönetilmelidir.
- ✅ **Örnek Yapılandırma Dosyası (`config.json`):**
  ```json
  {
      "motor_max_speed": 100,
      "sensor_update_rate": 0.5,
      "log_level": "DEBUG"
  }
  ```

---

#### 5️⃣ **Gelişmiş Hata Yönetimi ve Loglama**
- ✅ **Hata Yönetimi:** Kodun hata yönetimi iyi yapılmalıdır.
- ✅ **Loglama:** Hata mesajları anlaşılır olmalı ve sistem loglanmalıdır.
- ✅ **Örnek Python Loglama:**
  ```python
  import logging

  logging.basicConfig(filename='system.log', level=logging.DEBUG)
  logging.debug('Bu bir debug mesajıdır.')
  ```

---

### Genel Akış Şeması
1. **Dosya Oluşturma:** Dosya oluşturulmadan önce `./docs/foldertree.md` kontrol edilir.
2. **Değişiklik Kaydı:** Değişiklik yapılmadan önce `./docs/changes.md` kontrol edilir.
3. **Versiyon Takibi:** Her değişiklik dosya başlığına ve `./docs/changes.md` dosyasına kaydedilir.
4. **Kod Modülerliği:** Kodlar modüler ve bağımlılıklar merkezi olarak yönetilir.
5. **Hata Yönetimi:** Hata mesajları açık ve loglanmış olmalıdır.
6. **Temel Donanım:** Esp32 Cam > Uart > Rpi Pico > uart > asrpro
7. **İşletim Sistemi:** FreeRTOS ve Hall Katmanı
8. **Yol Haritası:** Proje ilerlemesi akademik ve teknik olarak `./docs/roadmap.md` dosyasına işlenecektir.


Bu talimatlar, kod kalitesini artırmak ve proje yönetimini daha düzenli hale getirmek için tasarlanmıştır. Her adımın takip edilmesi, projenin daha verimli ve sürdürülebilir olmasını sağlayacaktır.

