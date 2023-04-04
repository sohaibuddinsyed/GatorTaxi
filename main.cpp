#include "MyHeap.h"

using namespace std;

int main() {
    Heap *heap = new Heap();
    heap -> push(new HeapNode(nullptr, 10,11,12));
    heap -> push(new HeapNode(nullptr, 20,9,12));
    heap -> push(new HeapNode(nullptr, 30,9,9));
    heap -> getTopNode();
    cout << heap -> getSize() << endl;

    heap -> pop();

    heap -> getTopNode();
    cout << heap -> getSize() << endl;
}