#include <Arduino_FreeRTOS.h>

// Deklarasi task
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void Taskprint(void *pvParameters);

void setup() {
    // Inisialisasi komunikasi serial
    Serial.begin(9600);

    // Membuat task 1
    xTaskCreate(
        TaskBlink1, // Fungsi task
        "task1",    // Nama task
        128,        // Stack size
        NULL,       // Parameter
        1,          // Priority
        NULL        // Task handle
    );

    // Membuat task 2
    xTaskCreate(
        TaskBlink2,
        "task2",
        128,
        NULL,
        1,
        NULL
    );

    // Membuat task 3
    xTaskCreate(
        Taskprint,
        "task3",
        128,
        NULL,
        1,
        NULL
    );

    // Menjalankan scheduler FreeRTOS
    vTaskStartScheduler();
}

void loop() {
    // Kosong karena menggunakan FreeRTOS
}

// Task LED blink pada pin 8
void TaskBlink1(void *pvParameters) {
    pinMode(8, OUTPUT);

    while (1) {
        Serial.println("Task1");

        digitalWrite(8, HIGH);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        digitalWrite(8, LOW);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

// Task LED blink pada pin 7
void TaskBlink2(void *pvParameters) {
    pinMode(7, OUTPUT);

    while (1) {
        Serial.println("Task2");

        digitalWrite(7, HIGH);
        vTaskDelay(300 / portTICK_PERIOD_MS);

        digitalWrite(7, LOW);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

// Task mencetak counter
void Taskprint(void *pvParameters) {
    int counter = 0;

    while (1) {
        counter++;

        Serial.println(counter);

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}