#include <iostream>
#include "BinaryTree.hpp"
#include "LevelList.hpp"

using namespace std;

struct QueueNode {
    TreeNode* data;
    QueueNode* next;

    QueueNode(TreeNode* d) {
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

    void push(TreeNode* node) {
        QueueNode* q = new QueueNode(node);
        if (!back)
            front = back = q;
        else {
            back->next = q;
            back = q;
        }
        sz++;
    }

    TreeNode* pop() {
        QueueNode* q = front;
        TreeNode* t = q->data;
        front = front->next;
        if (!front) back = nullptr;
        delete q;
        sz--;
        return t;
    }
};

LevelList* getLevelCounts(TreeNode* root) {
    LevelList* list = new LevelList();
    if (!root) return list;

    NodeQueue q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        list->add(levelSize);
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.pop();
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return list;
}

int main() {
    BinaryTree tree;
    int n, val;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val;
        tree.insert(val);
    }

    cout << "\nTree:\n";
    tree.print(cout);

    LevelList* levels = getLevelCounts(tree.getRoot());
    cout << "\nNodes per level:\n";
    levels->print(cout);
    delete levels;

    return 0;
}