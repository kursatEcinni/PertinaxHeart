Here is a professional and structured README.md file designed to give Claude Code (and any human contributors) a clear roadmap of the Pertinax Heart project.
Pertinax Heart 🤎

An Industrial-Naked IoT Smart Hub & Sentimental Gift

Pertinax Heart is a custom-engineered desktop companion built on the ESP32-S3. It merges a raw, "naked" hardware aesthetic—featuring an exposed pertinax circuit board behind transparent plexiglass—with a modern, modular software ecosystem.
🚀 Overview

The project serves as a "Smart Hub" for a partner, featuring remote interaction via Firebase and a suite of "Apps" driven by the LVGL graphics library and FreeRTOS.
Key Features

    "Thinking of You" LED: A remote-triggered indicator synced via Firebase.

    Modular App Suite: * 13x13 Go Game: A fully playable logic-based board game.

        Digital Ruler: Real-time distance measurements using ultrasonic/laser sensors.

        Milestone Counter: Tracks and displays significant relationship dates.

        Music Recommender: A dedicated UI for sharing track suggestions.

    Environmental Monitoring: Real-time temperature and humidity tracking via DHT22.

    Industrial Design: 3D-printed enclosure with a visible, hand-soldered pertinax core.

🛠 Tech Stack

    Microcontroller: ESP32-S3.

    Display: 1.3" ST7789 TFT LCD (240x240).

    Input: Rotary Encoder for menu navigation.

    Sensors: DHT22 (Temp/Humid) and VL53L0X/HC-SR04 (Distance).

    Software: PlatformIO, C++, FreeRTOS, LVGL, and Firebase.

📂 Project Structure

The repository follows a strict separation of concerns to ensure scalability:
📝 Roadmap & Progress can accesible from TODO.md on docs file


🔧 Installation & Setup

    Clone the Repo: git clone <repo-url>

    Environment: Open the project in VS Code with the PlatformIO extension.

    Config: Update src/config/settings.h with your Wi-Fi and Firebase credentials.

    Build: Run pio run -t upload to flash the ESP32-S3.