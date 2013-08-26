#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

/**
 * Enables some special behaviors used to ease debugging.
 *
 * 0 = disabled, anything else = enabled.
 */
#define DEBUG 1
#if !(defined DEBUG && DEBUG)
#define NDEBUG
#endif
#include <cassert>

/**
 * Sets the maximum framerate at which the Application should run.
 *
 * This is expressed as a number of frames per second.
 */
#define FRAMERATE_LIMIT 60

/**
 * Authorizes the cache of some renderings.
 *
 * The cache uses RenderTexture, which seems to be unstable at the moment.
 * Disabling this, re-renders everything at each frame.
 *
 * 0 = disabled, anything else = enabled.
 */
#define CACHE_RENDER 0

/**
 * Returns the path of a file in the resource directory.
 *
 * @param basename    the name of the file
 *
 * @return            the path to the file
 */
std::string res_path(std::string basename);

extern sf::Font DEFAULT_FONT;

void log(const std::stringstream&);
void log(const std::string);

#endif /* _CONFIG_H_ */
