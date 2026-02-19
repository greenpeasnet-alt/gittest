#include <Arduino.h>

void taskPrintDot(void *parameter) {
    for(;;) {
        Serial.print(".");
        vTaskDelay(pdMS_TO_TICKS(1000));  
    }
}

void setup() {
    Serial.begin(115200);
    
    while (!Serial);
    
    Serial.println("\n== Start  ==");
    
    xTaskCreatePinnedToCore(
        taskPrintDot,       
        "PrintDotTask",     
        2048,               
        NULL,              
        1,                 
        NULL,               
        1                
    );
    
    Serial.println("Zadanie RTOS utworzone!");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
