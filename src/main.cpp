#include <Arduino.h>

void printMemoryInfo() {
    Serial.println("\n=== INFORMACJA O PAMIĘCI ===");
    
    // Podstawowa informacja o PSRAM
    if (psramFound()) {
        Serial.println("✅ PSRAM ZNALEZIONY!");
        Serial.printf("Rozmiar PSRAM: %d bajtów (%.1f MB)\n", 
                     ESP.getPsramSize(), ESP.getPsramSize() / 1024.0 / 1024.0);
        Serial.printf("Wolne PSRAM: %d bajtów\n", ESP.getFreePsram());
    } else {
        Serial.println("❌ PSRAM NIEDOSTĘPNY");
    }
    
    // Test alokacji PSRAM
    Serial.println("\n=== TEST ALOKACJI PSRAM ===");
    size_t testSize = 1000000;  // 1MB
    
    void* psramBuffer = ps_malloc(testSize);
    if (psramBuffer != NULL) {
        Serial.printf("✅ Alokacja %d bajtów PSRAM - SUKCES\n", testSize);
        Serial.printf("Użyte PSRAM: %d bajtów\n", ESP.getPsramSize() - ESP.getFreePsram());
        
        // Wypełnij bufor danymi
        memset(psramBuffer, 0xAA, testSize);
        Serial.println("Bufor wypełniony danymi testowymi");
        
        free(psramBuffer);
        Serial.printf("Zwolniono - wolne PSRAM: %d bajtów\n", ESP.getFreePsram());
    } else {
        Serial.printf("❌ BŁĄD alokacji %d bajtów PSRAM\n", testSize);
    }
    
    // Porównanie pamięci
    Serial.println("\n=== PORÓWNANIE PAMIĘCI ===");
    Serial.printf("Całkowita Heap: %d bajtów\n", ESP.getHeapSize());
    Serial.printf("Wolna Heap: %d bajtów\n", ESP.getFreeHeap());
    Serial.printf("Flash: %d bajtów\n", ESP.getFlashChipSize());
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    printMemoryInfo();
}

void loop() {
    delay(10000);
    printMemoryInfo();
}
