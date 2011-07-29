#ifndef _MOVE_H_
#define _MOVE_H_

namespace Move {
    enum Type {
      NONE = 0,
      FORWARD = 1,
      BACKWARD = 1 << 1,
      TURN_CW = 1 << 2,
      TURN_CCW = 1 << 3,
      LEFT = 1 << 4,
      RIGHT = 1 << 5,
      UP = 1 << 6,
      DOWN = 1 << 7,
    };
}

#endif /* _MOVE_H_ */
