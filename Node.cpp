#include "Node.hpp"
#include <iostream>

std::mt19937 Node::mRand;
std::uniform_int_distribution<int> Node::mDist;

/**
 * \brief 乱数発生器を初期化
 *
 * \param mt メルセンヌ・ツイスタ
 */
void Node::init(std::mt19937 mt){
  mRand = mt;
  std::uniform_int_distribution<int> dist(0, 7);
  mDist = dist;
}

Node::Node(int v, bool ismax)
:value(v)
,children()
,visited_count(0)
,total_reward(0)
,is_leaf(true)
,is_max(ismax){
}

/**
 * \brief ノードの子供を追加
 *
 * \param array 子供となるノード
 */
void Node::addChildren(std::shared_ptr<Node> array[]){
  for(int i = 0; i < 8; i++){
    children[i] = array[i];
  }
}

std::shared_ptr<Node> Node::getChild(int i){
  return children[i];
}

/**
 * \brief 親ノードからのエッジのvalueを取得
 * \return value
 */
int Node::getValue(){
  return value;
}

/**
 * \brief そのノードを基点にランダムプレイアウトをしたときの結果を返す
 * \return ランダムプレイアウトで得られる得点の総和
 */
int Node::randomPlayout(){
  if(!children[0]){
    return value;
  }else{
    int idx = mDist(mRand);
    // std::cout << "route: " << idx << std::endl;
    return value + (*children[idx]).randomPlayout();
  }
}

/**
 * \brief 探索中に訪れたときに呼ぶ
 *
 * \param reward エピソードの結果 (勝ち = 1.0, 引き分け = 0.5, 負け = 0.0)
 */
void Node::visited(double reward){
  visited_count++;
  // MAXノードでは, MINノードがこのノードを評価するので, resultを反転させる
  if(is_max) reward = 1.0 - reward;
  total_reward += reward;
}

int Node::getVisitedCount(){
  return visited_count;
}

double Node::getAverageReward(){
  return total_reward / visited_count;
}

/**
 * \brief 葉(末端)かどうか
 * \return 葉 = true
 */
bool Node::isLeaf(){
  return is_leaf;
}

/**
 * \brief 展開する(葉扱いでなくなる)
 */
void Node::deploy(){
  is_leaf = false;
}
