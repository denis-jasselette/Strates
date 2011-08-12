#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <sstream>
#include <string>

#define DEBUG 1
#if !(defined DEBUG && DEBUG)
#define NDEBUG
#endif
#include <cassert>

#define FRAMERATE_LIMIT 60
#define CACHE_RENDER 0

std::string res_path(std::string basename);

void log(const std::stringstream&);
void log(const std::string);

#endif /* _CONFIG_H_ */
