#pragma once
#include <cmath>

class Vector2 {
public:
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) {
        return Vector2(x / scalar, y / scalar);
    }

    float dot(const Vector2& other) {
        return x * other.x + y * other.y;
    }

    float length() {
        return sqrt(x * x + y * y);
    }

    Vector2 normalize() {
        float len = length();
        if (len > 0) {
            return *this / len;
        }
        return Vector2(0, 0);
    }
};