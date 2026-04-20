# Jawaban Pertanyaan Praktikum Modul 2: Pemrograman GPIO

**Nama:** Afif Nur Rahman  
**NIM:** H1H024016  
**Mata Kuliah:** TK244005-Praktikum Sistem Mikrokontroller

---

## Bagian 3.5.4: Percobaan 3A (UART)

## 1. Proses Input Keyboard hingga LED Menyala/Mati

1. User mengetik perintah pada Serial Monitor.
2. Data dikirim ke Arduino melalui komunikasi UART.
3. Arduino membaca data menggunakan `Serial.read()`.
4. Data diperiksa:

   - '1' → LED menyala
   - '0' → LED mati
   - '2' → LED berkedip (setelah modifikasi pada soal no 3)
5. Arduino mengontrol LED melalui pin digital (pin 12/8).

---

## 2. Fungsi Serial.available()

Digunakan untuk mengecek apakah ada data yang masuk ke Arduino:

```cpp
if (Serial.available() > 0)
```

### Fungsi:

- Mencegah pembacaan data kosong
- Menghindari error

### Jika dihilangkan:

- Arduino tetap membaca walaupun tidak ada data
- Bisa menghasilkan nilai acak
- Program menjadi tidak stabil

---

## 3. Program Modifikasi (LED Blink saat input '2')

```cpp
int led = 12;
char data;
bool blinkMode = false;

void setup() {
  pinMode(led, OUTPUT);      // Set pin LED sebagai output
  Serial.begin(9600);        // Memulai komunikasi serial
}

void loop() {

  if (Serial.available() > 0) {   // Cek apakah ada data masuk
    data = Serial.read();         // Membaca data dari serial

    if (data == '1') {
      digitalWrite(led, HIGH);    // LED menyala
      blinkMode = false;          // Matikan mode blink
    }
    else if (data == '0') {
      digitalWrite(led, LOW);     // LED mati
      blinkMode = false;
    }
    else if (data == '2') {
      blinkMode = true;           // Aktifkan mode blink
    }
    else {
      Serial.println("Input tidak valid!"); // Jika input salah
    }
  }

  if (blinkMode == true) {
    digitalWrite(led, HIGH);  // LED ON
    delay(500);               // Tunggu 500 ms
    digitalWrite(led, LOW);   // LED OFF
    delay(500);               // Tunggu 500 ms
  }
}
```

---

## 4. Penggunaan delay() atau millis()

Pada program ini digunakan `delay()`.

### Pengaruh delay():

- Program berhenti sementara selama delay
- Sederhana dan mudah digunakan

### Jika menggunakan millis():

- Program tidak berhenti (non-blocking)
- Lebih cocok untuk sistem kompleks

### Kesimpulan:

Untuk percobaan ini, `delay()` sudah cukup karena sistem masih sederhana.