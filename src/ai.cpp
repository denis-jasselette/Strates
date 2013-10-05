#include "ai.h"
#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

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
  //manhattan dist
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

double dist(Node &a, Node &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void addWaypoints(Node *goal, Unit *ent) {
  std::stack<Node*> stack;
  Node* cur = goal;
  while(cur != NULL) {
    stack.push(cur);
    cur = cur->prev;
  }

  //Delete the start point
  stack.pop();
  while(!stack.empty()) {
    Node* n = stack.top();
    stack.pop();
    ent->addWaypoint(sf::Vector2i(n->x, n->y));
    std::cout << n->x << " " << n->y << std::endl;
  }
}

std::vector<Node*> getNeighbors(Map *m, std::vector<Node*> &nodeMap, std::vector<bool> &accMap, Node &n) {
  std::vector<Node*> rtn;
  int w = m->getWidth();
  int h = m->getHeight();

  int j_start = std::max(n.x - 1, 0);
  int i_start = std::max(n.y - 1, 0);

  int j_end = std::min(w, n.x + 2);
  int i_end = std::min(h, n.y + 2);

  for (int j = j_start; j < j_end; j++) {
    for (int i = i_start; i < i_end; i++) {

      if((j == n.x && i == n.y) || accMap[i*w+j]) 
	continue;
      
      if(nodeMap[i*w+j] == NULL)
	nodeMap[i*w+j] = new Node(j, i); 

      std::cout << "j,i " << j << " " << i << std::endl;
      std::cout << nodeMap[i*w+j]->x << " " << nodeMap[i*w+j]->y << std::endl;
      rtn.push_back(nodeMap[i*w+j]);
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

void AI::computePath(Unit *e, const sf::Vector2i &coords) {
  //Compute an accessibility map
  Map* map = game->getMap();
  
  std::vector<bool> accMap(map->getWidth() * map->getHeight(), false);
  std::vector<Entity*>::iterator it;
  std::vector<Entity*> ents = game->getEntities();
  for(it = ents.begin(); it != ents.end(); it++) {
    std::cout << "Addings ent to the visibility map" << std::endl;
    sf::Vector2i pos = (*it)->getTilePosition();
    int size = (*it)->getProperty(L"size")->AsNumber();
    for (int i = pos.y; i < pos.y + size; i++) {
      for (int j = pos.x; j < pos.x + size; j++) {
	accMap[i*map->getWidth()+j] = true;
      }
    }
  }

  //Astar implementation
  std::vector<Node*> nodeMap(map->getWidth() * map->getHeight(), NULL);
  Node *start = new Node(e->getTilePosition().x, e->getTilePosition().y);
  Node *goal = new Node(coords.x, coords.y);
  nodeMap[start->y * map->getWidth() + start->x] = start;
  nodeMap[goal->y * map->getWidth() + goal->x] = goal;
  std::priority_queue<Node*, std::vector<Node*>, CompareNode> queue;
  
  start->g = 0;
  start->f = start->g + heuristicCostEstimate(*start, *goal);
  start->opened = true;
  queue.push(start);
  std::cout << "Start :" << start->x << " " << start->y << std::endl;
  std::cout << "Goal :" << goal->x << " " << goal->y << std::endl;

  while (!queue.empty()) {
    
    Node* current = queue.top();
    if (*current == *goal) {
      addWaypoints(goal, e);
      break;
    }

    std::cout << "Current :" << current->x << " " << current->y << " " << current->f << std::endl;
    queue.pop();
    current->opened = false;
    current->closed = true;

    std::vector<Node*>::iterator it;
    std::vector<Node*> neighbors = getNeighbors(map, nodeMap, accMap, *current);
    for (it = neighbors.begin(); it != neighbors.end(); it++) {
      Node* n = (*it);
      double tent_g = current->g + dist(*n, *current);
      double tent_f = tent_g + heuristicCostEstimate(*n, *goal);
      std::cout << "new " << n->x << " " << n->y << " " <<n->f << std::endl;

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
