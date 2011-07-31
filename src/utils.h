#ifndef _UTILS_H_
#define _UTILS_H_

#include <SFML/Graphics.hpp>
#include <algorithm>

template <class T>
T clamp(T v, T min, T max) {
  if (v < min)
    return min;
  return (v > max)? max : v;
}

sf::IntRect viewGetRect(sf::View &view);

void viewSetRect(sf::View &view, sf::IntRect &rect);

#endif /* _UTILS_H_ */
