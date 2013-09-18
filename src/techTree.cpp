#include <fstream>
#include <iostream>
#include "techTree.h"

TechTree::TechTree(JSONValue *tree) : tree(tree) {
  // nothing to do here, just makes the default constructor private
}

TechTree::~TechTree() {
  UnitMap::const_iterator uit;
  for (uit = units.begin(); uit != units.end(); uit++)
    delete uit->second;
  BuildingMap::const_iterator bit;
  for (bit = buildings.begin(); bit != buildings.end(); bit++)
    delete bit->second;

  delete tree;
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

  TechTree *that = fromJSONObject(tree, imgMgr);

  return that;
}

/* A tech-tree is divided into a subtree for buildings, units and upgrades.
 * Each subtree has objects as direct children, each object has a className
 * identifying it and a list of properties. */
TechTree *TechTree::fromJSONObject(JSONValue *tree_value,
    ImageManager *imgMgr)
{
  const JSONObject tree = tree_value->AsObject();
  TechTree *that = new TechTree(tree_value);

  JSONObject::const_iterator tree_it;
  for (tree_it = tree.begin(); tree_it != tree.end(); tree_it++) {
    std::string type = wstrToStr(tree_it->first);
    const JSONObject &obj = tree_it->second->AsObject();

    JSONObject::const_iterator it;
    for (it = obj.begin(); it != obj.end(); it++) {
      const std::string &className = wstrToStr(it->first);
      const JSONObject &properties = it->second->AsObject();

      if (type == "units") {
        that->units[className] = new Unit(className,
            properties,
            imgMgr);
      }
      else if (type == "buildings") {
        that->buildings[className] = new Building(className,
            properties,
            imgMgr);
      }
      else if (type == "upgrades") {
        // TODO: support this
      }
      else {
        log("Unknown type found in tech tree");
      }
    }
  }

  log("Successfully loaded the technology tree");
  return that;
}
