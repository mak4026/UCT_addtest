/**
 * P-game treeのNode
 */

#include <memory>
#include <random>

class Node {
public:
  Node(int value);
  void addChildren(std::shared_ptr<Node> array[]);
  std::shared_ptr<Node> getChild(int i);
  int getValue();
  int randomPlayout();
  void visited(double reward);
  int getVisitedCount();
  double getAverageReward();
  bool isLeaf();
  void deploy();
  static void init(std::mt19937 mt);
private:
  static std::mt19937 mRand;
  static std::uniform_int_distribution<int> mDist;
  int value;                                        // 親ノードからつながっている辺のvalue
  std::shared_ptr<Node> children[8];                // ノードの子供へのポインタ
  int visited_count;                                // 探索中訪れた回数
  double total_reward;                              // エピソードの総計得点
  bool is_leaf;                                     // ノードが葉かどうか
};
