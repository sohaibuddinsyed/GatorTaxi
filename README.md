# GatorTaxi
GatorTaxi replicates the core functionalities of a large scale texi service application such as Uber. The idea is to use efficient data structures and solve a real problem in the most efficient way possible. This project uses clean code, SOLID principles and advanced data structures. Some of the features implemented are:

- Requesting a ride
- Cancelling a ride
- Updating a ride
- Finding best profit ride

## Program Structure
The project consists of 4 main files - MyRBT.h, MyHeap.h, stringUtils.h,
gatorTaxi.cpp.
### gatorTaxi.cpp
The gatorTaxi file is the driver program which does the following:
• Instantiates an RBT
• Instantiates a Min-Heap
• Parses the input file
• Writes output to output file
It consists of the following helper functions:
```c++
void print(RBT *rbt, Heap *heap, int *args, string &output);
void printRange(RBT *rbt, Heap *heap, int *args, string &output);
void insertRide(RBT *rbt, Heap *heap, int* args, string &output);
void getNextRide(RBT *rbt, Heap *heap, string &output);
void cancelRide(RBT *rbt, Heap *heap, int* args, string &output);
void updateTrip(RBT *rbt, Heap *heap, int* args, string &output);
void parseInput(RBT *rbt, Heap *heap, int argc, char **argv, string &output);
```
The first 6 functions are responsible for processing essential GatorTaxi
operations and have been described in Chapter 3. parseInput function
uses file parsing fuctions in stringUtils header and invokes appropriate
GatorTaxi operations. This function is responsible for writing the output
as well.
### MyHeap.h
This is a header file which includes implementation of the Min-Heap. It
has the definition of class HeapNode and class Heap described further
4
in Chapter 2.
### MyRBT.h
This is a header file which includes implementation of the Red-Black Tree.
It has the definition of class RBTNode and class RBT described further in Chapter 2.
1.0.4 stringUtils.h
This is a header file which includes helper functions for file parsing.
```c++
void parseArgs1(int *args, string line)
void parseArgs2(int *args, string line)
void parseArgs3(int *args, string line)
void processOperation(RBT *rbt, Heap *heap, string line, string
operationPrefix, string &output)
```
These functions split the string to parse 1, 2, or 3 arguments and store
them in argv.


# Design and Implementation of Data Structures
The following section describe the design and analysis of the underlying data structures used for the project i.e Min-Heap and Red-Black Tree.

## Min-Heap
A Min-Heap is a complete binary tree that follows a relationship such that
the value of every parent node is always less than the value of it’s child
nodes except for the root which has no parent.
In the following sub-sections, the fundamental min-heap operations are described.
### Heap Node Structure
```c++
class HeapNode {
  RBTNode *rbtNode;
  int index, rideNumber, rideCost, tripDuration;
public:
  HeapNode(RBTNode *rbtNode, int rideNumber, int rideCost, int tripDuration)
};
```

Every heap node has a pointer to the corresponding RBT node and stores
values for the rideNumber, rideCost and tripDuration. The node is
mapped to the index of the Heap array through the index variable. The
constructor can be used to initialize new heap nodes before pushing into
the heap.

### Heap Structure
```c++
class Heap {
  HeapNode* heap[2000];
  int back;
public:
  Heap();
  void push(HeapNode *heapNode);
  HeapNode* pop();
  void remove(HeapNode* heapNode);
  void heapifyUp(int index);
  void heapifyDown(int index);
  void update(HeapNode* heapNode, int newRideCost, int newTripDuration);
};
```

The heap is an array of heap nodes which satisfy the min-heap properties.
The size of the heap is capped at 2000 pertaining to the maximum limit
of input size provided. We describe the members that support min-heap
operations next.
- Index: The integer back stores the index of the HeapNode array where a new
node can be pushed. It is incremented and decremented to maintain this
property. The initial value of back is 0.
- Push Operation: The push method pushes a heap node into the heap array at the back
index. This is followed by the HeapifyUp operation to maintain the minheap property.
- Pop Operation: The pop method pops a heap node from the heap array at the 0th index.
This is followed by the HeapifyDown operation to maintain the min-heap
property.
- Arbitrary Remove Operation: The remove method pops the heap node from the heap array at the 0th
index. This is followed by the HeapifyDown operation to maintain the
min-heap property.

- Heapify-Up Operation: The HeapifyUp method checks the rideCost value of the node with its
parent. If the min-Heap properties are not satisfied, it swaps the nodes
and continues on the parent index. Ties are resolved using tripDuration
- Heapify-Down Operation: The HeapifyDown method checks the rideCost value of the node with its 2
children.. If the min-Heap properties are not satisfied, it swaps the nodes
and continues on the child index. Ties are resolved using tripDuration.
- Update Node Operation: The UpdateNode method checks the rideCost value of the node with its
original value. If the values increase a heapify-down operation is performed
otherwise a heapify-up takes place.

## Red-Black Tree
A Red-Black Tree (RBT) is a self balancing binary search tree similar to
AVL Tree but can run efficient range queries. In this sub-section, the RBT
design and implementation details have been provided.

- RBT Node Structure
```c++
class RBTNode {
  RBTNode *leftChild, *rightChild, *parent;
  HeapNode *heapNode;
  bool color;
  int rideNumber, rideCost, tripDuration;
public :
  RBTNode();
  RBTNode(RBTNode *leftChild, RBTNode *rightChild, RBTNode *parent,
  HeapNode* heapNode, bool color, int rideNumber, int rideCost, int tripDuration);
};
```
An RBT Node has the following data members:
1. RBTNode *parent, *leftChild, *rightChild : These RBT pointers point to the parent and left, right children nodes respectively. The
parent pointer of the root node is null.
2. Heap *heapNode : It is the pointer to the corresponding heap node.
3. bool color : The color is stores as 0 for Red and 1 for Black.
4. int rideNumber, rideCost, tripDuration : These variables are used
to store the values of rideNumber, rideCost and tripDuration respectively.
5. RBT() : Default constructor with all null pointers and values as 0.
6. RBTNode (RBTNode*parent, RBTNode *leftChild, *rightChild,
Heap *heapNode, bool color, int rideNumber, int rideCost, int
tripDuration) : Initializes all members with the corresponding parameter values.

### RBT Structure
```c++
class RBT {
  RBTNode *root;
public:
  RBT();
  bool isExternalNode(RBTNode* node);
  RBTNode* findNode(int key, RBTNode* node);
  RBTNode* findParent(int key, RBTNode* node);
  RBTNode *findCommonAncestor(int r1, int r2, RBTNode *root);
  string range(int r1, int r2);
  void printInorder(int r1, int r2, string &output, RBTNode* node);
  int getChildType(RBTNode* pp, RBTNode* p);
  RBTNode* getMaxNode(RBTNode *p, RBTNode *currMax);

  // Insert methods
  void insert(RBTNode *p);
  void adjustRBT(RBTNode* p);
  void XYr(RBTNode* p);
  void LLRotation(RBTNode* gp);
  void RRRotation(RBTNode* gp);
  void LRRotation(RBTNode* pp, RBTNode *gp);
  void RLRotation(RBTNode* pp, RBTNode *gp);

  // delete methods
  HeapNode* deleteNode(int rideNumber);
  void adjustRBTAfterDelete(RBTNode *y, RBTNode* py);
  void RB0(RBTNode *y, RBTNode *py);
  void RB1Cases(RBTNode *y, RBTNode *py, RBTNode *a);
  void RB11(RBTNode *y, RBTNode *py);
  void RB12(RBTNode *y, RBTNode *py);
  void RB2(RBTNode *y, RBTNode *py);
  void RRCases(RBTNode *py);
  void RR0(RBTNode *py, RBTNode *v, RBTNode *b);
  void RR11(RBTNode *y, RBTNode *py, RBTNode *b);
  void RR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x);
  void RR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x);
  void LB0(RBTNode *y, RBTNode *py);
  void LB1Cases(RBTNode *y, RBTNode *py, RBTNode *b);
  void LB11(RBTNode *y, RBTNode *py);
  void LB12(RBTNode *y, RBTNode *py);
  void LB2(RBTNode *y, RBTNode *py);
  void LRCases(RBTNode *py);
  void LR0(RBTNode *py, RBTNode *v, RBTNode *a);
  void LR11(RBTNode *v, RBTNode *py, RBTNode *c);
  void LR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b);
  void LR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b);
};
```

### RBT Insert Methods
The methods for delete in the case where the deficient sub-tree is the
rightChild of it’s parent have been explained. The other cases for the left
relationship are symmetric.

The insert method inserrts node p into the RBT using the following insert
cases.
- p is the inserted node
- pp is the parent of p
- gp is the parent of pp
- Th color of the inserted node is always red
adjustRBTAfterInsert is called to fix any imbalancse. The various imbalance cases have been described using the folowing convention:

 XYz Insert Cases
- X represents the type of relationship between gp and pp (R/L)
- Y represents the type of relationship between pp and p (R/L)
- n is the number of red children of v.

### RBT Delete Methods
The methods for delete in the case where the deficient sub-tree is the
rightChild of it’s parent have been explained. The other cases for the left
relationship are symmetric.

The deleteNode method deletes a node from the RBT using the BST delete
cases.
1. Deleting a node of degree 0 : The pointers of the parent node are
adjusted.
2. Deleting a node of degree 1 : The parent and child pointers of the
parent and child nodes are adjusted.
3. Deleting a node of degree 2 : The deleted node is replaced with the
in-order predecessor.
If color of the deleted node is red, no further actions are taken. But
if the deleted node is black, adjustRBTAfterDelete is called to fix any
imbalance. The various imbalance cases have been described using the
folowing convention:

- y is the root of the deficient sub-tree
- py is the parent of y
- v is the sibling of y

Xcn Delete Cases
- X represents the type of relationship between u and py (R/L)
- c is the color of the node v (R/B)
- n is the number of red children of v.

Xc(n) Delete Cases
The rotations involved in the imbalance resolution are followed and method names are associated with the various cases. If
X = r, n is the number of red children of the right child of v.


# Design and Analysis of GatorTaxi Operations
## 1) Print(rideNumber)
void print(RBT *rbt, Heap *heap, int *args, string &output);
The print operation calls the findNode operation on the RBT.
- Time Complexity - O(logn)
Finding a node in a BST takes logarithmic operations and therefore this
- Space Complexity - O(logn)
The recursive findNode implementation will incur a O(log n) time stack
space.
## 2) Print(rideNumber1, rideNumber2)
void printRange(RBT *rbt, Heap *heap, int *args, string &output);
This operation calls the range method in the RBT which uses the common
ancestor of the nodes with rideCost as r1 and r2 for the inorder traversal.
- Time Complexity - O(logn + S)
Finding an ancestor in a BST takes logarithmic operations and therefore
this operation in a RBT takes O(log n) time. Once the common ancestor
is obtained, finding the S elements in the LST and RST takes O(S) time.
14
- Space Complexity - O(logn + S)
The recursive findAncestor costs O(log n) space and the recursive in-order
traversal on the common ancestor requires O(S) stack.
## 3) Insert(rideNumber, rideCost, tripDuration)
void insertRide(RBT *rbt, Heap *heap, int* args, string &output);
This operation calls the insert method on the RBT and push method on
the min-heap.
- Time Complexity - O(logn)
• RBT : Searching the parent costs O(log n) and adjusting imbalances
after inserting may take O(log n).
• Heap: Inserting at the last index is O(1) time but heapify operation
costs O(log n).
- Space Complexity - O(logn)
• RBT: Searching the parent and adjusting imbalances after inserting
will take O(log n) stack space.
• Heap: Recursive heapify operation costs O(log n).
## 4) GetNextRide()
void getNextRide(RBT *rbt, Heap *heap, string &output);
- Time Complexity - O(logn)
• RBT: Deleting a node is O(1) time for a red node. In the case of
imbalance, it will take O(log n) to rebalance.
• Heap: Deleting the node is O(1) time. However, the heapify operation
will cost O(log n).

- Space Complexity - O(logn)
• RBT: Adjusting imbalances after deleting may take O(log n).
• Heap: Inserting at the last index is O(1) time but heapify operation
costs O(log n).

## 5) CancelRide(rideNumber)
void cancelRide(RBT *rbt, Heap *heap, int* args, string &output);
We perform delete operation from the RBT and heap.
- Time Complexity - O(logn)
• RBT: Deleting a node is O(1) time for a red node. In the case of
imbalance, it will take O(log n) to rebalance.
• Heap: Deleting the node is O(1) time. However, the heapify operation
will cost O(log n).
- Space Complexity - O(logn)
The recursive findNode and heapify implementations will incur a O(log n)
time stack space.
## 6) UpdateTrip(rideNumber, newtripDuration)
void updateTrip(RBT *rbt, Heap *heap, int* args, string &output);
If the new trip duration is less, we update the value in heap using the
update method. If the new value is less than 2 times old trip duration,
we delete and insert the node with new cost and duration in the RBT but
only heapify in the heap. In the last case, we simply perform a cancelRide
operation.
- Time Complexity - O(logn)
• RBT: In the worst case, an update trip will require both insert and
delete operation which cost O(log n).
16
• Heap: Modifying a heao node may cause a heapify operation which
also takes O(log n) time.
- Space Complexity - O(logn)
Any insert or delete operations will cause O(log n) space in the stack for
both RBT and heap.
17
