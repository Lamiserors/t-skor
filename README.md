
# Otomatik Sınav Değerlendirme Sistemi

Bu proje, çoktan seçmeli sınavlarda öğrenci cevaplarını otomatik olarak değerlendiren ve istatistiksel analizler sunan bir C programıdır.

## 🧩 Proje Özeti

Bu uygulama, belirli sayıda öğrencinin belirli sayıda çoktan seçmeli soruya verdiği cevapları değerlendirerek:

- Her öğrenci için **Ham Başarı Notu (HBN)** ve **T-skoru** hesaplar.
- Her öğrencinin **harf notunu (AA, BB, CC, vs.)** belirler.
- Sınıfın **ortalamasını** ve **standart sapmasını** hesaplar.
- Sınıfın genel başarı seviyesini (İyi, Orta, Kötü, vb.) verir.

## ⚙️ Özellikler

- Rastgele cevap anahtarı üretimi.
- Öğrencilerin cevaplarının:
  - Doğru olma,
  - Yanlış olma veya
  - Boş bırakılma ihtimallerine göre simülasyonu.
- 4 yanlış 1 doğruyu götürme sistemi.
- T-skoru ile değerlendirme.
- Sınıf ortalamasına göre dinamik harf notu aralığı.
- Gelişmiş çıktı gösterimi.

## 📊 Örnek Ekran Çıktısı

Program çalıştırıldığında kullanıcıdan aşağıdaki veriler istenir:

- Öğrenci sayısı
- Soru sayısı
- Boş bırakılma ihtimali
- Doğru cevaplanma ihtimali

Örnek çıktı:

```
Sinif ortalamasi: 59.34, standart sapma: 18.29
Sinif duzeyi: İyi

Ogrenci notlari:
001. ogrencinin HBN: 69.50 T-skoru: 65.55, harf notu: BB
...
```

## 📌 Kullanım

### Derleme

Bu proje bir C derleyicisi ile çalışır. Örnek:

```bash
gcc -o sinav main.c -lm
```

### Çalıştırma

```bash
./sinav
```

Ardından komut satırında kullanıcıdan girişler alınır.

## 📁 Dosya Yapısı

| Dosya Adı     | Açıklama                                 |
|---------------|------------------------------------------|
| `main.c`      | Programın tüm kaynak kodlarını içerir    |
| `README.md`   | Bu dokümantasyon dosyası                 |

## 📚 Teknik Bilgiler

### Hesaplamalar

- **Ham Başarı Notu (HBN)**: Her soru 100 / soru sayısı puan değerindedir. Yanlışlar ve boş bırakmalar değerlendirilir.
- **T-skoru**: `T = 60 + 10 * (HBN - Ortalama) / StdSapma`
- **Harf Notu**: T-skoru aralıklarına göre verilir ve sınıf ortalamasına göre dinamikleşir.

### Sınıf Başarı Seviyesi

| Ortalama Aralığı | Düzey         |
|------------------|---------------|
| 0 - 42.5         | Kötü          |
| 42.6 - 47.5      | Zayıf         |
| 47.6 - 52.5      | Orta          |
| 52.6 - 57.5      | Ortanın Üstü  |
| 57.6 - 62.5      | İyi           |
| 62.6 - 70        | Çok İyi       |
| 70.1 - 80        | Mükemmel      |
| 80.1 - 100       | Üstün Başarı  |

## ✨ Geliştirme Önerileri

- Sonuçları bir dosyaya yazma özelliği eklenebilir.
- GUI (Grafiksel Arayüz) entegrasyonu yapılabilir.
- Gerçek sınav verileriyle entegrasyon.
- Öğrenci isimleri dosyadan okunabilir hale getirilebilir.

## 🧑‍💻 Geliştirici

Bu proje bir eğitim projesi kapsamında hazırlanmıştır. Kodlar açık kaynak olup eğitim amaçlı kullanılabilir.
