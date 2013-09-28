#ifndef _CLONABLE_H_
#define _CLONABLE_H_

struct Clonable {
  virtual Clonable* clone() const = 0;
};

#endif /* _CLONABLE_H_ */
