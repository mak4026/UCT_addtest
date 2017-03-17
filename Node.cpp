#include "Node.hpp"
#include <iostream>

std::mt19937 Node::mRand;
std::uniform_int_distribution<int> Node::mDist;

void Node::init(std::mt19937 mt){
  mRand = mt;
  std::uniform_int_distribution<int> dist(0, 7);
  mDist = dist;
}

Node::Node(int v)
:value(v)
,children(){
}

void Node::addChildren(std::shared_ptr<Node> array[]){
  for(int i = 0; i < 8; i++){
    children[i] = array[i];
  }
}

std::shared_ptr<Node> Node::getChild(int i){
  return children[i];
}

int Node::getValue(){
  return value;
}

int Node::randomPlayout(){
  if(!children[0]){
    return value;
  }else{
    int idx = mDist(mRand);
    std::cout << "route: " << idx << std::endl;
    return value + (*children[idx]).randomPlayout();
  }
}
