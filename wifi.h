#pragma once
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "info.h"

#define WIFI_CONNECT_TIMEOUT_MS 60000
#define WIFI_CONNECT_CHECK_INTERVAL_MS 500
#define WIFI_CONNECT_NUM_CHECKS WIFI_CONNECT_TIMEOUT_MS / WIFI_CONNECT_CHECK_INTERVAL_MS
#define WIFI_UDP_PORT 4210
#ifndef WIFI_SSID
#    define WIFI_SSID "DUMMY_SSID"
#endif
#ifndef WIFI_PASSWORD
#    define WIFI_PASSWORD "DUMMY_PASSWORD"
#endif


namespace wifi {

WiFiUDP udp;

void setup() {
    info::status("configuring wifi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    info::status("connecting wifi");
    for(uint8_t i = 0; i < WIFI_CONNECT_NUM_CHECKS; i++) {
        info::status2(String(i) + " / " + WIFI_CONNECT_NUM_CHECKS);
        if(WiFi.status() == WL_CONNECTED) break;
        delay(WIFI_CONNECT_CHECK_INTERVAL_MS);
    }
    if(WiFi.status() != WL_CONNECTED) {
        info::status("wifi connection failed");
        return;
    }
    info::status("wifi connected");
    info::status2(String("ip address:") + WiFi.localIP().toString());
    info::status("listening");
    info::status2(String("port:") + WIFI_UDP_PORT);
    udp.begin(WIFI_UDP_PORT);
}

template<size_t N>
void read_package(char (&packet)[N]) {
    int packetSize = udp.parsePacket();
    if(packetSize) {
        udp.read(packet, max(N, packetSize));
        udp.flush();
        info::status(String("received packet"));
        info::status2(String(packet));
        return;
    }
    packet[0] = '\0';
}
