#ifndef __VECTOR3__H__
#define __VECTOR3__H__

#include <sstream>
#include <math.h>
#include <vector>

namespace TFC
{
    namespace Math
    {
        template<typename T> class Vector3
        {
        public:
            Vector3()
            {
            }

            Vector3(const Vector3<T>& other)
            {
                *this = other;
            }

            Vector3(T x)
            {
                this->x = this->y = this->z = x;
            }

            Vector3(T x, T y, T z)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            ~Vector3()
            {
            }

            Vector3<T>& operator=(const Vector3<T>& other)
            {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
                return *this;
            }

            Vector3<T>& operator+=(const Vector3<T>& other)
            {
                Vector3<T> v = *this;
                *this = v + other;
                return *this;
            }

            Vector3<T> operator+(const Vector3<T>& other)
            {
                return Vector3<T>(this->x + other.x, this->y + other.y, this->z + other.z);
            }

            Vector3<T> operator-(const Vector3<T>& other)
            {
                return Vector3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
            }

            Vector3<T> operator*(const Vector3<T>& other)
            {
                return Vector3<T>(this->x * other.x, this->y * other.y, this->z * other.z);
            }

            Vector3<T> operator*(T x)
            {
                return Vector3<T>(this->x * x, this->y * x, this->z * x);
            }

            bool operator==(const Vector3 & other)
            {
                return (this->x == other.x && this->y == other.y && this->z == other.z);
            }

            bool operator!=(const Vector3<T>& other)
            {
                return !(operator==(other));
            }

            float Dot(const Vector3<T>& other)
            {
                return x * other.x + y * other.y;
            }

            Vector3<T> Project(const Vector3<T>& other)
            {
                return Vector3<T>( (Dot(other) / ( (T)pow(other.x, 2) + (T)pow(other.y, 2) )) * other.x,
                                   (Dot(other) / ( (T)pow(other.x, 2) + (T)pow(other.y, 2) )) * other.y,
                                   0.0 );
            }

            std::string ToString()
            {
                std::stringstream ss;
                ss << "(" << (T)x << "," << (T)y << ")";
                return ss.str();
            }
            T x;
            T y;
            T z;
        };
    }
}
#endif  // __VECTOR3__H__
