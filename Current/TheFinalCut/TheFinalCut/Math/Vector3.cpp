#include "Vector3.h"

template<typename T>
TFC::Math::Vector3<T>::Vector3()
{
}

template<typename T>
TFC::Math::Vector3<T>::Vector3(const Vector3<T>& other)
{
    this = other;
}

template<typename T>
TFC::Math::Vector3<T>::Vector3(T x)
{
    this.x = this.y = this.z = x;
}

template<typename T>
TFC::Math::Vector3<T>::Vector3(T x, T y, T z)
{
    this.x = x;
    this.y = y;
    this.z = z;
}

template<typename T>
TFC::Math::Vector3<T>::~Vector3()
{
}

template<typename T>
TFC::Math::Vector3<T>& TFC::Math::Vector3<T>::operator=(const Vector3<T>& other)
{
    this.x = other.x;
    this.y = other.y;
    this.z = other.z;
    return *this;
}

template<typename T>
TFC::Math::Vector3<T>& TFC::Math::Vector3<T>::operator+=(const Vector3<T>& other)
{
    /*Vector3<T> v = *this;
    *this = v + other;*/
    return *this;
}

template<typename T>
TFC::Math::Vector3<T> TFC::Math::Vector3<T>::operator+(const Vector3<T>& other)
{
    return Vector3<T>(this.x + other.x, this.y + other.y, this.z + other.z);
}

template<typename T>
TFC::Math::Vector3<T> TFC::Math::Vector3<T>::operator-(const Vector3<T>& other)
{
    return Vector3<T>(this.x - other.x, this.y - other.y, this.z - other.z);
}

template<typename T>
TFC::Math::Vector3<T> TFC::Math::Vector3<T>::operator*(const Vector3<T>& other)
{
    return Vector3<T>(this.x * other.x, this.y * other.y, this.z * other.z);
}

template<typename T>
TFC::Math::Vector3<T> TFC::Math::Vector3<T>::operator*(T x)
{
    return Vector3<T>(this.x * x, this.y * x, this.z * x);
}

template<typename T>
bool TFC::Math::Vector3<T>::operator==(const Vector3 & other)
{
    return (this.x == other.x && this.y == other.y && this.z == other.z);
}

template<typename T>
bool TFC::Math::Vector3<T>::operator!=(const Vector3<T>& other)
{
    return !(operator==(other));
}
