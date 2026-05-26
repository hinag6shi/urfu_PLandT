#pragma once
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    TreeNode* root;

    void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void insertBST(TreeNode*& node, int val) {
        if (!node) {
            node = new TreeNode(val);
            return;
        }
        if (val < node->val)
            insertBST(node->left, val);
        else
            insertBST(node->right, val);
    }

    void printHelper(std::ostream& out, TreeNode* node, int depth) const {
        if (!node) return;
        printHelper(out, node->right, depth + 1);
        for (int i = 0; i < depth; i++) out << "    ";
        out << node->val << "\n";
        printHelper(out, node->left, depth + 1);
    }

public:
    BinaryTree() { root = nullptr; }

    ~BinaryTree() {
        destroy(root);
    }

    void insert(int val) {
        insertBST(root, val);
    }

    TreeNode* getRoot() const {
        return root;
    }

    void print(std::ostream& out) const {
        printHelper(out, root, 0);
    }
};