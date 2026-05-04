# Jawaban Pertanyaan Praktikum Modul 4: Percobaan 2 (PWM)

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()?

Fungsi `analogWrite()` tidak benar-benar mengeluarkan tegangan analog murni, melainkan menggunakan teknik **PWM (Pulse Width Modulation)**. PWM memanipulasi sinyal digital (HIGH dan LOW) dengan cara mengatur seberapa lama sinyal berada dalam keadaan HIGH (menyala) dalam satu periode waktu tertentu, yang disebut sebagai *duty cycle*. 

Dengan mengubah persentase *duty cycle*, Arduino dapat mengubah nilai "tegangan rata-rata" yang diterima oleh LED. Jika *duty cycle* besar (HIGH lebih lama daripada LOW), maka tegangan rata-rata akan tinggi dan LED menyala terang. Sebaliknya, jika *duty cycle* kecil, tegangan rata-rata menjadi rendah dan LED terlihat meredup. Mata manusia tidak bisa melihat kedipan sinyal digital yang sangat cepat ini, sehingga yang terlihat hanyalah perubahan intensitas cahaya (analog semu).

---

## 2. Hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)

Hubungan antara keduanya didasarkan pada perbedaan resolusi sistem perangkat keras di dalam mikrokontroler Arduino Uno:
- **ADC (Analog to Digital Converter)** pada Arduino Uno memiliki resolusi **10-bit**, yang berarti mampu memecah sinyal tegangan analog menjadi $2^{10}$ atau **1024** tingkatan nilai (dari **0 hingga 1023**).
- **PWM (Pulse Width Modulation)** pada Arduino Uno diatur oleh timer dengan resolusi **8-bit**, yang berarti hanya mampu menerima $2^8$ atau **256** tingkatan nilai (dari **0 hingga 255**).

Karena perbedaan batas nilai ini, nilai ADC dari sensor (0-1023) tidak bisa langsung dimasukkan sebagai output PWM. Harus ada proses penskalaan *(scaling)*, biasanya menggunakan fungsi `map()` atau dengan cara membagi rentang nilai ADC dengan angka 4 ($1024 \div 4 = 256$), agar rentang nilai dari input selaras dengan kapasitas rentang output.

---

## 3. Program Modifikasi (LED hanya menyala pada rentang PWM 50-200)

Berikut adalah source code program yang dimodifikasi beserta penjelasannya:

```cpp
#include <Arduino.h> 

// ===================== PIN SETUP =====================
const int potPin = A0;   // pin analog untuk membaca potensiometer
const int ledPin = 9;    // pin digital PWM untuk output ke LED

// ===================== VARIABEL =====================
int nilaiADC = 0;  
int pwm = 0;       

void setup() {
  // Atur pin LED sebagai output
  pinMode(ledPin, OUTPUT);

  // Aktifkan komunikasi serial
  Serial.begin(9600); 
}

void loop() {
  // ===================== PEMBACAAN SENSOR =====================
  nilaiADC = analogRead(potPin); 

  // ===================== PEMROSESAN DATA =====================
  // Mapping dasar dari rentang ADC ke rentang PWM maksimal
  pwm = map(nilaiADC, 0, 1023, 0, 255);  

  // ===================== LOGIKA MODIFIKASI =====================
  // LED hanya menyala jika nilai PWM berada di antara 50 dan 200
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm); // LED menyala sesuai kecerahan PWM saat ini
  } else {
    analogWrite(ledPin, 0);   // Di luar rentang 50-200, matikan LED (PWM = 0)
  }

  // ===================== MONITORING DATA =====================
  Serial.print("ADC: ");
  Serial.print(nilaiADC); 

  Serial.print(" | PWM Awal: ");
  Serial.print(pwm); 
  
  Serial.print(" | Status LED: ");
  if (pwm >= 50 && pwm <= 200) {
    Serial.println("MENYALA");
  } else {
    Serial.println("MATI");
  }

  // Delay untuk stabilisasi
  delay(50); 
}