#pragma once

#include <limits>
#include <cmath>

static const float PI = M_PI;
static const float TWO_PI = M_PI * 2.0;
static const float HALF_PI = M_PI * 0.5;

static const float D2R = M_PI / 180.0;
static const float R2D = 180.0 / M_PI;

static inline float bound(float value, float range)
{
    float bound = fmod(value, range);
    return (bound < 0) ? (bound + range) : bound;
}

static inline int bound(int value, int range)
{
    int bound = value % range;
    return (bound < 0) ? (bound + range) : bound;
}

static inline float constrain(float value, float min, float max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

static inline int constrain(int value, int min, int max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

static inline float ease(float t)
{
    return (t * t * (3 - 2 * t));
}

static inline float easeIn(float t)
{
    return (t < 0.5f) ? ease(t) : t;
}

static inline float easeOut(float t)
{
    return (t > 0.5f) ? ease(t) : t;
}

static inline float FastSqrt(float x)
{
    int i = *(int*)&x; // store floating-point bits in integer
    i = 0x5f3759d5 - (i >> 1); // initial guess for Newton's method
    float r = *(float*)&i; // convert new bits into float
    r *= (1.5f - 0.5f * x * r * r); // One round of Newton's method
    return r * x;
}
