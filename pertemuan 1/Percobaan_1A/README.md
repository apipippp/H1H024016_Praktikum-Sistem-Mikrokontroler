# Jawaban Pertanyaan Praktikum: Modul I Percabangan dan Perulangan

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## 1.5.4 Pertanyaan Praktikum (Percabangan)

**1. Pada kondisi apa program masuk ke blok if?**
Program akan masuk ke blok `if` ketika variabel `timeDelay` memiliki nilai kurang dari atau sama dengan 100 (`timeDelay <= 100`).

**2. Pada kondisi apa program masuk ke blok else?**
Program akan masuk ke blok `else` ketika kondisi pada `if` tidak terpenuhi, yaitu ketika nilai `timeDelay` masih lebih besar dari 100.

**3. Apa fungsi dari perintah `delay(timeDelay)`?**
Fungsi dari perintah `delay(timeDelay)` adalah untuk memberikan jeda waktu (dalam satuan milidetik) saat menyalakan dan mematikan LED. Karena nilai `timeDelay` dikurangi secara bertahap dalam perulangan program, instruksi ini menciptakan efek nyala kedip LED yang semakin cepat.

**4. Jika program yang dibuat memiliki alur mati → lambat → cepat reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya!**

Berikut adalah modifikasi kodenya beserta penjelasan baris per baris:

```cpp
const int ledPin = 6;           // Mendefinisikan pin 6 untuk LED
int timeDelay = 1000;           // Menginisialisasi delay awal sebesar 1000ms (1 detik)
bool isSpeedingUp = true;       // Membuat variabel penanda (flag) untuk menentukan fase kedipan (mempercepat atau memperlambat)

void setup() {
  pinMode(ledPin, OUTPUT);      // Mengatur ledPin (pin 6) sebagai pin OUTPUT
}

void loop() {
  digitalWrite(ledPin, HIGH);   // Menyalakan LED
  delay(timeDelay);             // Menahan kondisi menyala selama durasi timeDelay saat ini
  digitalWrite(ledPin, LOW);    // Mematikan LED
  delay(timeDelay);             // Menahan kondisi mati selama durasi timeDelay saat ini

  // Logika untuk mengubah fase kecepatan
  if (isSpeedingUp) {           // Jika sedang dalam fase mempercepat (nyala lambat -> cepat)
    timeDelay -= 100;           // Mengurangi delay sebesar 100ms agar kedipan semakin cepat
    
    if (timeDelay <= 100) {     // Mengecek apakah kecepatan sudah mencapai batas maksimal (delay terkecil 100ms)
      isSpeedingUp = false;     // Jika ya, ubah penanda fase menjadi fase memperlambat (false)
    }
  } else {                      // Jika sedang dalam fase memperlambat (nyala cepat -> sedang -> mati)
    timeDelay += 300;           // Menambah delay sebesar 300ms agar kedipan melambat
    
    if (timeDelay >= 1000) {    // Mengecek apakah kedipan sudah kembali lambat / pada batas awal
      isSpeedingUp = true;      // Reset penanda fase kembali ke fase mempercepat
      delay(3000);              // Memberikan jeda waktu diam 3 detik sebagai representasi fase "mati/reset" sebelum siklus diulang
    }
  }
}