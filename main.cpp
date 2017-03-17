#include "Node.hpp"
#include <iostream>
#include <random>
#include <memory>

using namespace std;
mt19937 engine;
uniform_int_distribution<> max_node(0, 127);
uniform_int_distribution<> min_node(-127, 0);

void genTree(Node& root, int depth){
  if(depth == 0) return;
  std::shared_ptr<Node> array[8];
  for(int i = 0; i < 8; i++){
    std::shared_ptr<Node> p;
    if(depth % 2 == 0){
      p.reset(new Node(max_node(engine)));
    }else{
      p.reset(new Node(min_node(engine)));
    }
    array[i] = p;
  }
  root.addChildren(array);
  for(int i = 0; i < 8; i++)
    genTree(*array[i], depth-1);
}

void dumpTree(Node& root, int depth){
  cout << root.getValue() << endl;
  if(root.getChild(0) == nullptr) return;
  for(int i = 0; i < 8; i++){
    cout << string(depth+1, ' ');
    dumpTree(*(root.getChild(i)), depth+1);
  }
}

int main(){
  random_device seed_gen;
  engine.seed(seed_gen());
  Node::init(engine);
  Node a(0);
  cout << "start" << endl;
  genTree(a, 2);
  cout << "score: " << a.randomPlayout() << endl;
  dumpTree(a, 0);
}
