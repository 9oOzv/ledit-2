#pragma once

#define MAX_UNSIGNED_LONG 4294967295

template<typename T> inline void fill(T *arr, T val, int n) {
    for(int i = 0; i < n; i++) {
        arr[i] = val;
    }
}

template<typename T, uint16_t N> inline uint16_t arrsize(T (&arr)[N]) {
    return N;
}

template<typename T, uint16_t N> inline String join(
    T (&arr)[N],
    String sep,
    int base = DEC
) {
    if(N == 0) return "";
    String s(arr[0]);
    for(int i = 1; i < N; i++) {
        s += sep + String(arr[i], base);
    }
    return s;
}

uint32_t hsv_to_rgb(uint16_t hue, uint8_t sat, uint8_t val) {
    uint32_t r, g, b;
    uint8_t region, remainder, p, q, t;

    if (sat == 0) {
        r = g = b = val;
        return (r << 16) | (g << 8) | b;
    }

    region = hue / 43;
    remainder = (hue - (region * 43)) * 6;

    p = (val * (255 - sat)) >> 8;
    q = (val * (255 - ((sat * remainder) >> 8))) >> 8;
    t = (val * (255 - ((sat * (255 - remainder)) >> 8))) >> 8;

    switch(region) {
        case 0: r = val; g = t; b = p; break;
        case 1: r = q; g = val; b = p; break;
        case 2: r = p; g = val; b = t; break;
        case 3: r = p; g = q; b = val; break;
        case 4: r = t; g = p; b = val; break;
        default: r = val; g = p; b = q; break;
    }
    return (r << 16) | (g << 8) | b;
}

