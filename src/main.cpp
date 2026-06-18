#include <LittleFS.h>
#include <M5Unified.h>

const int NUM_DIR = 9;
const int WIDTH = 251;   // Image width. Please adjust based on your image.
const int HEIGHT = 240; // Image height. Please adjust based on your image.

M5Canvas* dirCanvas[NUM_DIR];
int currentDir = 4;      // Center direction by default

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  Serial.begin(115200);
  Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());

  // Initialize LittleFS
  if (!LittleFS.begin(true)) {  // true = format if mount fails
    Serial.println("LittleFS Mount Failed");
    return;
  }
  Serial.println("LittleFS Mount Success");

  // Load 9 direction canvases & images
  for (int i = 0; i < NUM_DIR; i++) {
    dirCanvas[i] = new M5Canvas(&M5.Display);
    dirCanvas[i]->setColorDepth(16);
    dirCanvas[i]->createSprite(WIDTH, HEIGHT);

    String filename = String("/dir") + i + ".png";
    if (dirCanvas[i]->drawPngFile(LittleFS, filename.c_str())) {
      Serial.printf("Loaded: %s\n", filename.c_str());
    } else {
      Serial.printf("Failed to load: %s  (black placeholder)\n", filename.c_str());
      dirCanvas[i]->fillSprite(TFT_BLACK);
      dirCanvas[i]->setTextColor(TFT_WHITE, TFT_BLACK);
      dirCanvas[i]->drawCenterString(String("Dir ") + i, WIDTH/2, HEIGHT/2);
    }
  }

  Serial.println("Setup Complete!");
}

int getDirection(int touchX, int touchY) {
  int cx = M5.Display.width() / 2;
  int cy = M5.Display.height() / 2;
  float dx = touchX - cx;
  float dy = touchY - cy;

  if (sqrt(dx*dx + dy*dy) < 50) return 4;  // Center

  float angle = atan2(dy, dx) * 180.0 / PI;

  if (angle < -157.5 || angle > 157.5) return 3;  // Left
  else if (angle < -112.5) return 0;              // Upper Left
  else if (angle < -67.5)  return 1;              // Up
  else if (angle < -22.5)  return 2;              // Upper Right
  else if (angle < 22.5)   return 5;              // Right
  else if (angle < 67.5)   return 8;              // Lower Right
  else if (angle < 112.5)  return 7;              // Down
  else if (angle < 157.5)  return 6;              // Lower Left
  return 3;
}

void loop() {
  M5.update();

  if (M5.Touch.getCount() > 0) {
    auto p = M5.Touch.getDetail(0);
    if (p.isPressed()) {
      currentDir = getDirection(p.x, p.y);
    }
  }

  // Draw the current direction canvas with scaling to fit the display
  float zx = (float)M5.Display.width()  / WIDTH;
  float zy = (float)M5.Display.height() / HEIGHT;
  M5.Display.startWrite();
  dirCanvas[currentDir]->pushRotateZoom(
    M5.Display.width()  / 2,
    M5.Display.height() / 2,
    0.0f, zx, zy
  );
  M5.Display.endWrite();
}