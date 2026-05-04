# Jawaban Pertanyaan Praktikum Modul 4: Percobaan 1 (ADC)

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1. Fungsi Perintah analogRead() pada Rangkaian Praktikum

Fungsi `analogRead()` pada Arduino digunakan untuk membaca nilai tegangan analog dari pin analog (seperti pin A0 yang terhubung ke potensiometer). Arduino memiliki fitur *Analog to Digital Converter* (ADC) dengan resolusi 10-bit, yang artinya tegangan analog yang dibaca (berkisar antara 0V hingga 5V) akan dikonversi atau dipetakan menjadi nilai digital dalam rentang angka **0 hingga 1023**.

---

## 2. Mengapa Diperlukan Fungsi map() dalam Program?

Fungsi `map()` diperlukan untuk proses penskalaan atau penyesuaian rentang nilai (scaling). 

Nilai digital hasil pembacaan potensiometer oleh ADC memiliki rentang dari **0 hingga 1023**. Sementara itu, motor servo umumnya hanya menerima perintah derajat putaran dalam rentang **0 hingga 180 derajat**. Jika kita langsung memasukkan nilai ADC ke dalam fungsi penggerak servo, servo tidak akan berfungsi dengan benar karena nilainya melebihi batas sudut yang mampu dibaca. Oleh karena itu, fungsi `map()` digunakan untuk mengonversi rentang input (0-1023) secara proporsional agar menjadi rentang output yang sesuai dengan sudut servo (0-180).

---

## 3. Program Modifikasi (Servo bergerak pada rentang 30° hingga 150°)

Berikut adalah source code program yang dimodifikasi beserta penjelasannya:

```cpp
#include <Servo.h> // library untuk servo motor

Servo myservo; // membuat objek servo

// ===================== PIN SETUP =====================
// Tentukan pin yang digunakan untuk potensiometer dan servo
const int potensioPin = A0;   // pin analog input untuk potensiometer
const int servoPin = 9;       // pin digital untuk servo (PWM)

// ===================== VARIABEL =====================
// Variabel untuk menyimpan data ADC dan sudut servo
int pos = 0; // inisialisasi awal variabel posisi sudut servo
int val = 0; // inisialisasi awal variabel data bacaan ADC

void setup() {
  // Hubungkan servo ke pin yang sudah ditentukan
  myservo.attach(servoPin); 

  // Aktifkan komunikasi serial untuk monitoring
  Serial.begin(9600); 
}

void loop() {
  // ===================== PEMBACAAN ADC =====================
  // Baca nilai dari potensiometer (rentang 0–1023)
  val = analogRead(potensioPin); 

  // ===================== KONVERSI DATA =====================
  // Ubah nilai ADC menjadi sudut servo modifikasi (30–150 derajat)
  pos = map(val, 0, 1023, 30, 150);  

  // ===================== OUTPUT SERVO =====================
  // Gerakkan servo sesuai hasil mapping
  myservo.write(pos); 

  // ===================== MONITORING DATA =====================
  // Tampilkan data ADC dan sudut servo ke Serial Monitor
  Serial.print("ADC Potensio: ");
  Serial.print(val); 

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos); 

  // ===================== STABILISASI =====================
  // Delay untuk memberi waktu servo bergerak stabil
  delay(15); 
}