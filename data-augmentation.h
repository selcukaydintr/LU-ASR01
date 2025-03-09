/**
 * ===========================================================
 * Proje: Zuzu v1 - Türkçe ASR Veri Artırma Modülü
 * Dosya: audio_data_augmentation.h
 * Açıklama: Türkçe konuşma tanıma için otomatik veri artırma
 * 
 * Versiyon: 1.0.0
 * ===========================================================
 */

#include <vector>
#include <random>
#include <string>
#include "audio_buffer.h"

class AudioDataAugmentation {
private:
    std::random_device rd;
    std::mt19937 gen{rd()};
    
    // Konfigürasyon parametreleri
    struct Config {
        // Hız değişimi (pitch etkilemeden)
        float timeStretchMin = 0.85f;
        float timeStretchMax = 1.15f;
        
        // Pitch değişimi
        float pitchShiftMin = -2.0f; // semitone
        float pitchShiftMax = 2.0f;  // semitone
        
        // Gürültü ekleme 
        float noiseLevel = 0.05f;
        
        // Oda simülasyonu
        float roomReverbMin = 0.1f;
        float roomReverbMax = 0.3f;
        
        // Frekans maskeleme
        int freqMaskCount = 2;
        int freqMaskWidth = 20; // Mel bands
        
        // Zaman maskeleme
        int timeMaskCount = 2;
        int timeMaskWidth = 100; // frames
        
        // Spektrogram rastgele taşıma
        float specAugDeltaMax = 0.2f;
    } config;
    
    // Farklı ortam gürültüleri
    std::vector<AudioBuffer> noiseProfiles;
    
    // Farklı oda yankı profilleri
    std::vector<AudioBuffer> roomIRs;

public:
    AudioDataAugmentation() {
        // Varsayılan gürültü profillerini yükle
        loadNoiseProfiles();
        
        // Oda yankı profillerini yükle
        loadRoomIRs();
    }
    
    void loadNoiseProfiles() {
        // Çeşitli ortam gürültülerini yükle
        noiseProfiles.push_back(loadAudio("noise/cafe.wav"));
        noiseProfiles.push_back(loadAudio("noise/street.wav"));
        noiseProfiles.push_back(loadAudio("noise/car.wav"));
        noiseProfiles.push_back(loadAudio("noise/home.wav"));
        noiseProfiles.push_back(loadAudio("noise/rain.wav"));
    }
    
    void loadRoomIRs() {
        // Farklı oda yankı profillerini yükle
        roomIRs.push_back(loadAudio("reverb/small_room.wav"));
        roomIRs.push_back(loadAudio("reverb/medium_room.wav"));
        roomIRs.push_back(loadAudio("reverb/large_room.wav"));
        roomIRs.push_back(loadAudio("reverb/hall.wav"));
    }
    
    AudioBuffer loadAudio(const std::string& path) {
        // Ses dosyasını yükle
        // Gerçek implementasyon ses dosyası yükleme kütüphanesine bağlı olacaktır
        AudioBuffer buffer;
        // AudioLoader::load(path, buffer);
        return buffer;
    }
    
    // Hız değişimi (pitch korunarak)
    AudioBuffer timeStretch(const AudioBuffer& input) {
        std::uniform_real_distribution<float> dist(config.timeStretchMin, config.timeStretchMax);
        float stretchFactor = dist(gen);
        
        AudioBuffer output;
        // Phase vocoder kullanarak hız değişimi uygula
        // output = PhaseVocoder::stretch(input, stretchFactor);
        return output;
    }
    
    // Perde (pitch) değişimi 
    AudioBuffer pitchShift(const AudioBuffer& input) {
        std::uniform_real_distribution<float> dist(config.pitchShiftMin, config.pitchShiftMax);
        float semitones = dist(gen);
        
        AudioBuffer output;
        // STFT ve phase vocoder kullanarak pitch shift uygula
        // output = PhaseVocoder::shiftPitch(input, semitones);
        return output;
    }
    
    // Gürültü ekleme
    AudioBuffer addNoise(const AudioBuffer& input) {
        // Rastgele bir gürültü profili seç
        std::uniform_int_distribution<int> distProfile(0, noiseProfiles.size() - 1);
        int profileIdx = distProfile(gen);
        
        std::uniform_real_distribution<float> distLevel(0, config.noiseLevel);
        float level = distLevel(gen);
        
        AudioBuffer output = input;
        // Seçilen gürültüyü belirtilen seviyede ekle
        // AudioMixer::addNoise(output, noiseProfiles[profileIdx], level);
        return output;
    }
    
    // Yankı ekleme (oda simülasyonu)
    AudioBuffer addReverb(const AudioBuffer& input) {
        // Rastgele bir oda yankı profili seç
        std::uniform_int_distribution<int> distRoom(0, roomIRs.size() - 1);
        int roomIdx = distRoom(gen);
        
        std::uniform_real_distribution<float> distLevel(config.roomReverbMin, config.roomReverbMax);
        float level = distLevel(gen);
        
        AudioBuffer output;
        // Convolution reverb uygula
        // Convolve::apply(input, roomIRs[roomIdx], level, output);
        return output;
    }
    
    // Spektrogram frekans maskeleme (SpecAugment)
    FeatureMatrix freqMask(const FeatureMatrix& features) {
        FeatureMatrix output = features;
        
        // Belirtilen sayıda frekans maskesi uygula
        for (int i = 0; i < config.freqMaskCount; i++) {
            std::uniform_int_distribution<int> distFreq(0, features.rows() - config.freqMaskWidth);
            int f0 = distFreq(gen);
            
            // Frekans bandını maskele (sıfırla)
            for (int f = f0; f < f0 + config.freqMaskWidth && f < features.rows(); f++) {
                for (int t = 0; t < features.cols(); t++) {
                    output(f, t) = 0.0f;
                }
            }
        }
        
        return output;
    }
    
    // Spektrogram zaman maskeleme (SpecAugment)
    FeatureMatrix timeMask(const FeatureMatrix& features) {
        FeatureMatrix output = features;
        
        // Belirtilen sayıda zaman maskesi uygula
        for (int i = 0; i < config.timeMaskCount; i++) {
            std::uniform_int_distribution<int> distTime(0, features.cols() - config.timeMaskWidth);
            int t0 = distTime(gen);
            
            // Zaman dilimini maskele (sıfırla)
            for (int t = t0; t < t0 + config.timeMaskWidth && t < features.cols(); t++) {
                for (int f = 0; f < features.rows(); f++) {
                    output(f, t) = 0.0f;
                }
            }
        }
        
        return output;
    }
    
    // Spektrogram değer taşıma (spectrum augmentation)
    FeatureMatrix specAugment(const FeatureMatrix& features) {
        FeatureMatrix output = features;
        
        std::uniform_real_distribution<float> dist(-config.specAugDeltaMax, config.specAugDeltaMax);
        float delta = dist(gen);
        
        // Tüm spektrograma offset ekle (ve 0-1 aralığında tut)
        for (int f = 0; f < features.rows(); f++) {
            for (int t = 0; t < features.cols(); t++) {
                output(f, t) = std::max(0.0f, std::min(1.0f, output(f, t) + delta));
            }
        }
        
        return output;
    }
    
    // Ses hızını biraz artır/azalt (resample)
    AudioBuffer resample(const AudioBuffer& input) {
        std::uniform_real_distribution<float> dist(0.95f, 1.05f);
        float rate = dist(gen);
        
        AudioBuffer output;
        // Sampling rate değiştirme
        // AudioResampler::resample(input, rate, output);
        return output;
    }
    
    // Telefon ses kalitesi simülasyonu
    AudioBuffer simulatePhoneQuality(const AudioBuffer& input) {
        AudioBuffer output = input;
        
        // Telefon bandı filtresi uygula (300Hz-3400Hz)
        // AudioFilter::bandpass(output, 300.0f, 3400.0f);
        
        // Düşük bit derinliği simülasyonu
        // AudioQuantizer::reduce(output, 8);
        
        return output;
    }
    
    // Konuşmacı simulasyonu - formant kaydırma
    AudioBuffer shiftFormants(const AudioBuffer& input) {
        std::uniform_real_distribution<float> dist(0.9f, 1.1f);
        float factor = dist(gen);
        
        AudioBuffer output;
        // Formant kaydırma PSOLA algoritması ile
        // FormantShifter::shift(input, factor, output);
        return output;
    }
    
    // Rastgele artırma kombinasyonu uygula
    AudioBuffer applyRandomAugmentation(const AudioBuffer& input) {
        AudioBuffer result = input;
        
        // Rastgele artırma teknikleri seçimi
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        
        if (dist(gen) < 0.5f) result = timeStretch(result);
        if (dist(gen) < 0.3f) result = pitchShift(result);
        if (dist(gen) < 0.7f) result = addNoise(result);
        if (dist(gen) < 0.4f) result = addReverb(result);
        if (dist(gen) < 0.3f) result = resample(result);
        if (dist(gen) < 0.2f) result = simulatePhoneQuality(result);
        if (dist(gen) < 0.3f) result = shiftFormants(result);
        
        return result;
    }
    
    // Tüm veri setini artır
    std::vector<std::pair<AudioBuffer, std::string>> augmentDataset(
            const std::vector<std::pair<AudioBuffer, std::string>>& dataset,
            int augmentationFactor) {
        
        std::vector<std::pair<AudioBuffer, std::string>> augmentedDataset;
        
        // Orijinal veri setini koru
        augmentedDataset = dataset;
        
        // Her örnek için augmentationFactor kadar yeni veri üret
        for (const auto& sample : dataset) {
            for (int i = 0; i < augmentationFactor; i++) {
                AudioBuffer augmentedAudio = applyRandomAugmentation(sample.first);
                augmentedDataset.push_back({augmentedAudio, sample.second});
            }
        }
        
        return augmentedDataset;
    }

    // Önerilen ek özellikler
    struct TurkishPhonemeFeatures {
        float vowelHarmonyWeight;    // Ünlü uyumu ağırlığı
        float stressPatterns[4];     // Vurgu kalıpları
        float consonantMutations;    // Ünsüz yumuşaması
    };
    
    // Bölgesel aksan desteği
    enum TurkishAccent {
        ISTANBUL,
        KARADENIZ,
        DOGU,
        IC_ANADOLU,
        EGE
    };
};

/**
 * ===========================================================
 * Proje: Zuzu v1 - Türkçe Metin Veri Artırma
 * Dosya: text_data_augmentation.h
 * Açıklama: Türkçe metin verisi için artırma teknikleri
 * 
 * Versiyon: 1.0.0
 * ===========================================================
 */

#include <string>
#include <vector>
#include <map>
#include <random>

class TextDataAugmentation {
private:
    std::random_device rd;
    std::mt19937 gen{rd()};
    
    // Türkçe yazım hataları ve alternatif yazımlar
    std::map<char, std::vector<char>> charReplacements = {
        {'a', {'e'}},
        {'e', {'a', 'i'}},
        {'i', {'ı', 'e'}},
        {'ı', {'i', 'u'}},
        {'o', {'u', 'ö'}},
        {'ö', {'o', 'ü'}},
        {'u', {'ü', 'o'}},
        {'ü', {'u', 'ö'}},
        {'c', {'ç', 'j'}},
        {'ç', {'c'}},
        {'g', {'ğ', 'k'}},
        {'ğ', {'g'}},
        {'s', {'ş', 'z'}},
        {'ş', {'s'}},
        {'b', {'p'}},
        {'d', {'t'}},
        {'k', {'g', 'q'}},
        {'p', {'b'}}
    };
    
    // Yaygın Türkçe yazım hataları
    std::map<std::string, std::string> commonMisspellings = {
        {"gelicek", "gelecek"},
        {"geliyorum", "geliyorum"},
        {"herşey", "her şey"},
        {"yalnız", "yalnız"},
        {"birşey", "bir şey"},
        {"kucuk", "küçük"},
        {"buyuk", "büyük"},
        {"şöför", "şoför"}
    };
    
    // Diyalekt varyasyonları
    std::map<std::string, std::vector<std::string>> dialectVariations = {
        {"geliyorum", {"geliyem", "gelirem"}},
        {"gideceğim", {"gidecām", "gidecem"}},
        {"yapacağım", {"yapacam", "yapacağam"}},
        {"söylüyorum", {"söylüyem", "söylerem"}}
    };

public:
    TextDataAugmentation() {}
    
    // Kelimede rastgele harf değiştirme
    std::string randomCharacterReplacement(const std::string& text) {
        std::string result = text;
        std::uniform_int_distribution<int> dist(0, text.length() - 1);
        int pos = dist(gen);
        
        if (charReplacements.find(text[pos]) != charReplacements.end()) {
            std::vector<char> options = charReplacements[text[pos]];
            std::uniform_int_distribution<int> optDist(0, options.size() - 1);
            result[pos] = options[optDist(gen)];
        }
        
        return result;
    }
    
    // Rastgele bir yazım hatası ekle
    std::string introduceSpellingMistake(const std::string& text) {
        // Metni kelimelere ayır
        std::vector<std::string> words;
        std::string word;
        
        for (char c : text) {
            if (c == ' ' || c == '.' || c == ',' || c == '!' || c == '?') {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
                words.push_back(std::string(1, c));
            } else {
                word += c;
            }
        }
        
        if (!word.empty()) {
            words.push_back(word);
        }
        
        // Rastgele bir kelimeyi seç ve değiştir
        if (words.size() > 1) {
            std::uniform_int_distribution<int> dist(0, words.size() - 1);
            int pos;
            
            // Boşluk olmayan bir kelime seç
            do {
                pos = dist(gen);
            } while (words[pos] == " " || words[pos] == "." || words[pos] == "," || 
                     words[pos] == "!" || words[pos] == "?");
            
            // Kelimeyi değiştir
            words[pos] = randomCharacterReplacement(words[pos]);
        }
        
        // Metni geri birleştir
        std::string result;
        for (const auto& w : words) {
            result += w;
        }
        
        return result;
    }
    
    // Diyalekt varyasyonu ekle
    std::string addDialectVariation(const std::string& text) {
        // Metni kelimelere ayır
        std::vector<std::string> words;
        std::string word;
        
        for (char c : text) {
            if (c == ' ' || c == '.' || c == ',' || c == '!' || c == '?') {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
                words.push_back(std::string(1, c));
            } else {
                word += c;
            }
        }
        
        if (!word.empty()) {
            words.push_back(word);
        }
        
        // Değiştirilebilecek kelimeleri bul
        std::vector<int> replaceable;
        for (size_t i = 0; i < words.size(); i++) {
            if (dialectVariations.find(words[i]) != dialectVariations.end()) {
                replaceable.push_back(i);
            }
        }
        
        // Değiştirilebilir kelime varsa, bir tanesini rastgele değiştir
        if (!replaceable.empty()) {
            std::uniform_int_distribution<int> dist(0, replaceable.size() - 1);
            int idx = replaceable[dist(gen)];
            
            std::vector<std::string> options = dialectVariations[words[idx]];
            std::uniform_int_distribution<int> optDist(0, options.size() - 1);
            words[idx] = options[optDist(gen)];
        }
        
        // Metni geri birleştir
        std::string result;
        for (const auto& w : words) {
            result += w;
        }
        
        return result;
    }
    
    // Kelime sırasını değiştir (Türkçe'de serbest kelime sırası)
    std::string shuffleWordOrder(const std::string& text) {
        // Metni cümlelere ayır
        std::vector<std::string> sentences;
        std::string sentence;
        
        for (char c : text) {
            sentence += c;
            if (c == '.' || c == '!' || c == '?') {
                sentences.push_back(sentence);
                sentence.clear();
            }
        }
        
        if (!sentence.empty()) {
            sentences.push_back(sentence);
        }
        
        // Her cümle için
        for (auto& s : sentences) {
            // Cümleyi kelimelere ayır
            std::vector<std::string> words;
            std::string word;
            
            for (char c : s) {
                if (c == ' ' || c == '.' || c == ',' || c == '!' || c == '?') {
                    if (!word.empty()) {
                        words.push_back(word);
                        word.clear();
                    }
                    words.push_back(std::string(1, c));
                } else {
                    word += c;
                }
            }
            
            if (!word.empty()) {
                words.push_back(word);
            }
            
            // İçerik kelimelerini belirle (noktalama ve boşluklar hariç)
            std::vector<std::string> contentWords;
            std::vector<int> contentPositions;
            
            for (size_t i = 0; i < words.size(); i++) {
                if (words[i] != " " && words[i] != "." && words[i] != "," && 
                    words[i] != "!" && words[i] != "?") {
                    contentWords.push_back(words[i]);
                    contentPositions.push_back(i);
                }
            }
            
            // Kelimeleri karıştır ama son kelimeyi yerinde bırak (Türkçe yapısına uygun)
            if (contentWords.size() > 2) {
                // Rastgele iki kelimeyi değiştir
                std::uniform_int_distribution<int> dist(0, contentWords.size() - 2);
                int pos1 = dist(gen);
                int pos2;
                do {
                    pos2 = dist(gen);
                } while (pos1 == pos2);
                
                // Kelimeleri değiştir
                std::swap(words[contentPositions[pos1]], words[contentPositions[pos2]]);
            }
            
            // Cümleyi geri birleştir
            s.clear();
            for (const auto& w : words) {
                s += w;
            }
        }
        
        // Metni geri birleştir
        std::string result;
        for (const auto& s : sentences) {
            result += s;
        }
        
        return result;
    }
    
    // Rastgele artırma uygula
    std::string applyRandomAugmentation(const std::string& text) {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        float rand = dist(gen);
        
        if (rand < 0.33f) {
            return introduceSpellingMistake(text);
        } else if (rand < 0.66f) {
            return addDialectVariation(text);
        } else {
            return shuffleWordOrder(text);
        }
    }
    
    // Tüm veri setini artır
    std::vector<std::string> augmentDataset(
            const std::vector<std::string>& dataset,
            int augmentationFactor) {
        
        std::vector<std::string> augmentedDataset;
        
        // Orijinal veri setini koru
        augmentedDataset = dataset;
        
        // Her örnek için augmentationFactor kadar yeni veri üret
        for (const auto& text : dataset) {
            for (int i = 0; i < augmentationFactor; i++) {
                std::string augmentedText = applyRandomAugmentation(text);
                augmentedDataset.push_back(augmentedText);
            }
        }
        
        return augmentedDataset;
    }

    // Yeni özellikler
    // Türkçe dil yapısı kuralları
    struct TurkishGrammarRules {
        bool vowelHarmony;          // Ünlü uyumu
        bool consonantHarmony;      // Ünsüz uyumu
        bool wordOrderCheck;        // Söz dizimi kontrolü
    };
    
    // Ağız özellikleri
    std::map<std::string, std::vector<std::string>> dialectFeatures = {
        {"İstanbul", {"yapacağım", "geliyorum"}},
        {"Karadeniz", {"yapayirum", "geliyirum"}},
        {"Doğu", {"yapacağam", "gelirem"}}
    };
};

/**
 * ===========================================================
 * Proje: Zuzu v1 - Veri Artırma Yöneticisi
 * Dosya: augmentation_manager.h
 * Açıklama: Ses ve metin veri artırma süreçlerini yöneten modül
 * 
 * Versiyon: 1.0.0
 * ===========================================================
 */

#include <vector>
#include <string>
#include <utility>

class AugmentationManager {
private:
    AudioDataAugmentation audioAug;
    TextDataAugmentation textAug;
    
    // Etiketlenmiş veri seti
    std::vector<std::pair<AudioBuffer, std::string>> dataset;
    
    // Artırma konfigürasyonu
    struct AugmentationConfig {
        int audioAugmentationFactor = 5;  // Her ses örneği için kaç artırma
        int textAugmentationFactor = 3;   // Her metin için kaç artırma
        float trainTestSplit = 0.8f;      // Eğitim/test ayırma oranı
        bool balanceClasses = true;       // Sınıfları dengele
    } config;

    // Kalite kontrol metrikleri
    struct QualityMetrics {
        float signalToNoiseRatio;
        float pronunciationClarity;
        float accentConsistency;
    };
    
public:
    AugmentationManager() {}
    
    // Veri setini yükle
    bool loadDataset(const std::string& datasetPath) {
        // Veri setini yükle
        // Gerçek implementasyon veri seti formatına bağlı olacaktır
        return true;
    }
    
    // Veri setini artır
    void augmentDataset() {
        // Ses verilerini artır
        std::vector<std::pair<AudioBuffer, std::string>> augmentedAudioDataset = 
            audioAug.augmentDataset(dataset, config.audioAugmentationFactor);
        
        // Metin transkriptlerini topla
        std::vector<std::string> transcripts;
        for (const auto& sample : dataset) {
            transcripts.push_back(sample.second);
        }
        
        // Metinleri artır
        std::vector<std::string> augmentedTranscripts = 
            textAug.augmentDataset(transcripts, config.textAugmentationFactor);
        
        // Artırılmış veri setini oluştur
        // Bu örnekte sadece ses artırma kullanılıyor
        dataset = augmentedAudioDataset;
    }
    
    // Sınıfları dengele (ender sınıfların örneklerini artırarak)
    void balanceClasses() {
        if (!config.balanceClasses) return;
        
        // Sınıf frekanslarını say
        std::map<std::string, int> classFreq;
        for (const auto& sample : dataset) {
            classFreq[sample.second]++;
        }
        
        // En yüksek frekansı bul
        int maxFreq = 0;
        for (const auto& cf : classFreq) {
            maxFreq = std::max(maxFreq, cf.second);
        }
        
        // Dengelenmiş veri seti
        std::vector<std::pair<AudioBuffer, std::string>> balancedDataset = dataset;
        
        // Her sınıf için, maksimum frekansa ulaşana kadar örnekleri artır
        for (const auto& cf : classFreq) {
            int needed = maxFreq - cf.second;
            
            if (needed > 0) {
                // Bu sınıfa ait tüm örnekleri topla
                std::vector<std::pair<AudioBuffer, std::string>> classExamples;
                for (const auto& sample : dataset) {
                    if (sample.second == cf.first) {
                        classExamples.push_back(sample);
                    }
                }
                
                // Rastgele seç ve artır
                std::uniform_int_distribution<int> dist(0, classExamples.size() - 1);
                for (int i = 0; i < needed; i++) {
                    int idx = dist(gen);
                    AudioBuffer augmented = audioAug.applyRandomAugmentation(classExamples[idx].first);
                    balancedDataset.push_back({augmented, cf.first});
                }
            }
        }
        
        // Dengelenmiş veri setini güncelle
        dataset = balancedDataset;
    }
    
    // Eğitim ve test setlerini ayır
    std::pair<std::vector<std::pair<AudioBuffer, std::string>>, 
              std::vector<std::pair<AudioBuffer, std::string>>> 
    splitTrainTest() {
        // Veri setini karıştır
        std::shuffle(dataset.begin(), dataset.end(), gen);
        
        // Bölme noktasını hesapla
        size_t splitPoint = static_cast<size_t>(dataset.size() * config.trainTestSplit);
        
        // Eğitim ve test setlerini ayır
        std::vector<std::pair<AudioBuffer, std::string>> trainSet(
            dataset.begin(), dataset.begin() + splitPoint);
        std::vector<std::pair<AudioBuffer, std::string>> testSet(
            dataset.begin() + splitPoint, dataset.end());
            
        return {trainSet, testSet};
    }
    
    // Tam artırma akışını çalıştır
    std::pair<std::vector<std::pair<AudioBuffer, std::string>>, 
              std::vector<std::pair<AudioBuffer, std::string>>> 
    runFullAugmentationPipeline(const std::string& datasetPath) {
        // Veri setini yükle
        if (!loadDataset(datasetPath)) {
            throw std::runtime_error("Veri seti yüklenemedi: " + datasetPath);
        }
        
        // Veriyi artır
        augmentDataset();
        
        // Sınıfları dengele
        balanceClasses();
        
        // Eğitim/test ayır ve döndür
        return splitTrainTest();
    }

    // Veri doğrulama
    bool validateAugmentedData(const AudioBuffer& audio, 
                             const string& transcript);
};

// Önerilen yeni sınıf
class ASRPROIntegration {
public:
    bool init() {
        // ASR-PRO başlatma
        return true;
    }
    
    bool loadModel(const std::string& modelPath) {
        // Model yükleme
        return true;
    }
    
    std::string recognize(const AudioBuffer& audio) {
        // Ses tanıma
        return "";
    }
};

// Önerilen yeni sınıf
class BNPUOptimizer {
    void quantizeWeights();
    void pruneNetwork();
    void optimizeMemory();
};

// Önerilen yeni sınıf
class RealTimePreview {
public:
    void startPreview(const AudioBuffer& buffer);
    void updatePreview(const AudioBuffer& buffer);
    void stopPreview();
private:
    AudioPlayer player;
    DisplayManager display;
};

// Önerilen yeni sınıf
class DistributedProcessor {
public:
    void distributeWorkload();
    void collectResults();
    void synchronizeNodes();
private:
    std::vector<WorkerNode> nodes;
    TaskManager taskManager;
};

// ASR-PRO için gerekli olan özelliklerin eklenmesi gerekiyor:
class ASRPROTurkishSupport {
public:
    // BNPU yapılandırması
    struct BNPUConfig {
        uint32_t inputSize;
        uint32_t hiddenSize;
        uint32_t outputSize;
        uint8_t rnnLayers;
    };
    
    // Türkçe fonetik model
    struct TurkishPhoneticModel {
        std::vector<std::string> phonemes;
        std::vector<float> phonemeWeights;
        std::map<std::string, float> transitionProbs;
    };
    
    // ASR-PRO ses işleme
    struct AudioProcessing {
        float sampleRate;
        uint16_t frameSize;
        uint16_t hopSize;
        uint8_t melBands;
    };
};

/**
 * ===========================================================
 * Proje: Zuzu v1 - ASR-PRO Türkçe Entegrasyonu
 * Dosya: asrpro_integration.h
 * Açıklama: ASR-PRO donanım entegrasyonu ve Türkçe dil desteği
 * 
 * Versiyon: 1.0.0
 * ===========================================================
 */

#include <cstdint>
#include "bnpu_core.h"
#include "turkish_model.h"

class ASRPROIntegration {
private:
    // BNPU yapılandırması
    struct BNPUConfig {
        uint32_t inputLayerSize = 13;     // MFCC öznitelikleri
        uint32_t hiddenLayerSize = 256;   // Gizli katman
        uint32_t outputLayerSize = 29;    // Türkçe fonem sayısı
        uint8_t rnnLayers = 2;            // RNN katman sayısı
        float dropoutRate = 0.2f;         // Dropout oranı
    } bnpuConfig;

    // DMA konfigürasyonu
    struct DMAConfig {
        uint32_t bufferSize = 1024;       // DMA buffer boyutu
        uint8_t channelCount = 2;         // DMA kanal sayısı
        bool circularMode = true;         // Dairesel DMA modu
    } dmaConfig;

    // Bellek eşleme
    struct MemoryMap {
        uint32_t modelBaseAddr = 0x20000000;  // Model başlangıç adresi
        uint32_t audioBufferAddr = 0x20100000; // Ses buffer adresi
        uint32_t featureBufferAddr = 0x20200000; // Öznitelik buffer adresi
    } memoryMap;

public:
    bool initHardware() {
        // BNPU donanım başlatma
        if (!initBNPU()) return false;
        
        // DMA yapılandırması
        if (!setupDMA()) return false;
        
        // Bellek eşleme
        if (!configureMemoryMap()) return false;
        
        return true;
    }

    bool loadTurkishModel(const TurkishModel& model) {
        // Model parametrelerini BNPU'ya yükle
        if (!loadModelToBNPU(model)) return false;
        
        // Türkçe fonem setini yapılandır
        if (!configureTurkishPhonemes()) return false;
        
        return true;
    }

    std::string recognizeTurkish(const AudioBuffer& audio) {
        // Gerçek zamanlı ses işleme
        AudioFeatures features = extractFeatures(audio);
        
        // BNPU ile tanıma
        std::vector<float> probabilities = processBNPU(features);
        
        // Dil modeli ile son işlem
        return decodeTurkish(probabilities);
    }

private:
    bool initBNPU() {
        // BNPU çekirdek başlatma
        if (!BNPU_Init(&bnpuConfig)) {
            return false;
        }
        
        // Hızlandırıcı optimizasyonları
        BNPU_EnableAcceleration();
        BNPU_ConfigureCache();
        
        return true;
    }

    bool setupDMA() {
        // DMA kontrolcü yapılandırması
        DMA_Init(&dmaConfig);
        DMA_ConfigureChannels();
        return true;
    }

    bool configureMemoryMap() {
        // Bellek bölgelerini ayır ve eşle
        if (!MMU_MapRegion(memoryMap.modelBaseAddr, MODEL_SIZE)) {
            return false;
        }
        return true;
    }
};

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

/**
 * ===========================================================
 * Proje: Zuzu v1 - ASR-PRO Register Tanımlamaları
 * Dosya: asr_pro_defines.h
 * Açıklama: ASR-PRO çipi register ve değişken tanımlamaları
 * 
 * Versiyon: 1.0.0
 * Değişiklikler:
 * - [1.0.0] İlk sürüm
 * ===========================================================
 */

#ifndef ASR_PRO_DEFINES_H
#define ASR_PRO_DEFINES_H

// Temel Özellikler
#define ASR_PRO_CPU_FREQ      240000000   // 240MHz
#define ASR_PRO_SRAM_SIZE     640000      // 640KB
#define ASR_PRO_FLASH_SIZE    4194304     // 4MB

// Bellek Haritası
#define SRAM_BASE           0x1FF00000
#define SRAM_SIZE          (640 * 1024)
#define FLASH_BASE         0x00000000
#define FLASH_SIZE         (4 * 1024 * 1024)

// Periferik Base Adresleri
#define BNPU_BASE          0x40000000
#define DMA_BASE           0x40001000
#define ADC_BASE           0x40002000
#define DTR_FLASH_BASE     0x40004000
#define GPIO0_BASE         0x40020000
#define GPIO1_BASE         0x40021000
#define UART0_BASE         0x40022000
#define UART1_BASE         0x40023000
#define UART2_BASE         0x40024000
#define IIS0_BASE          0x40025000

// BNPU Registers
#define BNPU_CTRL         (BNPU_BASE + 0x00)
#define BNPU_STATUS       (BNPU_BASE + 0x04)
#define BNPU_CONFIG       (BNPU_BASE + 0x08)
#define BNPU_WEIGHT_ADDR  (BNPU_BASE + 0x0C)
#define BNPU_INPUT_ADDR   (BNPU_BASE + 0x10)
#define BNPU_OUTPUT_ADDR  (BNPU_BASE + 0x14)

// BNPU Status Bits
#define BNPU_STATUS_READY 0x01
#define BNPU_STATUS_BUSY  0x02
#define BNPU_STATUS_ERROR 0x04
#define BNPU_STATUS_DONE  0x08

// UART Registers
#define UART_DR(base)     ((base) + 0x000)
#define UART_RSR(base)    ((base) + 0x004)
#define UART_FR(base)     ((base) + 0x018)
#define UART_IBRD(base)   ((base) + 0x024)
#define UART_FBRD(base)   ((base) + 0x028)
#define UART_LCR_H(base)  ((base) + 0x02C)
#define UART_CR(base)     ((base) + 0x030)
#define UART_IFLS(base)   ((base) + 0x034)
#define UART_IMSC(base)   ((base) + 0x038)
#define UART_RIS(base)    ((base) + 0x03C)
#define UART_MIS(base)    ((base) + 0x040)
#define UART_ICR(base)    ((base) + 0x044)

// DMA Registers
#define DMA_STATUS        (DMA_BASE + 0x000)
#define DMA_CFG           (DMA_BASE + 0x004)
#define DMA_CTRL          (DMA_BASE + 0x008)
#define DMA_INT_STAT      (DMA_BASE + 0x00C)
#define DMA_INT_TC_STAT   (DMA_BASE + 0x010)
#define DMA_INT_TC_CLR    (DMA_BASE + 0x014)
#define DMA_INT_ERR_STAT  (DMA_BASE + 0x018)
#define DMA_INT_ERR_CLR   (DMA_BASE + 0x01C)

// ADC Registers
#define ADC_CTRL          (ADC_BASE + 0x000)
#define ADC_STAT          (ADC_BASE + 0x004)
#define ADC_DATA          (ADC_BASE + 0x008)
#define ADC_INT_EN        (ADC_BASE + 0x00C)
#define ADC_INT_STAT      (ADC_BASE + 0x010)
#define ADC_INT_CLR       (ADC_BASE + 0x014)

// I2S Registers 
#define IIS_CTRL          (IIS0_BASE + 0x000)
#define IIS_STAT          (IIS0_BASE + 0x004)
#define IIS_CLKDIV        (IIS0_BASE + 0x008)
#define IIS_TXDATA        (IIS0_BASE + 0x00C)
#define IIS_RXDATA        (IIS0_BASE + 0x010)

// Interrupt Numbers
typedef enum {
    INT_WWDG        = 0,
    INT_SCU         = 1,
    INT_ADC         = 3,
    INT_TIMER0      = 5,
    INT_TIMER1      = 6,
    INT_TIMER2      = 7,
    INT_TIMER3      = 8,
    INT_IIC         = 9,
    INT_GPIO0       = 10,
    INT_GPIO1       = 11,
    INT_UART0       = 12,
    INT_UART1       = 13,
    INT_UART2       = 14,
    INT_IIS0        = 15,
    INT_PDM         = 20,
    INT_DTR         = 21,
    INT_VDT         = 23,
    INT_EXT0        = 24,
    INT_EXT1        = 25,
    INT_IWDG        = 26,
    INT_EFUSE       = 29,
    INT_GPIO2       = 30
} IRQn_Type;

// System Control Bits
#define SCU_CTRL_ENABLE   (1 << 0)
#define SCU_CTRL_SLEEP    (1 << 1)
#define SCU_CTRL_DEEPSLEEP (1 << 2)

// GPIO Pin Functions
typedef enum {
    GPIO_FUNC_INPUT = 0,
    GPIO_FUNC_OUTPUT = 1,
    GPIO_FUNC_ALT1 = 2,
    GPIO_FUNC_ALT2 = 3,
    GPIO_FUNC_ALT3 = 4,
    GPIO_FUNC_ALT4 = 5
} GPIO_Function;

// DMA Channel Priority
typedef enum {
    DMA_PRIORITY_LOW = 0,
    DMA_PRIORITY_MEDIUM = 1,
    DMA_PRIORITY_HIGH = 2,
    DMA_PRIORITY_VERY_HIGH = 3
} DMA_Priority;

#endif // ASR_PRO_DEFINES_H

/**
 * ===========================================================
 * Proje: Zuzu v1 - ASR-PRO Hata Ayıklama Modülü
 * Dosya: asr_pro_debug.h
 * Açıklama: ASR-PRO için hata ayıklama ve kontrol
 * 
 * Versiyon: 1.0.0
 * ===========================================================
 */

#ifndef ASR_PRO_DEBUG_H
#define ASR_PRO_DEBUG_H

#include <cstdint>
#include "asr_pro_defines.h"

class ASRPRODebug {
public:
    // Hata kodları
    enum ErrorCode {
        ERR_NONE = 0,
        ERR_INIT_FAILED = -1,
        ERR_INVALID_STATE = -2, 
        ERR_TIMEOUT = -3,
        ERR_BUFFER_OVERFLOW = -4,
        ERR_BUFFER_UNDERFLOW = -5,
        ERR_INVALID_PARAM = -6,
        ERR_HARDWARE = -7
    };

    // BNPU durumu kontrolü
    struct BNPUStatus {
        bool isReady;
        bool isBusy;
        bool hasError;
        uint32_t errorCode;
        uint32_t registers[8];
    };

    // DMA durumu kontrolü 
    struct DMAStatus {
        bool isActive;
        bool hasError;
        uint32_t transferred;
        uint32_t remaining;
    };

    // Bellek durumu
    struct MemoryStatus {
        uint32_t freeRAM;
        uint32_t usedRAM;
        uint32_t freeFlash;
        uint32_t usedFlash;
    };

    // Donanım kontrolü
    bool checkHardware() {
        // Temel donanım kontrolü
        if (!checkBNPU()) return false;
        if (!checkDMA()) return false;
        if (!checkMemory()) return false;
        return true;
    }

    // BNPU kontrolü
    BNPUStatus checkBNPU() {
        BNPUStatus status;
        volatile uint32_t* bnpuStatus = (volatile uint32_t*)BNPU_STATUS;
        
        status.isReady = (*bnpuStatus & BNPU_STATUS_READY);
        status.isBusy = (*bnpuStatus & BNPU_STATUS_BUSY);
        status.hasError = (*bnpuStatus & BNPU_STATUS_ERROR);
        
        return status;
    }

    // DMA kontrolü 
    DMAStatus checkDMA() {
        DMAStatus status;
        volatile uint32_t* dmaStatus = (volatile uint32_t*)DMA_STATUS;
        
        status.isActive = (*dmaStatus & 0x1);
        status.hasError = (*dmaStatus & 0x2);
        status.transferred = *(volatile uint32_t*)(DMA_BASE + 0x20);
        status.remaining = *(volatile uint32_t*)(DMA_BASE + 0x24);
        
        return status;
    }

    // Bellek kontrolü
    MemoryStatus checkMemory() {
        MemoryStatus status;
        
        // SRAM kullanımı
        status.freeRAM = SRAM_SIZE - getUsedRAM();
        status.usedRAM = getUsedRAM();
        
        // Flash kullanımı
        status.freeFlash = FLASH_SIZE - getUsedFlash();
        status.usedFlash = getUsedFlash();
        
        return status;
    }

    // Hata durumlarını logla
    void logError(ErrorCode error, const char* message) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), 
                "ASR-PRO Error [%d]: %s", error, message);
        
        // UART üzerinden gönder
        sendDebugMessage(buffer);
    }

    // Watchdog Timer kontrolü
    bool checkWatchdog() {
        volatile uint32_t* wwdgStatus = (volatile uint32_t*)(0x40010000);
        return (*wwdgStatus & 0x1) == 0;
    }

private:
    uint32_t getUsedRAM() {
        // SRAM kullanımı hesaplama
        return (*(volatile uint32_t*)(SRAM_BASE + 0x4));
    }
    
    uint32_t getUsedFlash() {
        // Flash kullanımı hesaplama
        return (*(volatile uint32_t*)(FLASH_BASE + 0x8));
    }
    
    void sendDebugMessage(const char* msg) {
        // UART üzerinden debug mesajı gönder
        volatile uint32_t* uartData = (volatile uint32_t*)UART_DR(UART0_BASE);
        while (*msg) {
            *uartData = *msg++;
            while (*(volatile uint32_t*)UART_FR(UART0_BASE) & (1 << 5));
        }
    }
};

#endif // ASR_PRO_DEBUG_H
