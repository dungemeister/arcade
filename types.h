#ifndef GYBRID_TYPES_H
#define GYBRID_TYPES_H

#include "cmath"

namespace MyMath{
    const float Pi = 3.1415926535f;
    const float TwoPi = Pi * 2.0f;
    const float PiOver2 = Pi / 2.0f;
    const float Infinity = std::numeric_limits<float>::infinity();
    const float NegInfinity = -std::numeric_limits<float>::infinity();

    inline float ToRadians(float degrees)
    {
        return degrees * Pi / 180.0f;
    }

    inline float ToDegrees(float radians)
    {
        return radians * 180.0f / Pi;
    }

    inline bool NearZero(float val, float epsilon = 0.001f)
    {
        if (fabs(val) <= epsilon) return true;
        else return false;
    }

};

struct Vector2{
    Vector2(float x_, float y_): x(x_), y(y_){}

    Vector2(int x_, int y_): x(static_cast<float>(x_)), y(static_cast<float>(y_)){}

    Vector2(): Vector2(0.f, 0.f) {}

    float x, y;

    friend Vector2 operator+(const Vector2& a, const Vector2& b){
        return Vector2(a.x + b.x, a.y + b.y);
    }
    friend Vector2 operator-(const Vector2& a, const Vector2& b){
        return Vector2(a.x - b.x, a.y - b.y);
    }
    friend Vector2 operator*(const Vector2& a, const Vector2& b){
        return Vector2(a.x * b.x, a.y * b.y);
    }
    
    friend Vector2 operator*(const Vector2& a, int val){
        return a * static_cast<float>(val);
    }

    friend Vector2 operator*(const Vector2& a, float val){
        return Vector2(a.x * val, a.y * val);
    }

    friend Vector2 operator*(int val, const Vector2& a){
        return static_cast<float>(val) * a;
    }

    friend Vector2 operator*(float val, const Vector2& a){
        return Vector2(a.x * val, a.y * val);
    }

    friend Vector2 operator/(const Vector2& a, float val){
        if(MyMath::NearZero(val)) return Vector2(a.x , a.y);
        
        return Vector2(a.x / val, a.y / val);
    }
    Vector2& operator*=(float val){
        this->x *= val;
        this->y *= val;
        return *this;
    }
    Vector2& operator*=(int val){
        this->x *= static_cast<float>(val);
        this->y *= static_cast<float>(val);
        return *this;
    }

    Vector2& operator+=(const Vector2& a){
        this->x += a.x;
        this->y += a.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& a){
        this->x -= a.x;
        this->y -= a.y;
        return *this;
    }
    Vector2& operator/=(float val){
        if(MyMath::NearZero(val)) return *this;
        
        this->x /= val;
        this->y /= val;
        return *this;
    }
    bool operator==(const Vector2& a){
        return this->x == a.x && this->y == a.y;
    }
    bool operator!=(const Vector2& a){
        return !(*this == a);
    }
    
    float getLengthSquared() const { return (x*x + y*y); }
    float getLength() const { return sqrt(getLengthSquared()); }

    void normalize()
    {
        float len = getLength();
        x /= len;
        y /= len;
    }
    static Vector2 Normalize(const Vector2& vec)
    {
        Vector2 temp = vec;
        temp.normalize();
        return temp;
    }

    static float DotProduct(const Vector2& a, const Vector2& b)
    {
        return (a.x * b.x + a.y * b.y);
    }

    static float CrossProduct(const Vector2& a, const Vector2& b)
    {
        return (a.x * b.y - a.y * b.x);
    }

    //Rotate vector a to -tetha
    static float GetRotationAngleRad(const Vector2& a, const Vector2& b)
    {
        auto dot = Vector2::DotProduct(Vector2::Normalize(a), Vector2::Normalize(b));
        auto cross = Vector2::CrossProduct(Vector2::Normalize(a), Vector2::Normalize(b));
        return atan2(cross, dot);
    }
};

#endif //GYBRID_TYPES_H