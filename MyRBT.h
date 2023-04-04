#define RED 0, BLACK 1

class HeapNode;

class RBTNode {
    RBTNode *leftChild, *rightChild, *parent;
    HeapNode *hptr;
    bool color;
    int rideNumber, rideCost, tripDuration;
};

class RBT {
public:
    RBTNode *root;
};