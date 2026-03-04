#ifndef NETWORK_PORTAL_H
#define NETWORK_PORTAL_H

#include <WifiManager.h>


void wifi_init();

//String wifi_get_status();

void show_wifi_popup(bool success);

String get_clock_string();
String get_date_string();

#endif // WIFI_MANAGER_H