#ifndef _UTILS_H_
#define _UTILS_H_

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

template <class T>
inline T clamp(T v, T min, T max) {
  if (v < min)
    return min;
  return (v > max)? max : v;
}

sf::IntRect viewGetRect(sf::View &view);

void viewSetRect(sf::View &view, sf::IntRect &rect);

template <class T>
inline T dot(const sf::Vector2<T> &a, const sf::Vector2<T> &b) {
  return a.x * b.x + a.y * b.y;
}

template <class T>
inline float norm(const sf::Vector2<T> &v) {
  return sqrt(dot(v, v));
}

inline bool approx(float a, float b) {
  return fabs(a - b) < 1 / 32.;
}

inline bool approx(const sf::Vector2f &a, const sf::Vector2f &b) {
  return approx(a.x, b.x) && approx(a.y, b.y);
}

template <class T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &vec) {
  out << "(" << vec.x << ", " << vec.y << ")";
  return out;
}

#endif /* _UTILS_H_ */
