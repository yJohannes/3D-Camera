#pragma once
#include <cmath>

// Fast inverse square root
inline float fast_inv_sqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int*)&x;       // Interpret float bits as int
    i = 0x5f3759df - (i >> 1);       // Initial guess
    x = *(float*)&i;                 // Interpret int bits as float
    x = x * (1.5f - xhalf * x * x);  // Newton-Raphson iteration
    return x;
}
