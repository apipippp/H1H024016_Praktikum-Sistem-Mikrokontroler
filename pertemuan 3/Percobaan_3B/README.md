# Jawaban Pertanyaan Praktikum Modul 2: Pemrograman GPIO

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## Bagian 3.5.4: Percobaan 3B (I2C)

## 1. Cara Kerja I2C antara Arduino dan LCD

- Arduino sebagai Master
- LCD sebagai Slave
- Menggunakan 2 jalur komunikasi:
  - SDA (data)
  - SCL (clock)

### Alur kerja:

1. Arduino membaca nilai analog dari potensiometer (`analogRead`).
2. Arduino mengirim data ke LCD menggunakan alamat I2C (misalnya 0x27).
3. LCD menampilkan data tersebut.

---

## 2. Konfigurasi Potensiometer

- Kaki kiri → GND
- Kaki tengah → A0
- Kaki kanan → 5V

### Jika kiri dan kanan tertukar:

- Sistem tetap berjalan
- Nilai menjadi terbalik:

  - Putar kanan → nilai kecil
  - Putar kiri → nilai besar

---

## 3. Program (Gabungan UART + I2C)

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int potPin = A0;

void setup() {
  lcd.init();              // Inisialisasi LCD
  lcd.backlight();         // Menyalakan lampu LCD
  Serial.begin(9600);      // Memulai komunikasi serial
}

void loop() {
  int adc = analogRead(potPin);          // Membaca nilai ADC
  float volt = adc * (5.0 / 1023.0);     // Konversi ke volt
  int persen = map(adc, 0, 1023, 0, 100);// Konversi ke persen

  // Tampilkan ke LCD
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(adc);

  lcd.setCursor(0, 1);
  int bar = map(adc, 0, 1023, 0, 16);
  for (int i = 0; i < bar; i++) {
    lcd.print("#");        // Menampilkan bar level
  }

  // Tampilkan ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" Volt: ");
  Serial.print(volt);
  Serial.print(" V Persen: ");
  Serial.print(persen);
  Serial.println("%");

  delay(500);              // Delay pembacaan
}
```

---

## 4. Tabel Pengamatan

| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 4%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

---

## Kesimpulan

- I2C memungkinkan komunikasi dengan LCD hanya menggunakan 2 kabel
- Nilai potensiometer dapat ditampilkan dalam bentuk angka dan bar
- Kombinasi UART dan I2C memungkinkan data ditampilkan di LCD dan Serial Monitor secara bersamaan
