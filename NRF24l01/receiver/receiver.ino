#include <SPI.h>
#include <RF24.h>

// Ustawienie pinów dla NRF24L01
RF24 radio(26, 27);  // CE, CSN

// Adresy rurek do komunikacji
const byte address[6] = "00001";

// Definicje pinów
const int ledPin = 15;  // Pin LED
bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);  // Konfiguracja LED

  // Inicjalizacja modułu NRF24L01
  SPI.begin(18, 19, 23, 27);         // SCK, MISO, MOSI, CSN
  radio.begin();
  radio.openReadingPipe(1, address); // Ustawienie adresu do odbioru
  radio.setPALevel(RF24_PA_HIGH);    // Ustawienie mocy odbioru
  radio.startListening();            // Rozpoczęcie nasłuchiwania
}

void loop() {
  // Sprawdzenie, czy jest dostępny pakiet do odczytu
  if (radio.available()) {
    // Odczyt odebranego stanu przycisku
    radio.read(&ledState, sizeof(ledState));

    // Ustawienie stanu LED na podstawie odebranej wartości
    digitalWrite(ledPin, ledState ? HIGH : LOW);
  }
}
