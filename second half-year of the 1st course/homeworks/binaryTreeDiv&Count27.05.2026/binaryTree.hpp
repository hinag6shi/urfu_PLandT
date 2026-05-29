#pragma once
#include <iostream>

struct treeNode {
    int val;
    treeNode* left;
    treeNode* right;

    treeNode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

class binaryTree {
private:
    treeNode* root;

    void destroy(treeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void insertBST(treeNode*& node, int val) {
        if (!node) { node = new treeNode(val); return; }
        if (val < node->val) insertBST(node->left, val);
        else insertBST(node->right, val);
    }

public:
    binaryTree() { root = nullptr; }

    ~binaryTree() {
        destroy(root);
    }

    void insert(int val) {
        insertBST(root, val);
    }

    treeNode* getRoot() const {
        return root;
    }
};