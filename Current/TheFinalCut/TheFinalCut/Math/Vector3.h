#ifndef __VECTOR3__H__
#define __VECTOR3__H__

namespace TFC
{
    namespace Math
    {
        template<typename T> class Vector3
        {
        public:
            Vector3();
            Vector3(const Vector3<T>& other);
            Vector3(T x);
            Vector3(T x, T y, T z);

            ~Vector3();

            Vector3<T>& operator=(const Vector3<T>& other);
            Vector3<T>& operator+=(const Vector3<T>& other);

            Vector3<T> operator+(const Vector3<T>& other);
            Vector3<T> operator-(const Vector3<T>& other);
            Vector3<T> operator*(const Vector3<T>& other);
            Vector3<T> operator*(T x);

            bool operator==(const Vector3& other);
            bool operator!=(const Vector3<T>& other);

            T x;
            T y;
            T z;
        };
    }
}
#endif  // __VECTOR3__H__
