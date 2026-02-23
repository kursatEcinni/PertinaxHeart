Project Structure (DeskHub)

- src/
  - apps/            App modules (milestone, ruler, go, music)
  - ui/              LVGL UI manager, themes, common widgets
  - drivers/         Sensor + peripheral drivers (DHT22, distance, encoder)
  - tasks/           FreeRTOS task entry points (sensor polling, wifi, ui)
  - config/          Global config and pin mappings
  - assets/          Fonts and images for LVGL (optimize sizes)

- include/           Public headers for libraries
- lib/               Local libraries (third-party or homegrown)
- docs/              Design notes, wiring, PCB photos

Notes
- Keep LVGL assets in `assets/` and load them on demand to save RAM.
- Use FreeRTOS task priorities: encoder (highest), ui, sensors, wifi.