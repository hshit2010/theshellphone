#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

byte rowPins[4] = {13, 12, 14, 27};
byte colPins[3] = {26, 25, 33};
char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 3);
String dialedNumber = "";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("DenDenMushi");
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);
  display.setCursor(0, 20);
  display.println("Ready");
  display.display();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
      dialedNumber = dialedNumber + key;
      
      display.clearDisplay();
      display.setCursor(0, 20);
      display.println(dialedNumber);
      display.display();

      if (dialedNumber.length() == 10) {
        display.clearDisplay();
        display.setCursor(0, 10);
        display.println("Calling:");
        display.println(dialedNumber);
        display.display();
        
        SerialBT.print("ATD");
        SerialBT.print(dialedNumber);
        SerialBT.println(";");
        
        delay(5000);
        
        dialedNumber = "";
        
        display.clearDisplay();
        display.setCursor(0, 20);
        display.println("Ready");
        display.display();
      }
    }
  }
}