#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Struktur data sensor
struct readings {
    int temp;
    int h;
};

// Membuat queue
QueueHandle_t my_queue;

// Deklarasi task
void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {
    Serial.begin(9600);

    // Membuat queue dengan kapasitas 1 data
    my_queue = xQueueCreate(1, sizeof(struct readings));

    // Membuat task
    xTaskCreate(
        read_data,      // Fungsi task
        "read sensors", // Nama task
        128,            // Stack size
        NULL,           // Parameter
        0,              // Priority
        NULL            // Task handle
    );

    xTaskCreate(
        display,
        "display",
        128,
        NULL,
        0,
        NULL
    );
}

void loop() {
    // Kosong karena menggunakan FreeRTOS task
}

// Task membaca data sensor
void read_data(void *pvParameters) {
    struct readings x;

    for (;;) {
        x.temp = 54;
        x.h = 30;

        // Mengirim data ke queue
        xQueueSend(my_queue, &x, portMAX_DELAY);

        vTaskDelay(100);
    }
}

// Task menampilkan data
void display(void *pvParameters) {
    struct readings x;

    for (;;) {
        // Menerima data dari queue
        if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {

            Serial.print("temp = ");
            Serial.println(x.temp);

            Serial.print("humidity = ");
            Serial.println(x.h);
        }
    }
}