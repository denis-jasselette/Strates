#include <sys/stat.h>
#include <iostream>
#include "config.h"

/* FIXME: dirty hack to find the resource directory */
static std::string resDir;
static bool set = false;

std::string res_path(std::string basename) {
  if (!set) {
    std::string dirs[] = { "res", "../res" };
    for (size_t i = 0; i < sizeof(dirs); i++) {
      struct stat st;
      if (stat(dirs[i].c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        resDir = dirs[i];
        set = true;
        break;
      }
    }

    if (!set) {
      log("Error: could not find the resource directory");
      set = true;
      return "";
    }
  }

  return resDir + "/" + basename;
}

void log(const std::stringstream &msg) {
  log(msg.str());
}

void log(const std::string msg) {
  std::cout << msg << std::endl;
}
