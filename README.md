# M5-guruguru
M5StopWatch Interactive Character Follower

A cute animated character that follows your finger (touch) on the M5Stack StopWatch's round AMOLED display.
- 9-direction head tracking

Inspired by @rotejin's tomari-guruguru project.

## How to Use

### Preparing Character Images
Image preparation: Please refer to @rotejin's [tomari-guruguru](https://github.com/rotejin/tomari-guruguru) repository for how to create the sprite sheets.

1. Create a sprite sheet.
2. Open the included tool: `tools/sprite-splitter.html` in your browser.
3. Upload your sprite sheet and adjust the grid settings.
4. Click **Split Sprites** to generate individual images.
5. Download the sliced images and rename them as `dir0.png` to `dir8.png`.
6. Open `src/main.cpp` and update the image size constants to match your images:
   ```cpp
   const int WIDTH = 251;   // Image width in pixels
   const int HEIGHT = 240;  // Image height in pixels
   ```

*Image mapping:*
- `dir0`: Top-Left
- `dir1`: Top
- `dir2`: Top-Right
- `dir3`: Left
- `dir4`: Center (Front) ← Default
- `dir5`: Right
- `dir6`: Bottom-Left
- `dir7`: Bottom
- `dir8`: Bottom-Right

### Flashing to Device
1. Place your character images (`dir0.png` to `dir8.png`) in the `data/` folder of the project.
2. Upload the firmware **and** the LittleFS filesystem (images) to your M5StopWatch.  
   (In PlatformIO: `Upload` and then `Upload Filesystem Image`)
3. Power on the device and touch the screen — the character will follow your finger!

## Hardware Required

- [M5Stack StopWatch](https://shop.m5stack.com/products/m5stack-stopwatch-dev-kit-esp32-s3) (ESP32-S3 + 1.75" round AMOLED touch)
- USB-C cable for power/upload

## Demo Video

https://x.com/nananauno/status/2067257510378274823

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

Character assets (images) follow their own license. Please respect the original creators.

## Acknowledgments

- Huge thanks to [@rotejin](https://github.com/rotejin) for the wonderful `tomari-guruguru` idea and open resources!
- M5Stack team for the amazing StopWatch hardware.