#pragma once

//// One lone coder Vector2
// clang-format off
#include <cstddef>
#include <cstdint>

template <class T>
struct v2d_generic
{
    T x = 0;
    T y = 0;

    inline v2d_generic() : x(0), y(0)                        {                                                      }
    inline v2d_generic(T _x, T _y) : x(_x), y(_y)            {                                                      }
    inline v2d_generic(const v2d_generic& v) : x(v.x), y(v.y){                                                      }
    inline T mag()                                           { return sqrt(x * x + y * y);                          }
    inline T mag2()					                         { return x * x + y * y; }
    inline v2d_generic  norm()                               { T r = 1 / mag(); return v2d_generic(x*r, y*r);       }
    inline v2d_generic  perp()                               { return v2d_generic(-y, x);                           }
    inline T dot(const v2d_generic& rhs)                     { return this->x * rhs.x + this->y * rhs.y;            }
    inline T cross(const v2d_generic& rhs)                   { return this->x * rhs.y - this->y * rhs.x;            }
    inline v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y);}
    inline v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y);}
    inline v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs);    }
    inline v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs);    }
    inline v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this;    }
    inline v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this;    }
    inline v2d_generic& operator *= (const T& rhs)           { this->x *= rhs; this->y *= rhs; return *this;        }
    inline v2d_generic& operator /= (const T& rhs)           { this->x /= rhs; this->y /= rhs; return *this;        }
    inline T& operator [] (std::size_t i)                    { return *((T*)this + i);	   /* <-- D'oh :( */        }
    inline operator v2d_generic<int>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
    inline operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
};

template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs) { return v2d_generic<T>(lhs * rhs.x, lhs * rhs.y); }
template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs){ return v2d_generic<T>(lhs * rhs.x, lhs * rhs.y); }
template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)   { return v2d_generic<T>(lhs * rhs.x, lhs * rhs.y); }
template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs) { return v2d_generic<T>(lhs / rhs.x, lhs / rhs.y); }
template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs){ return v2d_generic<T>(lhs / rhs.x, lhs / rhs.y); }
template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)   { return v2d_generic<T>(lhs / rhs.x, lhs / rhs.y); }

typedef v2d_generic<int> iVector2;
typedef v2d_generic<float> fVector2;
typedef v2d_generic<double> dVector2;
//typedef iVector2 Point;
// clang-format on
