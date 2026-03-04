#include <time.h>
#include "network_portal.h"
#include "../ui/ui_manager.h" // To call show_wifi_popup

WiFiManager wm;

// Configure for Turkey (UTC+3)
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 10800; // 3 hours * 3600
const int   daylightOffset_sec = 0; 

void wifi_init() {
    bool res = wm.autoConnect("PertinaxHeart");
    
    if (res) {
        show_wifi_popup(true);
        // Start background NTP synchronization
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        Serial.println("NTP Sync Initialized");
    } else {
        ESP.restart();
    }
}

// Formats time as "HH:MM" to match your UI layout
String get_clock_string() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        return "--:--";
    }
    char buf[6]; 
    strftime(buf, sizeof(buf), "%H:%M", &timeinfo);
    return String(buf);
}

String get_date_string() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        return "00/00/0000";
    }
    char buf[11]; // "MM/DD/YYYY\0"
    strftime(buf, sizeof(buf), "%m/%d/%Y", &timeinfo);
    return String(buf);
}