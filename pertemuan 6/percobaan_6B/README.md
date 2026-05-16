# Jawaban Pertanyaan Praktikum Modul 6: Percobaan 6B (Timer Menggunakan millis())

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Jelaskan bagaimana fungsi millis() bekerja pada program tersebut!

Fungsi `millis()` bekerja dengan cara mengembalikan nilai waktu yang telah berlalu sejak Arduino pertama kali menyala, dalam satuan milidetik. Pada program percobaan, fungsi ini digunakan untuk mengambil waktu saat ini yang kemudian disimpan dalam variabel `currentMillis`. Program kemudian melakukan pengecekan logika menggunakan pernyataan `if` untuk menghitung selisih antara `currentMillis` dengan `previousMillis` (waktu terakhir kondisi LED diubah). Jika selisih waktu tersebut sudah lebih besar atau sama dengan `interval` (dalam hal ini 1000 ms), maka program akan menyimpan waktu `currentMillis` saat ini ke `previousMillis`. Setelah itu, program membalikkan status LED (`!ledState`) dan menulis status baru tersebut ke pin LED menggunakan `digitalWrite()`. Mekanisme ini diulang terus menerus di dalam fungsi `loop()`.

---

## 2. Apa perbedaan utama antara delay() dan millis()?

Perbedaan utamanya terletak pada bagaimana keduanya menangani alur eksekusi program. Fungsi `delay()` akan menyebabkan program berhenti secara total (jeda waktu) selama durasi yang ditentukan. Selama masa jeda ini, mikrokontroler tidak dapat menjalankan instruksi atau tugas lain. Sebaliknya, metode `millis()` digunakan untuk mengecek apakah rentang waktu tertentu sudah terlewati tanpa menghentikan eksekusi kode utama. Dengan `millis()`, program tetap dapat terus berjalan, membaca input lain, dan menjalankan beberapa proses (task) sekaligus secara responsif.

---

## 3. Mengapa metode millis() disebut non-blocking?

Metode `millis()` disebut *non-blocking* karena cara kerjanya tidak memblokir (menghentikan sementara) jalannya program utama mikrokontroler. Alih-alih membuat CPU "tidur" saat menunggu, `millis()` membiarkan CPU terus melakukan siklus *looping* untuk mengeksekusi instruksi-instruksi lain yang ada di dalam `loop()`. Pengecekan interval waktu hanya dilakukan dengan mengevaluasi kondisi `if`, sehingga metode ini sangat cocok diterapkan pada sistem multitasking sederhana karena dapat menjalankan beberapa *task* sekaligus.

---

## 4. Modifikasi Program: 2 LED dengan Interval Berbeda Tanpa delay()

### Source Code Modifikasi

```cpp
#include <Arduino.h>

// --- Konfigurasi LED 1 ---
unsigned long previousMillis1 = 0;   // Waktu terakhir LED 1 berubah
const long interval1 = 1000;         // Interval kedip LED 1: 1000 ms (1 detik)
bool ledState1 = false;              // Status awal LED 1
const int ledPin1 = 13;              // Pin output untuk LED 1

// --- Konfigurasi LED 2 ---
unsigned long previousMillis2 = 0;   // Waktu terakhir LED 2 berubah
const long interval2 = 500;          // Interval kedip LED 2: 500 ms
bool ledState2 = false;              // Status awal LED 2
const int ledPin2 = 12;              // Pin output untuk LED 2

void setup() {
  pinMode(ledPin1, OUTPUT); // Menetapkan pin 13 sebagai OUTPUT
  pinMode(ledPin2, OUTPUT); // Menetapkan pin 12 sebagai OUTPUT
}

void loop() {
  // Mengambil waktu saat ini sejak Arduino menyala
  unsigned long currentMillis = millis();

  // --- Task LED 1 (1 Detik) ---
  // Mengevaluasi apakah selisih waktu sudah mencapai interval1 (1000ms)
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;     // Memperbarui waktu acuan LED 1
    ledState1 = !ledState1;              // Membalik status logika LED 1
    digitalWrite(ledPin1, ledState1);    // Menyalakan atau mematikan LED 1
  }

  // --- Task LED 2 (500 ms) ---
  // Mengevaluasi apakah selisih waktu sudah mencapai interval2 (500ms)
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;     // Memperbarui waktu acuan LED 2
    ledState2 = !ledState2;              // Membalik status logika LED 2
    digitalWrite(ledPin2, ledState2);    // Menyalakan atau mematikan LED 2
  }
}