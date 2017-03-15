#include "Node.hpp"
#include <iostream>
#include <random>

using namespace std;
mt19937 engine;
uniform_int_distribution<> max_node(0, 127);
uniform_int_distribution<> min_node(-127, 0);

void genTree(Node* root, int depth){
  if(depth == 0) return;
  Node* array[8];
  for(int i = 0; i < 8; i++){
    Node *p;
    if(depth % 2 == 0){
      p = new Node(max_node(engine));
    }else{
      p = new Node(min_node(engine));
    }
    array[i] = p;
  }
  root->addChildren(array);
  for(int i = 0; i < 8; i++)
    genTree(array[i], depth-1);
}

void dumpTree(Node *root, int depth){
  cout << root->getValue() << endl;
  if(root->getChild(0) == nullptr) return;
  for(int i = 0; i < 8; i++){
    cout << string(depth+1, ' ');
    dumpTree(root->getChild(i), depth+1);
  }
}

int main(){
  random_device seed_gen;
  engine.seed(seed_gen());
  Node a(0);
  cout << "start" << endl;
  // Node* array[8];
  // for(int i = 0; i < 8; i++){
  //   Node *p = new Node(i);
  //   array[i] = p;
  // }
  genTree(&a, 5);
  // cout << a.getValue() << endl;
  // for(int i = 0; i < 8; i++){
  //   cout << " " << a.getChild(i)->getValue() << endl;
  //   for(int j = 0; j < 8; j++){
  //     cout << "  "  << a.getChild(i)->getChild(j)->getValue() << endl;
  //   }
  // }
  dumpTree(&a, 0);
}
