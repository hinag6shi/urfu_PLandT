#include <iostream>
#include "binaryTree.hpp"
#include "levelList.hpp"

using namespace std;

struct QueueNode {
    treeNode* data;
    QueueNode* next;

    QueueNode(treeNode* d) {
        data = d;
        next = nullptr;
    }
};

struct NodeQueue {
    QueueNode* front;
    QueueNode* back;
    int sz;

    NodeQueue() {
        front = nullptr;
        back =nullptr;
        sz = 0;
    }

    ~NodeQueue() {
        while (front) {
            QueueNode* tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }

    void push(treeNode* node) {
        QueueNode* q = new QueueNode(node);
        if (!back)
            front = back = q;
        else {
            back->next = q;
            back = q;
        }
        sz++;
    }

    treeNode* pop() {
        QueueNode* q = front;
        treeNode* t = q->data;
        front = front->next;
        if (!front) back = nullptr;
        delete q;
        sz--;
        return t;
    }
};

LevelList* getLvlCnts(treeNode* root) {
    LevelList* list = new LevelList();
    if (!root) return list;

    NodeQueue q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        list->add(levelSize);
        for (int i = 0; i < levelSize; i++) {
            treeNode* node = q.pop();
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return list;
}

int main() {
    binaryTree tree;
    int n, val;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val;
        tree.insert(val);
    }

    LevelList* levels = getLvlCnts(tree.getRoot());
    cout << "\nNodes per level:\n";
    levels->print(cout);
    delete levels;

    return 0;
}