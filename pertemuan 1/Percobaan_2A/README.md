# Jawaban Pertanyaan Praktikum: Modul I Percabangan dan Perulangan

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
[cite_start]**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller [cite: 5]

---

## 1.6.4 Pertanyaan Praktikum (Perulangan)

### 1. Rangkaian Schematic 5 LED Running
[cite_start]*(Mengacu pada Tabel 1.1 di modul, rangkaian dikonfigurasikan menggunakan 6 LED pada pin 2 hingga 7)*[cite: 205, 207]. 

### 2. Bagaimana program membuat efek LED berjalan dari kiri ke kanan?
Program menciptakan efek berjalan dari kiri ke kanan dengan memanfaatkan struktur perulangan naik (increment). [cite_start]Kode `for (int pinLed = 2; pinLed < 8; pinLed++)` akan mengakses pin Arduino secara berurutan dimulai dari nilai pin terendah (pin 2) ke pin yang lebih tinggi (hingga pin 7)[cite: 183, 188]. [cite_start]Di dalam perulangan tersebut, setiap LED dihidupkan dengan logika `HIGH`, diberikan jeda waktu dengan `delay()`, lalu dimatikan dengan logika `LOW` [cite: 190-193]. Karena proses ini dieksekusi pin demi pin secara berurutan ke atas, terciptalah efek visual lampu berjalan ke arah kanan.

### 3. Bagaimana program membuat LED kembali dari kanan ke kiri?
Untuk membalikkan arah pergerakan, program menggunakan perulangan turun (decrement). [cite_start]Kode `for (int pinLed = 7; pinLed >= 2; pinLed--)` mengeksekusi instruksi dari nilai pin tertinggi (pin 7) dan menghitung mundur hingga pin terendah (pin 2)[cite: 195]. [cite_start]Proses yang terjadi di dalamnya sama persis (menyalakan, menahan, lalu mematikan LED) [cite: 196-200], namun karena urutan pinnya dibaca secara terbalik (dari kanan ke kiri secara fisik), maka nyala LED pun terlihat bergerak kembali dari arah kanan ke kiri.

### 4. Program LED Menyala Tiga Kiri dan Tiga Kanan Bergantian
Berikut adalah kode program untuk menyalakan 3 LED kiri (Pin 2, 3, 4) dan 3 LED kanan (Pin 5, 6, 7) secara bergantian, beserta penjelasan di setiap baris kodenya.

```cpp
int waktuJeda = 500;              // Menentukan durasi delay perpindahan sebesar 500 milidetik

void setup() {
  // Menggunakan loop for untuk menginisialisasi setiap pin (2 sampai 7) sebagai output
  for (int pinLed = 2; pinLed < 8; pinLed++) { 
    pinMode(pinLed, OUTPUT);      // Menetapkan pin yang sedang diakses sebagai OUTPUT
  }
}

void loop() {
  // --- FASE 1: Menyalakan 3 LED Kiri (Pin 2, 3, dan 4) ---
  for (int i = 2; i <= 4; i++) {  // Melakukan perulangan untuk pin 2, 3, dan 4
    digitalWrite(i, HIGH);        // Menghidupkan LED pada pin tersebut dengan sangat cepat (terlihat bersamaan)
  }
  
  delay(waktuJeda);               // Menahan posisi 3 LED kiri dalam keadaan menyala selama 500ms
  
  for (int i = 2; i <= 4; i++) {  // Melakukan perulangan kembali untuk pin 2, 3, dan 4
    digitalWrite(i, LOW);         // Mematikan 3 LED kiri tersebut
  }

  // --- FASE 2: Menyalakan 3 LED Kanan (Pin 5, 6, dan 7) ---
  for (int i = 5; i <= 7; i++) {  // Melakukan perulangan untuk pin 5, 6, dan 7
    digitalWrite(i, HIGH);        // Menghidupkan 3 LED kanan
  }
  
  delay(waktuJeda);               // Menahan posisi 3 LED kanan dalam keadaan menyala selama 500ms
  
  for (int i = 5; i <= 7; i++) {  // Melakukan perulangan kembali untuk pin 5, 6, dan 7
    digitalWrite(i, LOW);         // Mematikan 3 LED kanan sebelum siklus perulangan kembali ke Fase 1
  }
}