PertinaxHeart — MaChérie Hub (Smart Desktop Hub)

Short description
PertinaxHeart (working name: MaChérie Hub) is a small, Wi‑Fi connected desktop device built around an ESP32‑S3 and a 240×240 ST7789 display. It uses LVGL for a modular UI, FreeRTOS for concurrency, and Firebase for simple remote interactions (e.g., a "thinking of you" LED or message).

Hardware (summary)
- MCU: ESP32‑S3
- Display: ST7789 240×240 SPI
- Input: Rotary encoder (rotate = scroll/select, click = enter)
- Sensors: DHT22 (temp/humidity), distance sensor (ToF or ultrasonic)

Key features
- Modular LVGL apps: Milestone counter, 13×13 Go, Distance Ruler, Music recommendations
- Background sensor polling via FreeRTOS tasks with responsive encoder handling
- Wi‑Fi auto‑connect + Firebase integration (realtime triggers)
- OTA updates for painless field upgrades

Quickstart (PlatformIO)
1. Install PlatformIO in VS Code.
2. Open this project folder.
3. Update `platformio.ini` to match your ESP32‑S3 board and add required `lib_deps` (LVGL, TFT driver, Firebase libs).
4. Build and upload:

```powershell
pio run -e <your_env> -t upload
```

Notes on credentials
- Put Wi‑Fi and Firebase credentials in `src/config/settings.h` or a separate `src/config/credentials.h` (ignored by git). Never commit credentials to the repo.

Repository layout (high level)
- `src/` — application code (apps/, drivers/, tasks/, ui/, config/)
- `include/` — shared public headers
- `lib/` — third‑party or reusable local libraries
- `docs/` — wiring, structure, TODOs
- `src/assets/` — fonts and images for LVGL (keep optimized)

Development tips
- Reuse your working display, Wi‑Fi, Firebase and OTA code by copying small, well‑isolated modules into `lib/` or `src/config/`.
- Prioritize encoder responsiveness: run encoder handling at high FreeRTOS priority and keep the ISR short.
- Reduce LVGL RAM by subsetting fonts and loading large images from SPIFFS / LittleFS when needed.

Tasks & Roadmap
- See `docs/TODO.md` for the current prioritized task list and milestone plan.

Contact
If you want me to customise this README further (add wiring images, schematic, or exact `platformio.ini` entries), tell me which section to expand.

Project name note
The repository is currently `PertinaxHeart` on GitHub; the device callsign is `MaChérie Hub` (feel free to rename in docs if you prefer another option).