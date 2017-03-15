/**
 * P-game treeのNode
 */

class Node {
public:
  Node(int value);
  void addChildren(Node* array[]);
  Node* getChild(int i);
  int getValue();
private:
  Node* children[8];
  int value;
};
