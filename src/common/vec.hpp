#pragma once
#include <iostream>

#include "SFML/System/Vector2.hpp"
#include "../common/math.hpp"

template <typename T>
using Vec2  = sf::Vector2<T>;
using Vec2f = sf::Vector2f;
using Vec2i = sf::Vector2i;
using Vec2u = sf::Vector2u;

template <typename To, typename From>
inline Vec2<To> vec_cast(const Vec2<From>& vec)
{
	return Vec2<To>(static_cast<To>(vec.x), static_cast<To>(vec.y));
}

// Overloading the << operator for easy printing
template <typename T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vec)
{
	os << "{" << vec.x << ", " << vec.y << "}";
	return os;
}

template <typename T>
void print_vec(const T& vec)
{
	std::cout << "{ " << vec.x << ", " << vec.y << " }" << '\n';
}

template <typename T>
void print_std_vec(const T& vec)
{
	std::cout << "\n<";
	for (const auto& val : vec)
	{
		std::cout << val << ",";
	}
	std::cout << ">\n";
}

/// Math //////////////////////////////

template <typename T>
inline sf::Vector2<T> operator*(const sf::Vector2<T>& vec, const sf::Vector2<T>& vec2)
{ return { vec.x * vec2.x, vec.y * vec2.y}; }

template <typename T>
inline sf::Vector2<T> operator/(const sf::Vector2<T>& vec, const sf::Vector2<T>& vec2)
{ return { vec.x / vec2.x, vec.y / vec2.y}; }

template <typename T>
inline sf::Vector2<T> operator+(const sf::Vector2<T>& vec, T value)
{ return { vec.x + value, vec.y + value }; }

template <typename T>
inline sf::Vector2<T> operator-(const sf::Vector2<T>& vec, T value)
{ return { vec.x - value, vec.y - value }; }


inline float norm(const Vec2f& v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

inline float fast_norm(const Vec2f& v)
{
	float l2 = v.x * v.x + v.y * v.y;
	return l2 * fast_inv_sqrt(l2);
}

template <typename T>
inline float dot_p(const T& u, const T& v)
{
	return u.x * v.x + u.y * v.y;
}

inline Vec2f to_Vec2f(const Vec2i& vec)
{ return { static_cast<float>(vec.x), static_cast<float>(vec.y) }; }

inline Vec2f to_Vec2f(const Vec2u& vec)
{ return { static_cast<float>(vec.x), static_cast<float>(vec.y) }; }

inline Vec2i
to_Vec2i(const Vec2f& vec)
{ return { static_cast<int>(vec.x), static_cast<int>(vec.y) }; }


// Type alias for convenience
template <typename T>
using Vec3 = sf::Vector3<T>;
using Vec3f = sf::Vector3f;
using Vec3i = sf::Vector3i;

// Conversion between types
template <typename To, typename From>
inline Vec3<To> vec_cast(const Vec3<From>& vec)
{
    return Vec3<To>(static_cast<To>(vec.x), static_cast<To>(vec.y), static_cast<To>(vec.z));
}

// Overloading the << operator for easy printing
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec)
{
    os << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
    return os;
}

template <typename T>
void print_vec(const Vec3<T>& vec)
{
    std::cout << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }" << '\n';
}

template <typename T>
void print_std_vec(const Vec3<T>& vec)
{
    std::cout << "\n<";
    for (const auto& val : vec)
    {
        std::cout << val << ",";
    }
    std::cout << ">\n";
}

/// Math //////////////////////////////

template <typename T>
inline sf::Vector3<T> operator*(const sf::Vector3<T>& vec, const sf::Vector3<T>& vec2)
{
    return { vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z};
}

template <typename T>
inline sf::Vector3<T> operator/(const sf::Vector3<T>& vec, const sf::Vector3<T>& vec2)
{
    return { vec.x / vec2.x, vec.y / vec2.y, vec.z / vec2.z};
}

template <typename T>
inline sf::Vector3<T> operator+(const sf::Vector3<T>& vec, T value)
{
    return { vec.x + value, vec.y + value, vec.z + value };
}

template <typename T>
inline sf::Vector3<T> operator-(const sf::Vector3<T>& vec, T value)
{
    return { vec.x - value, vec.y - value, vec.z - value };
}

inline float norm(const Vec3f& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float fast_norm(const Vec3f& v)
{
    float l2 = v.x * v.x + v.y * v.y + v.z * v.z;
    return l2 * fast_inv_sqrt(l2);
}

template <typename T>
inline float dot_p(const Vec3<T>& u, const Vec3<T>& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}