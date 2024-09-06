#include <SPI.h>
#include <RF24.h>

// Ustawienie pinów dla NRF24L01
RF24 radio(26, 27);  // CE, CSN

// Adresy rurek do komunikacji
const byte address[6] = "00001";

// Definicje pinów
const int buttonPin = 4;  // Pin przycisku
const int ledPin = 15;    // Pin LED
bool buttonState = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Konfiguracja przycisku
  pinMode(ledPin, OUTPUT);           // Konfiguracja LED

  // Inicjalizacja modułu NRF24L01
  SPI.begin(18, 19, 23, 27);         // SCK, MISO, MOSI, CSN
  radio.begin();
  radio.openWritingPipe(address);    // Ustawienie adresu do wysyłania
  radio.setPALevel(RF24_PA_HIGH);    // Ustawienie mocy nadawania
  radio.stopListening();             // Zatrzymanie nasłuchiwania (tryb nadawania)
}

void loop() {
  // Odczyt stanu przycisku
  bool currentButtonState = digitalRead(buttonPin) == LOW;

  // Sprawdzenie, czy stan przycisku zmienił się
  if (currentButtonState != buttonState) {
    buttonState = currentButtonState;
    
    // Wysłanie aktualnego stanu przycisku do odbiorcy
    radio.write(&buttonState, sizeof(buttonState));
  }

  // Sygnalizacja przyciskiem lokalnym LED
  digitalWrite(ledPin, buttonState ? HIGH : LOW);
}
