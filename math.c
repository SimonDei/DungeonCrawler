/**
 * Created by Simon on 24.11.2020.
 */

#include "math.h"

FLOAT inclusive_random(_In_ const FLOAT min,
                       _In_ const FLOAT max) {
    return (((FLOAT) (rand()) / (FLOAT) RAND_MAX) * (max - min)) + min;
}

INT32 fast_round(_In_ const FLOAT value) {
    if (((INT32) (value * 1000) % 1000) >= 500) {
        return (INT32) (value + 1);
    }
    return (INT32) value;
}

FLOAT max_float(_In_ const FLOAT a,
                _In_ const FLOAT b) {
    if (a >= b) {
        return a;
    }
    return b;
}

FLOAT min_float(_In_ const FLOAT a,
                _In_ const FLOAT b) {
    if (a <= b) {
        return a;
    }
    return b;
}

BOOL rect_rect_collision(_In_ const FLOAT a_x,
                         _In_ const FLOAT a_y,
                         _In_ const FLOAT a_width,
                         _In_ const FLOAT a_height,
                         _In_ const FLOAT b_x,
                         _In_ const FLOAT b_y,
                         _In_ const FLOAT b_width,
                         _In_ const FLOAT b_height) {
    if (a_x + a_width >= b_x &&
        a_x <= b_x + b_width &&
        a_y + a_height >= b_y &&
        a_y <= b_y + b_height) {
        return TRUE;
    }
    return FALSE;
}

BOOL point_rect_collision(_In_ const FLOAT a_x,
                          _In_ const FLOAT a_y,
                          _In_ const FLOAT b_x,
                          _In_ const FLOAT b_y,
                          _In_ const FLOAT b_width,
                          _In_ const FLOAT b_height) {
    if (a_x >= b_x &&
        a_x <= b_x + b_width &&
        a_y >= b_y &&
        a_y <= b_y + b_height) {
        return TRUE;
    }
    return FALSE;
}
