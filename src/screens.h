#ifndef _SCREENS_H_
#define _SCREENS_H_

#include "screen.h"

enum {
  SCREEN_THIS = -2,
  SCREEN_EXIT = -1,
  SCREEN_GAME,
  SCREEN_MENU,
};

#include "gameScreen.h"
#include "menuScreen.h"

#endif /* _SCREENS_H_ */
