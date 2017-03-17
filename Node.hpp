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
  static void init(std::mt19937 mt);
private:
  static std::mt19937 mRand;
  static std::uniform_int_distribution<int> mDist;
  int value;
  std::shared_ptr<Node> children[8];
};
