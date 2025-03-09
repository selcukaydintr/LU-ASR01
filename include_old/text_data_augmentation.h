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