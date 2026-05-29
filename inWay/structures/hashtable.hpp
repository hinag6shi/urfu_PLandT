class hashTable {
private:
    struct vNode {
        int value;
        vNode* next;
        vNode(int value) : next(nullptr), value(value) {}
    };
    struct Node {
        int key;
        Node* value;
        Node* next;
        Node(int k, Node* v) : next(nullptr), key(k), value(v) {};
    };
public:
    
};