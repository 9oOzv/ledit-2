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
