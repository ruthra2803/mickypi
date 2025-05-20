#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo left_right;
Servo up_down;

int servoX = 90;
int servoY = 90;

unsigned long previousMillis = 0;
const long blinkInterval = 4000;  // Blink every 4 seconds
bool isBlinking = false;
int blinkFrame = 0;

void drawBigEyes() {
  display.fillCircle(38, 32, 20, SSD1306_WHITE);
  display.fillCircle(38, 32, 18, SSD1306_BLACK);
  display.drawCircle(38, 32, 20, SSD1306_WHITE);

  display.fillCircle(90, 32, 20, SSD1306_WHITE);
  display.fillCircle(90, 32, 18, SSD1306_BLACK);
  display.drawCircle(90, 32, 20, SSD1306_WHITE);
}

void drawPupils(int xOffset, int yOffset) {
  int pxLeft = constrain(38 + xOffset, 30, 46);
  int pyLeft = constrain(32 + yOffset, 24, 40);
  display.fillCircle(pxLeft, pyLeft, 6, SSD1306_WHITE);
  display.fillCircle(pxLeft, pyLeft, 3, SSD1306_BLACK);

  int pxRight = constrain(90 + xOffset, 82, 98);
  int pyRight = constrain(32 + yOffset, 24, 40);
  display.fillCircle(pxRight, pyRight, 6, SSD1306_WHITE);
  display.fillCircle(pxRight, pyRight, 3, SSD1306_BLACK);
}

void drawSmile() {
  for (int i = 0; i <= 8; i++) {
    int x = 48 + i * 2;  // Moved 4 pixels left to center
    int y = 50 + (int)(2 * sin(PI * i / 8));
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}

void drawBlink() {
  display.fillRect(18, 24, 40, 18, SSD1306_WHITE);  // left eye
  display.fillRect(70, 24, 40, 18, SSD1306_WHITE);  // right eye
}

void drawEyeDropScatter(int frame) {
  // Draw small drops going outward during blink
  if (frame == 1) {
    display.fillCircle(15, 20, 1, SSD1306_WHITE);
    display.fillCircle(110, 20, 1, SSD1306_WHITE);
  } else if (frame == 2) {
    display.fillCircle(10, 15, 1, SSD1306_WHITE);
    display.fillCircle(115, 15, 1, SSD1306_WHITE);
  } else if (frame == 3) {
    display.fillCircle(7, 10, 1, SSD1306_WHITE);
    display.fillCircle(120, 10, 1, SSD1306_WHITE);
  }
}

void drawCuteFace(int pupilXOffset, int pupilYOffset, bool blink, int frame = 0) {
  display.clearDisplay();

  if (blink) {
    drawBlink();
    drawEyeDropScatter(frame);
  } else {
    drawBigEyes();
    drawPupils(pupilXOffset, pupilYOffset);
    drawSmile();
  }

  display.display();
}

void setup() {
  left_right.attach(2);
  up_down.attach(3);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);  // Don't continue if OLED fails
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  if (Serial.available()) {
    String inputString = Serial.readStringUntil('\r');
    int commaIndex = inputString.indexOf(',');
    if (commaIndex == -1) return;

    int x = inputString.substring(0, commaIndex).toInt();
    int y = inputString.substring(commaIndex + 1).toInt();

    servoX = map(x, 0, 1920, 0, 180);
    servoY = map(y, 0, 1080, 180, 0);

    left_right.write(servoX);
    up_down.write(servoY);
  }

  int pupilXOffset = map(servoX, 0, 180, -4, 4);
  int pupilYOffset = map(servoY, 0, 180, -4, 4);

  unsigned long currentMillis = millis();

  if (!isBlinking && currentMillis - previousMillis >= blinkInterval) {
    isBlinking = true;
    blinkFrame = 1;
    previousMillis = currentMillis;
  }

  if (isBlinking) {
    drawCuteFace(pupilXOffset, pupilYOffset, true, blinkFrame);
    delay(80);
    blinkFrame++;
    if (blinkFrame > 3) {
      isBlinking = false;
    }
  } else {
    drawCuteFace(pupilXOffset, pupilYOffset, false);
  }
}
