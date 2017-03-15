#include "Node.hpp"

Node::Node(int v)
:value(v)
,children(){
}

void Node::addChildren(Node* array[]){
  for(int i = 0; i < 8; i++){
    children[i] = array[i];
  }
}

Node* Node::getChild(int i){
  return children[i];
}

int Node::getValue(){
  return value;
}
