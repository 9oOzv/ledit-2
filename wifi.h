#pragma once
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "info.h"
#include "common.h"

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
    info::status("configuring wifi", true);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    info::debug(
        "ssid: "
        + String(WIFI_SSID)
        + " password: "
        + String(WIFI_PASSWORD)
    );
    for(uint8_t i = 0; i < WIFI_CONNECT_NUM_CHECKS; i++) {
        info::status(
            (
                String("connecting wifi ")
                + String(i)
                + String("/")
                + String(WIFI_CONNECT_NUM_CHECKS)
            ),
            true
        );
        if(WiFi.status() == WL_CONNECTED) break;
        delay(WIFI_CONNECT_CHECK_INTERVAL_MS);
    }
    if(WiFi.status() != WL_CONNECTED) {
        info::status("wifi connection failed", true);
        return;
    }
    info::status("wifi connected", true);
    udp.begin(WIFI_UDP_PORT);
    info::message(
        (
            String("listening: ")
            + WiFi.localIP().toString()
            + String(":")
            + WIFI_UDP_PORT
        ),
        MAX_UNSIGNED_LONG
    );
}

template<int N>
void read_package(char (&packet)[N]) {
    int packetSize = udp.parsePacket();
    if(packetSize) {
        udp.read(packet, max(N, packetSize));
        udp.flush();
        info::debug(String("received packet: ") + packet);
        return;
    }
    packet[0] = '\0';
}


}  // namespace wifi
