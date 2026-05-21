#pragma once

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) {
        val = v;
        left = nullptr;
        right = nullptr; 
    }
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

void destroy(Node* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

void printTree(Node* root) {
    if (!root) {
        cout << "_";
        return;
    }

    cout << root->val;
    if (root->left || root->right) {
        cout << "(";
        printTree(root->left);
        cout << ",";
        printTree(root->right);
        cout << ")";
    }
}

Node* readTree() {
    int x;
    cin >> x;
    if (!cin) return nullptr;
    if (x == -1) return nullptr;

    Node* root = new Node(x);
    root->left = readTree();
    root->right = readTree();
    return root;
}
