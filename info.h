#pragma once
#include "serial.h"
#include "screen.h"

#ifdef SERIAL_INFO
#   if SERIAL_MAX_LINES > OLED_MAX_LINES
#       define INFO_MAX_LINES SERIAL_MAX_LINES
#   else
#       define INFO_MAX_LINES OLED_MAX_LINES
#   endif
#else
#   define INFO_MAX_LINES OLED_MAX_LINES
#endif

#define INFO_MAX_MESSAGES 16
#define INFO_MAX_DEBUGS 16
#define INFO_MESSAGE_INTERVAL_MS 2000
#define INFO_MESSAGE_DURATION_MS 30000
#define INFO_DEBUG_INTERVAL_MS 2000
#define INFO_DEBUG_DURATION_MS 30000
#define INFO_MESSAGE_LINE 4
#define INFO_WARN_LINE 6
#define INFO_DEBUG_LINE 5
#define INFO_STATUS_LINE 3

namespace info {


inline void loop();

struct Message {
    String text;
    unsigned long t_created = millis();
    unsigned long duration_ms = INFO_MESSAGE_DURATION_MS;
};

Message messages[INFO_MAX_MESSAGES];
Message debugs[INFO_MAX_DEBUGS];
uint8_t i_current_message = 0;
uint8_t i_current_debug = 0;
unsigned long t_message_changed = 0;
unsigned long t_debug_changed = 0;

inline void setup() {
    serial::setup();
    screen::setup();
}

template<typename T> inline void line(T text, uint8_t lineno = 0) {
    screen::set_line(text, lineno);
    serial::set_line(text, lineno);
}

template<typename T> inline void lines(T lines[], int n) {
    screen::set_lines(lines, n);
    serial::set_lines(lines, n);
}

template<typename T> inline void warning(T text) {
    line(text, INFO_WARN_LINE);
}

template<typename T> inline void status(T text, bool now = false) {
    line(text, INFO_STATUS_LINE);
    if(now) loop();
}

template<typename T, uint16_t N>
inline void message(
    T text,
    Message (&messages)[N],
    unsigned long duration_ms 
) {
    for(int i = 0; i < N; i++) {
        Message &m = messages[i];
        if(m.text.length() == 0) {
            m.text = String(text);
            m.t_created = millis();
            m.duration_ms = duration_ms;
            return;
        }
    }
    warning("no free message slots");
}

void message(
    String text,
    unsigned long duration_ms = INFO_MESSAGE_DURATION_MS
) {
    message(text, messages, INFO_MESSAGE_DURATION_MS);
}

#ifdef DEBUG
    template<typename T>
    void debug(T text) { message(text, debugs, INFO_DEBUG_DURATION_MS); }
#else
    template<typename T> inline void debug(T text) {}
#endif

template<uint16_t N>
inline void delete_old_messages(Message (&messages)[N]) {
    for(int i = 0; i < N; i++) {
        Message &m = messages[i];
        if(m.t_created == 0)
            continue;
        if(millis() - m.t_created > m.duration_ms) {
            m.text = "";
            m.t_created = 0;
        }
    }
}

template<uint16_t N>
inline void loop_messages(
    Message (&messages)[N],
    uint8_t &i_current,
    unsigned long &t_changed,
    uint8_t lineno,
    unsigned long interval_ms 
) {
    delete_old_messages(messages);
    if(millis() - t_changed < interval_ms)
        return;
    for(uint8_t i = 0; i < N; i++) {
        uint8_t j = (i_current + i + 1) % (N);
        if(messages[j].text.length() > 0) {
            line(messages[j].text, lineno);
            i_current = j;
            t_changed = millis();
            return;
        }
    }
}

inline void loop_messages() {
    loop_messages(
        messages,
        i_current_message,
        t_message_changed,
        INFO_MESSAGE_LINE,
        INFO_MESSAGE_INTERVAL_MS
    );
}

inline void loop_debugs() {
    loop_messages(
        debugs,
        i_current_debug,
        t_debug_changed,
        INFO_DEBUG_LINE,
        INFO_DEBUG_INTERVAL_MS
    );
}

inline void loop() {
    loop_messages();
    loop_debugs();
    screen::loop();
    serial::loop();
}


}
