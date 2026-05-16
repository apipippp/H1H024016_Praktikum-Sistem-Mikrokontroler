# Jawaban Pertanyaan Praktikum Modul 6: Percobaan 6A (External Interrupt)

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan interrupt!

Prosesnya dimulai ketika interrupt memberikan mekanisme yang memungkinkan mikrokontroler menghentikan sementara program utama untuk menangani suatu kejadian tertentu. Ketika tombol ditekan dan memicu interrupt, program utama dihentikan sementara. Mikrokontroler kemudian akan menjalankan fungsi khusus yang bernama ISR (Interrupt Service Routine). Pada percobaan ini, fungsi ISR tersebut adalah `tombolInterrupt()` yang berisi instruksi untuk mengubah status variabel `ledState` menjadi kebalikannya (`!ledState`). Setelah instruksi di dalam ISR selesai dieksekusi, program utama pada `loop()` dilanjutkan kembali. Di dalam `loop()` tersebut, mikrokontroler mengeksekusi `digitalWrite(13, ledState)` yang berfungsi memperbarui kondisi aktual LED sesuai dengan nilai terbaru dari variabel `ledState`.

---

## 2. Apa fungsi attachInterrupt() pada program tersebut?

Fungsi `attachInterrupt()` pada mikrokontroler Arduino disediakan untuk menghubungkan interrupt dengan fungsi ISR. Pada program yang dibuat, fungsi ini digunakan untuk mendaftarkan fungsi `tombolInterrupt` (sebagai ISR) pada pin 2 Arduino, sehingga fungsi tersebut akan tereksekusi secara otomatis ketika terjadi kondisi pemicu berupa `FALLING` (tepi turun) pada pin tersebut.

---

## 3. Mengapa pada ISR tidak disarankan menggunakan delay() dan Serial.print()?

Penggunaan `delay()` dan `Serial.print()` tidak disarankan karena sebuah ISR harus dibuat dan dieksekusi sesingkat mungkin. Selama ISR sedang berjalan, proses pada program utama akan berhenti sementara. Fungsi `delay()` dan `Serial.print()` membutuhkan waktu pemrosesan yang relatif lama. Hal ini dapat menghambat alur kerja mikrokontroler dan menyebabkan program utama terbengkalai, sehingga sistem kehilangan efisiensinya dalam menangani peristiwa *real-time*.

---

## 4. Apa fungsi keyword volatile pada variabel ledState?

Keyword `volatile` digunakan pada variabel `ledState` karena variabel tersebut diakses dan diubah di dalam fungsi ISR dan program utama. Fungsi utama keyword ini adalah untuk memberitahu compiler mikrokontroler bahwa nilai dari variabel tersebut dapat berubah sewaktu-waktu di luar alur normal program yang sedang berjalan. Hal ini mencegah *compiler* melakukan optimasi yang salah terhadap variabel tersebut di memori utama.

---

## 5. Modifikasi Program Menggunakan Mode Interrupt Lain

Terdapat beberapa mode pemicu interrupt yang tersedia, yaitu `RISING`, `FALLING`, `CHANGE`, dan `LOW`. Berikut adalah penjelasan perbedaan cara kerja masing-masing mode:

* **FALLING:** ISR dipicu saat transisi sinyal digital turun dari `HIGH` menjadi `LOW`. (Contoh: Saat tombol ditekan pada rangkaian *pull-up*).
* **RISING:** ISR dipicu saat transisi sinyal digital naik dari `LOW` menjadi `HIGH`. (Contoh: Saat tombol dilepas pada rangkaian *pull-up*).
* **CHANGE:** ISR dipicu setiap kali terjadi perubahan status logika sinyal, baik dari `HIGH` ke `LOW` maupun dari `LOW` ke `HIGH`. 
* **LOW:** ISR dipicu secara terus-menerus selama sinyal berada dalam keadaan logika `LOW`.

### Analisis Perilaku LED pada Mode CHANGE

Jika program dimodifikasi menggunakan mode **CHANGE**, perilaku LED akan menjadi jauh lebih responsif terhadap setiap fase penekanan tombol. Karena pin 2 menggunakan mode `INPUT_PULLUP` (awalnya `HIGH`), menekan tombol akan mengubah sinyal menjadi `LOW`, yang mana dihitung sebagai satu perubahan. Hal ini memicu interrupt dan mengubah status LED. Ketika jari melepaskan tombol, sinyal kembali naik menjadi `HIGH`, yang mana dihitung sebagai perubahan kedua. Hal ini memicu interrupt lagi dan langsung mengembalikan LED ke status semula. Akibatnya, LED mungkin akan menyala hanya selama tombol ditahan dan langsung mati saat dilepas (ataupun sebaliknya), namun juga sangat rentan terhadap *bouncing* mekanis tombol yang membaca multi-transisi secara instan.

### Source Code Modifikasi (Mode CHANGE)

```cpp
#include <Arduino.h>

// Variabel volatile agar dapat diubah dalam ISR
volatile bool ledState = false;

// ISR: dijalankan saat terjadi perubahan status (CHANGE) pada pin
void tombolInterrupt() {
  ledState = !ledState; // Toggle status LED
}

void setup() {
  // Konfigurasi pin 13 sebagai output (LED)
  pinMode(13, OUTPUT);
  
  // Konfigurasi pin 2 sebagai input dengan pull-up internal
  pinMode(2, INPUT_PULLUP);
  
  // Daftarkan ISR pada pin 2, dipicu saat CHANGE (tombol ditekan/dilepas)
  attachInterrupt(digitalPinToInterrupt(2), tombolInterrupt, CHANGE);
}

void loop() {
  // Tulis status LED sesuai variabel ledState
  digitalWrite(13, ledState);
}
```

### Source Code Modifikasi (Mode RISING)


```cpp
#include <Arduino.h>

// Variabel volatile agar dapat diubah dalam ISR
volatile bool ledState = false;

// ISR: dijalankan saat tombol dilepas (RISING edge)
void tombolInterrupt() {
  ledState = !ledState; // Toggle status LED
}

void setup() {
  // Konfigurasi pin 13 sebagai output (LED)
  pinMode(13, OUTPUT);
  
  // Konfigurasi pin 2 sebagai input dengan pull-up internal
  pinMode(2, INPUT_PULLUP);
  
  // Daftarkan ISR pada pin 2, dipicu RISING (transisi LOW ke HIGH)
  attachInterrupt(digitalPinToInterrupt(2), tombolInterrupt, RISING);
}

void loop() {
  // Tulis status LED sesuai variabel ledState
  digitalWrite(13, ledState);
}
```

### Source Code Modifikasi (Mode LOW)

```cpp
#include <Arduino.h>

// Variabel volatile agar dapat diubah dalam ISR
volatile bool ledState = false;

// ISR: dijalankan saat terjadi perubahan status (CHANGE) pada pin
void tombolInterrupt() {
  ledState = !ledState; // Toggle status LED
}

void setup() {
  // Konfigurasi pin 13 sebagai output (LED)
  pinMode(13, OUTPUT);
  
  // Konfigurasi pin 2 sebagai input dengan pull-up internal
  pinMode(2, INPUT_PULLUP);
  
  // Daftarkan ISR pada pin 2, dipicu saat CHANGE (tombol ditekan atau dilepas)
  attachInterrupt(digitalPinToInterrupt(2), tombolInterrupt, CHANGE);
}

void loop() {
  // Tulis status LED sesuai variabel ledState
  digitalWrite(13, ledState);
}
```
