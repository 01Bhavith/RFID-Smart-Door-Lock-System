#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define RST_PIN         9
#define SS_PIN          10
#define SERVO_PIN       3
#define GREEN_LED       4
#define RED_LED         5
#define BUZZER          6

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Replace this with the UID of your own RFID card/tag!
String authorizedUID = "DD AA D4 05"; 

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo doorServo;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  doorServo.attach(SERVO_PIN);
  doorServo.write(0); // Initial door position (closed)
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  updateDisplay("Scan Card", "to unlock door");
  Serial.println("System Ready. Scan your RFID card.");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }

  // Read the UID
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  String scannedUID = content.substring(1);
  
  Serial.print("Card UID: ");
  Serial.println(scannedUID);

  if (scannedUID == authorizedUID) {
    grantAccess();
  } else {
    denyAccess();
  }
  
  // Halt PICC to stop reading the same card repeatedly
  mfrc522.PICC_HaltA();
}

void grantAccess() {
  updateDisplay("Access", "Granted!");
  digitalWrite(GREEN_LED, HIGH);
  tone(BUZZER, 1000); 
  delay(200);         
  noTone(BUZZER);
  
  doorServo.write(90); // Open door
  delay(3000);         // Keep door open for 3 seconds
  
  doorServo.write(0);  // Close door
  digitalWrite(GREEN_LED, LOW);
  updateDisplay("Scan Card", "to unlock door");
}

void denyAccess() {
  updateDisplay("Access", "Denied!");
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER, 300); 
  delay(1000);       
  noTone(BUZZER);
  
  digitalWrite(RED_LED, LOW);
  updateDisplay("Scan Card", "to unlock door");
}

void updateDisplay(String line1, String line2) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(line1);
  
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println(line2);
  display.display();
}