# Jawaban Pertanyaan Praktikum Modul 5: Percobaan 5A (Multitasking)

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Pada sistem mikrokontroler Arduino Uno yang memiliki prosesor *single-core*, ketiga task tersebut berjalan secara **bergantian** (*concurrent*), bukan benar-benar berjalan bersamaan secara fisik pada satu waktu (*parallel*). 

Mekanisme ini diatur oleh komponen dari FreeRTOS yang disebut sebagai *Kernel Scheduler*. *Scheduler* ini bertugas membagi waktu pemrosesan CPU untuk masing-masing task. Ketika sebuah task sedang dieksekusi lalu memasuki masa tunda/jeda (misalnya dipanggilnya fungsi `vTaskDelay`), status task tersebut berubah menjadi *blocked*. Saat itulah *scheduler* mengambil alih CPU dan mengalihkannya untuk mengeksekusi task lain yang sedang dalam status siap (*ready*). Proses pergantian task (context switching) ini dilakukan dalam kecepatan yang sangat tinggi, sehingga dari sudut pandang pengguna, ketiga task tersebut seolah-olah berjalan secara bersamaan (multitasking).

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Untuk menambahkan task keempat pada program, berikut adalah langkah-langkah yang harus dilakukan:

1. **Deklarasi Purwarupa Task:** Deklarasikan nama fungsi task keempat di bagian atas program sebelum fungsi `setup()`. Contoh: `void TaskKeempat(void *pvParameters);`.
2. **Registrasi Task dengan `xTaskCreate()`:** Di dalam fungsi `setup()`, tambahkan pemanggilan fungsi `xTaskCreate()` untuk mendaftarkan task tersebut ke *scheduler* RTOS. Masukkan 6 argumen yang diperlukan: nama fungsi yang dieksekusi, string nama task (misal `"task4"`), ukuran *stack memory* (misal `128`), parameter *pointer* (`NULL`), nilai prioritas (misal `1`), dan *task handle* (`NULL`).
3. **Membuat Implementasi Fungsi:** Buat struktur fungsi `void TaskKeempat(void *pvParameters)` di luar fungsi `loop()`.
4. **Menambahkan Loop dan Delay:** Di dalam fungsi task tersebut, buat *infinite loop* menggunakan `while(1)` agar instruksi terus berjalan. Sangat penting untuk menyertakan fungsi `vTaskDelay()` di dalam loop tersebut agar task memberikan kesempatan waktu bagi task lain untuk dieksekusi oleh CPU.

---

## 3. Program Modifikasi (Kontrol Kecepatan LED dengan Potensiometer)

Pada modifikasi ini, task baru (atau task yang sudah ada) diubah agar dapat membaca nilai sensor (potensiometer), kemudian menggunakan pembacaan tersebut untuk mengatur nilai penundaan pada fungsi kedip (blink) LED.

### Source Code:

```cpp
#include <Arduino_FreeRTOS.h>

// Deklarasi task
void TaskBlinkLED(void *pvParameters);
void TaskReadPotensio(void *pvParameters);

// Variabel global untuk menyimpan delay LED
int ledDelay = 500; 
const int potPin = A0; // Pin analog potensiometer
const int ledPin = 8;  // Pin LED

void setup() {
  Serial.begin(9600);

  // Membuat Task 1: Mengontrol Kedipan LED
  xTaskCreate(TaskBlinkLED, "BlinkLED", 128, NULL, 1, NULL);
  
  // Membuat Task 2: Membaca Potensiometer
  xTaskCreate(TaskReadPotensio, "ReadPot", 128, NULL, 1, NULL);

  // Memulai scheduler RTOS
  vTaskStartScheduler();
}

void loop() {
  // Kosong karena scheduler RTOS sudah mengambil alih loop utama
}

// Implementasi Task 1
void TaskBlinkLED(void *pvParameters) {
  pinMode(ledPin, OUTPUT);
  while(1) {
    digitalWrite(ledPin, HIGH);
    // Delay sesuai dengan variabel global yang diubah potensiometer
    vTaskDelay(ledDelay / portTICK_PERIOD_MS); 
    
    digitalWrite(ledPin, LOW);
    vTaskDelay(ledDelay / portTICK_PERIOD_MS);
  }
}

// Implementasi Task 2
void TaskReadPotensio(void *pvParameters) {
  while(1) {
    int potValue = analogRead(potPin); // Membaca nilai potensiometer (0-1023)
    
    // Mapping nilai potensiometer menjadi delay (misal: 50ms - 1000ms)
    ledDelay = map(potValue, 0, 1023, 50, 1000); 
    
    Serial.print("Nilai Potensiometer: ");
    Serial.print(potValue);
    Serial.print(" | Delay LED: ");
    Serial.println(ledDelay);
    
    // Memberikan jeda pembacaan ADC (Context Switch)
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}