#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <sstream>
#include <string>

#define DEBUG 1

#define FRAMERATE_LIMIT 60
#define CACHE_RENDER false

std::string res_path(std::string basename);

void log(const std::stringstream&);
void log(const std::string);

#endif /* _CONFIG_H_ */
