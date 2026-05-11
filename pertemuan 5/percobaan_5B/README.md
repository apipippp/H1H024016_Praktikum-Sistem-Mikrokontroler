# Jawaban Pertanyaan Praktikum Modul 5: Percobaan 5B (Komunikasi Task)

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task (`read_data` dan `display`) berjalan secara **bergantian** (*concurrent*), bukan benar-benar bersamaan (*parallel*), karena arsitektur mikrokontroler Arduino Uno menggunakan prosesor *single-core*. 

Mekanisme pergantian ini dikendalikan oleh *Scheduler* dari FreeRTOS yang dipadukan dengan mekanisme **Queue**. 
1. Task `read_data` akan berjalan lebih dulu untuk membaca sensor (atau menetapkan variabel statis pada percobaan awal). Setelah itu, data dikirim ke dalam antrean menggunakan `xQueueSend()`. 
2. Saat task `read_data` memasuki fase `vTaskDelay()`, statusnya akan menjadi *Blocked*. Scheduler kemudian mengalihkan CPU untuk mengeksekusi task `display`. 
3. Task `display` yang tadinya berada dalam status *Blocked* (menunggu isi antrean masuk lewat `xQueueReceive()`) akan aktif, mengambil data dari *queue*, menampilkannya di Serial Monitor, lalu kembali menunggu data baru. Proses operan ini berlangsung sangat cepat secara terus menerus.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini **tidak berpotensi mengalami *race condition*** berkat penggunaan **Queue**. 

Dalam sistem *multitasking*, *race condition* terjadi jika ada dua atau lebih task yang saling berebut untuk memodifikasi satu sumber daya bersama (*shared resource* atau *global variable*) di saat yang bersamaan tanpa sinkronisasi yang tepat. 

Pada program ini, komunikasi antar task diwadahi melalui *Queue* bawaan FreeRTOS yang sudah bersifat *Thread-Safe*. Fungsi `xQueueSend` dan `xQueueReceive` akan secara otomatis mengamankan alur data. Jika `my_queue` sedang diisi oleh task pengirim, task penerima tidak bisa mencampuri instruksi tersebut sebelum datanya masuk secara utuh. Terlebih lagi, variabel struktur `readings x` diinisialisasi secara lokal di masing-masing fungsi task, sehingga benar-benar tidak ada variabel global yang rentan tumpang tindih.

---

## 3. Program Modifikasi (Menggunakan Sensor DHT Sesungguhnya)

Berikut adalah source code modifikasi program yang ditambahkan librari DHT agar data suhu dan kelembaban menjadi dinamis:

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "DHT.h" // Menambahkan library sensor DHT

#define DHTPIN 2      // Menentukan pin yang terhubung ke sensor DHT
#define DHTTYPE DHT11 // Menentukan tipe DHT (DHT11/DHT22)

DHT dht(DHTPIN, DHTTYPE); // Membuat objek dht

// Modifikasi struct: menggunakan tipe data float untuk nilai desimal sensor
struct readings {
  float temp;
  float h;
};

QueueHandle_t my_queue;

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {
  Serial.begin(9600);
  dht.begin(); // Menginisialisasi pembacaan sensor DHT

  // Membuat queue dengan kapasitas 1 item dari struct readings
  my_queue = xQueueCreate(1, sizeof(struct readings));
  
  if (my_queue != NULL) {
    // Membuat task dengan prioritas yang sama
    xTaskCreate(read_data, "ReadSensors", 128, NULL, 1, NULL);
    xTaskCreate(display, "Display", 128, NULL, 1, NULL);
  }
}

void loop() {
  // Loop dibiarkan kosong karena scheduler RTOS yang berjalan
}

void read_data(void *pvParameters) {
  struct readings x;
  for(;;) {
    // Membaca suhu dan kelembaban aktual dari sensor
    x.temp = dht.readTemperature();
    x.h = dht.readHumidity();

    // Error handling sederhana jika sensor gagal dibaca
    if (isnan(x.temp) || isnan(x.h)) {
      x.temp = 0.0;
      x.h = 0.0;
    }

    // Mengirim struct data ke queue
    xQueueSend(my_queue, &x, portMAX_DELAY);
    
    // Memberikan jeda karena sensor DHT membutuhkan waktu untuk update data
    vTaskDelay(2000 / portTICK_PERIOD_MS); 
  }
}

void display(void *pvParameters) {
  struct readings x;
  for(;;) {
    // Menunggu kiriman data dari queue
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
      // Menampilkan output yang sudah dinamis
      Serial.print("Suhu = ");
      Serial.print(x.temp);
      Serial.print(" *C | Kelembaban = ");
      Serial.print(x.h);
      Serial.println(" %");
    }
  }
}