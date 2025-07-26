#include "arduino_secrets.h"
#include <TFT_eSPI.h>
#include "thingProperties.h"
#include <ArduinoIoTCloud.h>
#include <WiFi.h>
#include <Arduino_ConnectionHandler.h>
#include <ESP_Mail_Client.h>

// Pin Definitions
#define TRIG_PIN 5
#define ECHO_PIN 18
#define GREEN_LED_PIN 21
#define YELLOW_LED_PIN 22
#define RED_LED_PIN 23
#define IR_SENSOR_PIN 4
#define TFT_BL 15
#define VIBRATION_SENSOR_PIN 19
#define BUZZER_PIN 17

// Email credentials
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define EMAIL_SENDER "systemalcohol@gmail.com"
#define EMAIL_APP_PASSWORD "nkdp oxan daow bqjz"
#define EMAIL_RECIPIENT "jarredhexico@gmail.com"

// Global variables
long duration;
int measuredDistance;
bool emailSent = false;
bool previousIRState = false;

TFT_eSPI tft = TFT_eSPI();
SMTPSession smtp;
SMTP_Message message;

void setup() {
  Serial.begin(9600);
  delay(1500);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  tft.init();
  tft.setRotation(0);

  ledcSetup(0, 5000, 8);  // Red
  ledcSetup(1, 5000, 8);  // Green
  ledcSetup(2, 5000, 8);  // Yellow
  ledcSetup(3, 5000, 8);  // Backlight
  ledcAttachPin(RED_LED_PIN, 0);
  ledcAttachPin(GREEN_LED_PIN, 1);
  ledcAttachPin(YELLOW_LED_PIN, 2);
  ledcAttachPin(TFT_BL, 3);
  ledcWrite(3, 255); // Full backlight

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(VIBRATION_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is off at startup

  drawUI();
  showAlarm(); // Show vibration alarm message initially
}

void drawUI() {
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 20); tft.println("Alcohol Monitoring System");
  tft.setCursor(10, 40); tft.println("Emilio Aguinaldo College");
  tft.setCursor(90, 60); tft.println("Building 7");

  tft.fillRoundRect(40, 100, 240, 180, 20, TFT_DARKGREY);
  tft.setCursor(80, 110); tft.println("Alcohol Level");

  tft.fillRoundRect(40, 300, 240, 140, 20, TFT_DARKGREY);
  tft.setCursor(80, 310); tft.println("System Status");
}

void updateGauge(int alcoholLevel) {
  uint16_t color;

  if (alcoholLevel > 50) {
    color = TFT_GREEN;
    ledcWrite(0, 0);
    ledcWrite(1, 200);
    ledcWrite(2, 0);
  } else if (alcoholLevel > 20) {
    color = TFT_YELLOW;
    ledcWrite(0, 200);
    ledcWrite(1, 200);
    ledcWrite(2, 0);
  } else {
    color = TFT_RED;
    ledcWrite(0, 200);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
  }

  tft.fillRoundRect(50, 150, 220, 110, 10, color);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(4);
  tft.setCursor(115, 180);
  tft.printf("%d%%", alcoholLevel);
}

void updateStatus(bool objectDetected) {
  uint16_t statusColor = objectDetected ? TFT_GREEN : TFT_RED;
  tft.fillRoundRect(50, 340, 220, 90, 10, statusColor);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(4);
  tft.setCursor(130, 365);
  tft.println(objectDetected ? "ON" : "OFF");
}

int readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  measuredDistance = duration * 0.034 / 2;
  return measuredDistance;
}

bool detectObject() {
  return digitalRead(IR_SENSOR_PIN) == LOW;
}

void sendEmailNotification() {
  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = EMAIL_SENDER;
  session.login.password = EMAIL_APP_PASSWORD;
  session.login.user_domain = "";

  smtp.debug(1);
  smtp.callback([](SMTP_Status status) {
    Serial.println(status.info());
  });

  message.sender.name = "ESP32 Alert";
  message.sender.email = EMAIL_SENDER;
  message.subject = "Low Alcohol Level Warning";
  message.addRecipient("Alert", EMAIL_RECIPIENT);
  message.text.content = "Warning! Alcohol level has dropped below 20%.";
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;

  if (!smtp.connect(&session)) {
    Serial.println("SMTP connection failed.");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.print("Send mail failed: ");
    Serial.println(smtp.errorReason());
  } else {
    Serial.println("Email sent successfully!");
  }

  smtp.closeSession();
}

void showAlarm() {
  tft.fillRoundRect(60, 270, 200, 40, 10, TFT_RED);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(75, 285);
  tft.println("Vibration Alarm!");
}

void clearAlarm() {
  tft.fillRoundRect(60, 270, 200, 40, 10, TFT_DARKGREY);
}

void loop() {
  ArduinoCloud.update();

  int rawDistance = readDistance();
  int level = map(rawDistance, 2, 10, 100, 0);
  level = constrain(level, 0, 100);
  level = max(0, level);
  alcoholLevel = level;
  updateGauge(alcoholLevel);

  bool currentIRState = detectObject();
  objectDetected = currentIRState;
  updateStatus(currentIRState);

  if (currentIRState && !previousIRState) {
    usageData++;
    ArduinoCloud.update();
  }
  previousIRState = currentIRState;

  if (alcoholLevel < 15 && !emailSent) {
    sendEmailNotification();
    emailSent = true;
  }
  if (alcoholLevel > 20) {
    emailSent = false;
  }

  // Vibration detection logic (LOW = vibration detected)
  int vibrationState = digitalRead(VIBRATION_SENSOR_PIN);

  if (vibrationState == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
    clearAlarm();       // Clear message when buzzer ON (vibration detected)
    Serial.println("Vibration detected! Buzzer ON");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    showAlarm();        // Show message when buzzer OFF (at rest)
  }

  delay(100);
}

void onAlcoholLevelChange() {
  Serial.print("Alcohol Level Changed to: ");
  Serial.println(alcoholLevel);
}

void onObjectDetectedChange() {
  Serial.println("IR object detection state changed.");
}

void onUsageDataChange() {
  Serial.print("Usage Count Changed to: ");
  Serial.println(usageData);
}
