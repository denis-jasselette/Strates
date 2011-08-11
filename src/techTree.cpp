#include <fstream>
#include <iostream>
#include "techTree.h"

TechTree::TechTree() {
  // nothing to do here, just makes the default constructor private
}

TechTree::~TechTree() {
  UnitMap::const_iterator uit;
  for (uit = units.begin(); uit != units.end(); uit++)
    delete uit->second;
  BuildingMap::const_iterator bit;
  for (bit = buildings.begin(); bit != buildings.end(); bit++)
    delete bit->second;
}

const Entity *TechTree::getEntity(std::string name) {
  UnitMap::const_iterator uit = units.find(name);
  if (uit != units.end())
    return uit->second;

  BuildingMap::const_iterator bit = buildings.find(name);
  if (bit != buildings.end())
    return bit->second;

  return NULL;
}

Entity *TechTree::createEntity(std::string name) {
  const Entity *ref = getEntity(name);
  if (ref == NULL)
    return NULL;

  return new Entity(*ref);
}

std::string TechTree::wstrToStr(const std::wstring &wstr) {
  return std::string(wstr.begin(), wstr.end());
}

TechTree *TechTree::fromFile(std::string filename,
    ImageManager *imgMgr)
{
  std::wifstream in(filename.c_str());

  std::wstring data = L"";
  std::wstring line;
  while (getline(in, line)) {
    data += line;
    if (!in.eof()) data += L"\n";
  }

  JSONValue *tree = JSON::Parse(data.c_str());
  if (!tree) {
    log("Failed to load the technology tree");
    return NULL;
  }

  TechTree *that = fromJSONObject(tree->AsObject(), imgMgr);
  delete tree;

  return that;
}

TechTree *TechTree::fromJSONObject(const JSONObject &tree,
    ImageManager *imgMgr)
{
  TechTree *that = new TechTree();

  JSONObject::const_iterator tree_it;
  for (tree_it = tree.begin(); tree_it != tree.end(); tree_it++) {
    std::string type = wstrToStr(tree_it->first);
    const JSONObject &obj = tree_it->second->AsObject();

    JSONObject::const_iterator it;
    for (it = obj.begin(); it != obj.end(); it++) {
      const std::string &className = wstrToStr(it->first);
      const JSONObject &content = it->second->AsObject();
      const std::wstring &displayName = content.find(L"displayName")->second->AsString();
      const JSONArray &rectVect = content.find(L"spriteRect")->second->AsArray();
      int size = content.find(L"size")->second->AsNumber();

      sf::IntRect spriteRect(rectVect[0]->AsNumber(), rectVect[1]->AsNumber(),
          rectVect[2]->AsNumber(), rectVect[3]->AsNumber());

      if (type == "units") {
        that->units[className] = new Unit(className,
            wstrToStr(displayName),
            spriteRect,
            size,
            imgMgr);
      }
      else if (type == "buildings") {
        that->buildings[className] = new Building(className,
            wstrToStr(displayName),
            spriteRect,
            size,
            imgMgr);
      }
      else
        break;
    }
  }

  log("Successfully loaded the technology tree");
  return that;
}
