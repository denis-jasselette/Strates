#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include "ai.h"

enum Dir {
  NONE = 0,
  NW,
  N,
  NE,
  E,
  SE,
  S,
  SW,
  W    
};

class Node {
public:
  Node(int x_, int y_) {
    x = x_;
    y = y_;
    f = 0;
    g = 0;
    prev = NULL;
    opened = false;
    closed = false;
  }  
  
  Node() {
    x = 0;
    y = 0;
    f = 0;
    g = 0;
    prev = NULL;
    opened = false;
    closed = false;
  }
  
  bool operator==(const Node& o) const {
    return x == o.x && y == o.y;
  }
  
  bool operator<(const Node& o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
  
  bool inLine(const Node& o) {
    return x == o.x || y ==o.y || (std::abs(x - o.x) == std::abs(y - o.y));
  }
  
  Dir getDir(const Node& o) {
    
    if(o.x == x - 1 && o.y == y - 1)
      return NW;
    if(o.x == x && o.y == y - 1)
      return N;
    if(o.x == x +1 && o.y == y - 1)
      return NE;
    if(o.x == x - 1 && o.y == y)
      return W;
    if(o.x == x + 1 && o.y == y)
      return E;
    if(o.x == x -1 && o.y == y + 1)
      return SW;
    if(o.x == x  && o.y == y + 1)
      return S;
    if(o.x == x + 1 && o.y == y + 1)
      return SW;
    
    return NONE;
  }
  
  double f;
  double g;
  int x;
  int y;
  Node *prev;
  bool opened;
  bool closed;
  
};

class CompareNode {
public:
  bool operator()(Node*& t1, Node*& t2) {
    return t1->f >= t2->f;
  }
};

double heuristicCostEstimate(Node &a, Node &b) {
  //http://rocketmandevelopment.com/blog/a-heuristics/
  int xDist = std::abs(a.x - b.x);
  int yDist = std::abs(a.y - b.y);

  if (xDist > yDist) 
    return 1.4*yDist + (xDist - yDist);
  else
    return 1.4*xDist + (yDist - xDist);
}

double dist(Node &a, Node &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void addWaypoints(Node *goal, ActionMove *action) {
  std::stack<Node*> stack;
  Node* cur = goal;
  while(cur != NULL) {
    stack.push(cur);
    cur = cur->prev;
  }
  
  action->clearWaypoints();
  //Delete the start point
  stack.pop();
  Node* prev = stack.top();
  Dir lastDir = NONE;
  while(!stack.empty()) {
    Node* n = stack.top();
    Dir dir = prev->getDir(*n);
    stack.pop();
    if  (dir != lastDir) {
      action->addWaypoint(sf::Vector2i(prev->x, prev->y));
    }
    lastDir = dir;
    prev = n;
  }
  
  action->addWaypoint(sf::Vector2i(prev->x, prev->y));
}

std::vector<Node*> getNeighbors(Map *m, std::vector<Node*> &nodeMap, std::vector<bool> &accMap, Node &n) {
  std::vector<Node*> rtn;
  int width = m->getWidth();
  
  //True obstacle
  //false can pass

  bool acc[9];
  //First compute if we are in the map
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      acc[i*3+j] = !m->contains(n.x-1+j, n.y-1+i); 
    }
  }

  //Then compute if the we are occupied
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if(!acc[i*3+j])
	acc[i*3+j] = accMap[(n.y - 1 + i) * width + n.x -1 + j];
    }
  }
  
  //Remove diagonals if there is an obstacle
  acc[0] = acc[0] || acc[1] || acc[3];
  acc[2] = acc[2] || acc[1] || acc[5];
  acc[6] = acc[6] || acc[3] || acc[7];
  acc[8] = acc[8] || acc[5] || acc[7];
  
  //Finaly add the accessible neighbors
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      
      if ((i == 1 && j == 1) || acc[i*3+j]) 
	continue;
      
      int index = (n.y + i - 1) * width + n.x + j - 1;
      if (nodeMap[index] == NULL)
	nodeMap[index] = new Node(n.x + j - 1, n.y + i - 1); 
      
      rtn.push_back(nodeMap[index]);
    }
  }  

  return rtn;
}

AI::AI() {
  game = NULL;
}

void AI::init(Game* game_) {
  game = game_;
}

void AI::prepareAccMap(std::vector<Entity*> &exclude) {
  std::set<Entity*> exclude_set;
  exclude_set.insert(exclude.begin(), exclude.end());
  Map* map = game->getMap();
  accMap = std::vector<bool>(map->getWidth() * map->getHeight(), false);
  std::vector<Entity*>::iterator it;
  std::vector<Entity*> ents = game->getEntities();
  for(it = ents.begin(); it != ents.end(); it++) {
    if (exclude_set.find((*it)) != exclude_set.end()) {
      continue;
    }
    sf::Vector2i pos = (*it)->getTilePosition();
    int size = (*it)->getProperty(L"size")->AsNumber();
    for (int i = pos.y; i < pos.y + size; i++) {
      for (int j = pos.x; j < pos.x + size; j++) {
	accMap[i*map->getWidth()+j] = true;
      }
    }
  }
}

void AI::computePath(Unit *e, const sf::Vector2i &coords, ActionMove *action) {
  //Compute an accessibility map
  Map* map = game->getMap(); 
  
  
  //Astar implementation
  std::vector<Node*> nodeMap(map->getWidth() * map->getHeight(), (Node*) NULL);
  Node *start = new Node(e->getTilePosition().x, e->getTilePosition().y);
  Node *goal = new Node(coords.x, coords.y);
  
  //Find another node if goal is occupied
  int radius = 1;
  bool found = !accMap[goal->y * map->getWidth() + goal->x];
  while (!found) {
    for(int i = 0; i < radius * 2; i++) {
      for(int j = 0; j < radius * 2; j++) {
	int x = goal->x - radius + j;
	int y = goal->y - radius + i;
	if(map->contains(x, y) &&
	   !accMap[y * map->getWidth() + x]) {
	  goal->x = x;
	  goal->y = y;
	  found = true;
	  break;
	}
      }
      if(found)
	break;
    }
    radius++;
  }
  
  nodeMap[start->y * map->getWidth() + start->x] = start;
  nodeMap[goal->y * map->getWidth() + goal->x] = goal;
  std::priority_queue<Node*, std::vector<Node*>, CompareNode> queue;
  
  start->g = 0;
  start->f = start->g + heuristicCostEstimate(*start, *goal);
  start->opened = true;
  queue.push(start);

  while (!queue.empty()) {
    
    Node* current = queue.top();
    if (*current == *goal) {
      addWaypoints(goal, action);
      break;
    }

    queue.pop();
    current->opened = false;
    current->closed = true;

    std::vector<Node*>::iterator it;
    std::vector<Node*> neighbors = getNeighbors(map, nodeMap, accMap, *current);
    for (it = neighbors.begin(); it != neighbors.end(); it++) {
      Node* n = (*it);
      double tent_g = current->g + dist(*n, *current);
      double tent_f = tent_g + heuristicCostEstimate(*n, *goal);

      if (n->closed && tent_f >= n->f)
	continue;

      if (!n->opened || tent_f < n->f) {
	n->prev = current;
	n->g = tent_g;
	n->f = tent_f;
	
	if (!n->opened) {
	  n->opened;
	  queue.push(n);	  
	}
      }
    }
  }

  //Clean our mess
  std::vector<Node*>::iterator nit;
  for (nit = nodeMap.begin(); nit != nodeMap.end(); nit++) {
    if (*nit != NULL) 
      delete *nit;
  }
}
