#include <BLEDevice.h>
#include <BLEHIDDevice.h>
#include <BLEGamepad.h>

// Gaz vermek için kullanılacak pin numarası
#define GAS_PIN 25

// Gaz pini için ayarlamalar
BLEGamepad gamepad;
BLECharacteristic* pCharacteristic;

void setup() {
  // Bluetooth bağlantısı başlatma
  BLEDevice::init("ESP32 Gamepad");
  BLEServer *pServer = BLEDevice::createServer();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pServer->startAdvertising();

  // Gaz pini için ayarlamalar
  pinMode(GAS_PIN, OUTPUT);
  digitalWrite(GAS_PIN, LOW);

  // Gamepad ayarlamaları
  gamepad.begin();
}

void loop() {
  // Rastgele gaz seviyesi belirleme (0-255 arasında)
  int gas_level = random(256);

  // Gaz verme
  analogWrite(GAS_PIN, gas_level);

  // Gamepad verilerini güncelleme
  gamepad.setAxis(GAMEPAD_AXIS_RIGHT_Y, gas_level);
  gamepad.sendReport();

  // 0.5 saniye bekleme
  delay(500);
}
