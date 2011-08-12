#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_

#include "application.h"
#include "screens.h"

class MenuScreen : public Screen {
  public:
    MenuScreen(Application *app);

    ScreenID run();
  private:
};

#endif /* _MENUSCREEN_H_ */
