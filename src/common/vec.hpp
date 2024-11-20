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