DeskHub prioritized TODOs

High priority (needed for prototype delivery)
- [x] Integrate working display/LVGL driver into `UI::init` and verify framebuffer + lv_timer running
- [x] Implement encoder driver: ISR, debouncing, rotary->navigation mapping (rotate=scroll/select, click=enter)
- [x] Add Wi‑Fi auto‑connect module (import working code and config)
- [-] Add OTA update flow (reuse prior implementation, verify full update cycle)

Core functionality
- [ ] Implement DHT22 driver and validate temperature/humidity readings
- [ ] Implement distance sensor driver (ToF/ultrasonic) and calibration routine
- [ ] Wire `sensor_task` to a shared data store and publish/cache readings
- [ ] Integrate Firebase: auth, realtime listeners, and a simple RPC/event (e.g., trigger LED)

Apps (UI + logic)
- [ ] Implement 13x13 Go core logic (rules, captures, scoring)
- [ ] Build Go UI: board rendering, cursor, move input via encoder
- [ ] Implement Ruler app: UI + distance→cm mapping with smoothing/filtering
- [ ] Implement Milestone app: persistent counter, increment presets, nice UI
- [ ] Implement Music app: Firebase‑synced recommendations display

Platform & optimization
- [ ] Update `platformio.ini` with `lib_deps` and build flags (LVGL, Firebase, OTA libraries)
- [ ] Optimize LVGL assets: subset fonts, compress images, lazy/streamed loading to save RAM
- [ ] Memory profiling and heap optimization for ESP32‑S3 (track worst-case LVGL usage)

Testing & validation
- [ ] Create automated/manual tests: display, encoder responsiveness, sensors, Wi‑Fi reconnection, Firebase events, OTA
- [ ] Verify encoder responsiveness under load (high-priority FreeRTOS task for encoder)

Hardware & enclosure
- [ ] Hardware check: wiring review, decoupling caps, power budget, PCB photos
- [ ] Enclosure: 3D print fit, plexiglass front, assembly & photos

Release
- [ ] Final acceptance checklist and release build for delivery

Notes
- Reuse display, Wi‑Fi, Firebase and OTA code from your prior projects where possible—keep copies in `lib/` or `src/config` with clear attribution.
- Prioritize encoder + LVGL responsiveness before polishing animations.
