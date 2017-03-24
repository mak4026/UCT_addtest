#include "Node.hpp"
#include <iostream>
#include <random>
#include <memory>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>
#include <string>

using namespace std;
mt19937 engine;
uniform_int_distribution<int> max_node(0, 127);
uniform_int_distribution<int> min_node(-127, 0);

int playout_limit = 100;

int DEPLOY_BOUND;
const bool MAX_NODE = true;
const bool MIN_NODE = false;


void genTree(Node& root, int depth){
  if(depth == 0) return;
  std::shared_ptr<Node> array[8];
  for(int i = 0; i < 8; i++){
    std::shared_ptr<Node> p;
    // Nodeのvalueは親からのエッジの値なので, MinノードはMaxの手番の後なので正の値, MaxノードはMinの手番の後なので負の値を持つ
    if(depth % 2 == 0){
      p.reset(new Node(max_node(engine), MIN_NODE));
    }else{
      p.reset(new Node(min_node(engine), MAX_NODE));
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

/**
 * \brief UCT探索
 *
 * \param root 現在見ているノード
 * \param score このエピソードの現在のスコア
 * \return エピソードの利得(勝ち=1.0, 引き分け=0.5, 負け=0.0)
 */
double searchUCB(Node& root, int score){
  if(root.isLeaf()){
    int ep_score = score + root.randomPlayout();
    double result;
    if(ep_score > 0)
      result = 1.0;
    else if(ep_score < 0)
      result = 0.0;
    else
      result = 0.5;
    root.visited(result);

    // TODO: 一定回数訪れていたら展開する
    if(root.getVisitedCount() > DEPLOY_BOUND)
      root.deploy();

    return result;
  }else if(root.getChild(0) == nullptr){
    int ep_score = score + root.getValue();
    double result;
    if(ep_score > 0)
      result = 1.0;
    else if(ep_score < 0)
      result = 0.0;
    else
      result = 0.5;
    root.visited(result);
    return result;
  }else{
    // 子供のUCB値を計算
    double max = -1.0;
    int max_idx = -1;
    for(int i = 0; i < 8; i++){
      Node& cur_node = *(root.getChild(i));
      double cur_ucb;
      if(cur_node.getVisitedCount() == 0){
        cur_ucb = numeric_limits<double>::infinity();
      }else{
        cur_ucb = cur_node.getAverageReward() + sqrt(2.0 * log(root.getVisitedCount()) / cur_node.getVisitedCount());
      }
      if(max < cur_ucb){
        max = cur_ucb;
        max_idx = i;
      }
    }
    Node& max_node = *(root.getChild(max_idx));

    //1段下げて探索
    double result = searchUCB(max_node, score + root.getValue());
    root.visited(result);
    return result;
  }
}

void search(Node& root, int playout_limit){
  double total = 0.0;
  for(int i = 0; i < playout_limit; i++){
    double result = searchUCB(root, 0);
    total += result;
    cout << i << "," << 1.0 - total / (i + 1) << endl;
  }
}

void lastAnswer(shared_ptr<Node> root){
  shared_ptr<Node> cur = root;
  int sum = 0;
  while(cur->getChild(0) != nullptr){
    int max = -1;
    int max_idx = -1;
    for(int i = 0; i < 8; i++){
      int cur_visited_count = cur->getChild(i)->getVisitedCount();
      cout << i << ": " << cur->getChild(i)->getValue() << ", visited count: " << cur_visited_count << endl;
      if(max < cur_visited_count){
        max = cur_visited_count;
        max_idx = i;
      }
    }
    cout << "path: " << max_idx << "->" << endl;
    shared_ptr<Node> next = cur->getChild(max_idx);
    cur.reset();
    cur = next;
    sum += cur->getValue();
  }
  cout << "sum: " << sum << endl;
}

int main(int argc, char *argv[]){
  random_device seed_gen;
  engine.seed(seed_gen());
  Node::init(engine);
  DEPLOY_BOUND = 8;

  if(argc == 2){
    string seedstr = argv[1];
    int treeseed = stoi(seedstr);
    engine.seed(treeseed);
  }

  shared_ptr<Node> a(new Node(0, MAX_NODE));
  genTree(*a, 4);
  // cout << "score: " << a.randomPlayout() << endl;
  a->deploy();
  // dumpTree(a, 0);
  search(*a, 100000);

  // lastAnswer(a);
}
