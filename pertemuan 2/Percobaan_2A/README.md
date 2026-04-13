# Jawaban Pertanyaan Praktikum Modul 2: Pemrograman GPIO

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## Bagian 2.5.4: Percobaan 2A (Seven Segment)

### 1. Rangkaian Schematic yang Digunakan

![Skema Rangkaian](dokumentasi/skema2A.png)

![Skemaa Rangkaian](dokumentasi/skemaa2A.png)


### 2. Apa yang terjadi jika nilai `num` lebih dari 15?
Jika nilai `num` lebih dari 15, program akan mengalami *Array Out of Bounds*. Hal ini dikarenakan array `digitPattern` hanya dideklarasikan dengan 16 baris elemen (indeks 0 - 15). Arduino akan membaca alamat memori acak di luar batas array, yang dapat menyebabkan *seven segment* menampilkan pola cahaya yang tidak menentu (nyala acak) atau mikrokontroler menjadi *freeze/crash*.

### 3. Apakah program ini menggunakan common cathode atau common anode?
Program ini menggunakan **Common Anode**.
* **Alasan:** Pada fungsi `displayDigit(int num)`, terdapat baris kode `digitalWrite(segmentPins[i], !digitPattern[num][i]);`. Tanda seru (`!`) membalik logika array (negasi). Nilai `1` pada array diubah menjadi `0` (LOW) untuk menyalakan LED segment. Karena LED menyala saat diberi sinyal LOW (GND) dari pin mikrokontroler, ini berarti semua kutub positif (anoda) pada *seven segment* telah disatukan dan dihubungkan secara konstan ke sumber tegangan VCC (5V).

### 4. Modifikasi Program (Hitung Mundur F ke 0)

```cpp
#include <Arduino.h>

// 7-Segment Common Anode
// Pin mapping segment: a b c d e f g dp
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};

byte digitPattern[16][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3 
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {1,1,1,0,1,1,1,0}, // A
  {0,0,1,1,1,1,1,0}, // b
  {1,0,0,1,1,1,0,0}, // C
  {0,1,1,1,1,0,1,0}, // d
  {1,0,0,1,1,1,1,0}, // E
  {1,0,0,0,1,1,1,0}  // F
};

// Fungsi tampil digit (dibalik untuk Common Anode)
void displayDigit(int num) {
  for(int i = 0; i < 8; i++) {
    // Menuliskan negasi dari array (!1 jadi LOW/Nyala, !0 jadi HIGH/Mati)
    digitalWrite(segmentPins[i], !digitPattern[num][i]); 
  }
}

void setup() {
  for(int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // MODIFIKASI: Mengubah arah perulangan (dari 15 turun ke 0)
  for(int i = 15; i >= 0; i--) { 
    displayDigit(i);
    delay(1000); // Jeda 1 detik
  }
}
```