#ifndef _TECHTREE_H_
#define _TECHTREE_H_

#include <string>
#include "JSON/JSON.h"
#include "imageManager.h"
#include "unit.h"
#include "building.h"

class TechTree {
  public:
    static TechTree *fromFile(std::string filename, ImageManager *imgMgr);
    static TechTree *fromJSONObject(const JSONObject &tree, ImageManager *imgMgr);
    ~TechTree();

    const Entity *getEntity(std::string name);
    Entity *createEntity(std::string name);
  private:
    typedef std::map<std::string, const Unit*> UnitMap;
    typedef std::map<std::string, const Building*> BuildingMap;

    UnitMap units;
    BuildingMap buildings;

    TechTree();

    static std::string wstrToStr(const std::wstring &wstr);
};

#endif /* _TECHTREE_H_ */
