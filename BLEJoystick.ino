#include <BLEDevice.h>
#include <BLEHIDDevice.h>
#include <BLEJoystick.h>

// Gaz vermek için kullanılacak pin numarası
#define GAS_PIN 25

// Gaz pini için ayarlamalar
BLEJoystick joystick(BLEHIDDevice::JOYSTICK);
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

  // Joystick ayarlamaları
  joystick.begin();
  joystick.setButtonCount(12);
  joystick.setAxesCount(6);
  pCharacteristic = joystick.getButton(1);
}

void loop() {
  // Rastgele gaz seviyesi belirleme (0-255 arasında)
  int gas_level = random(256);

  // Gaz verme
  analogWrite(GAS_PIN, gas_level);

  // Joystick verilerini güncelleme
  joystick.setAxis(1, gas_level);
  joystick.sendState();

  // 0.5 saniye bekleme
  delay(500);
}
