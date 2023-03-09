#include <BlePeripheral.h>

// Gaz vermek için kullanılacak pin numarası
#define GAS_PIN 10

BlePeripheral blePeripheral;

void setup() {
  // Bluetooth bağlantısı başlatma
  blePeripheral.setLocalName("Arduino Gamepad");
  blePeripheral.setDeviceName("Arduino Gamepad");
  blePeripheral.setAppearance(BLE_APPEARANCE_GENERIC_GAMEPAD);
  blePeripheral.begin();

  // Gaz pini için ayarlamalar
  pinMode(GAS_PIN, OUTPUT);
  digitalWrite(GAS_PIN, LOW);
}

void loop() {
  // Rastgele gaz seviyesi belirleme (0-255 arasında)
  int gas_level = random(256);

  // Gaz verme
  analogWrite(GAS_PIN, gas_level);

  // Gamepad verilerini güncelleme
  uint8_t gamepad_data[5] = {
    0x01,         // Report ID (always 0x01 for gamepad)
    0x00,         // Buttons (not used in this example)
    gas_level,    // Right joystick Y-axis (gaz)
    0x80,         // Left joystick X-axis (not used in this example)
    0x80          // Left joystick Y-axis (not used in this example)
  };
  blePeripheral.notifyCharacteristic(gamepad_data, sizeof(gamepad_data));

  // 0.5 saniye bekleme
  delay(500);
}
