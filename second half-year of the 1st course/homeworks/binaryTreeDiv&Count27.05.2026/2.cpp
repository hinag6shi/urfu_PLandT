#include <iostream>
#include "BinaryTree.hpp"

using namespace std;

TreeNode* findDivisibleByChild(TreeNode* node) {
    if (!node) return nullptr;

    if (node->left && node->left->val != 0 && node->val % node->left->val == 0)
        return node;
    if (node->right && node->right->val != 0 && node->val % node->right->val == 0)
        return node;

    TreeNode* res = findDivisibleByChild(node->left);
    if (res) return res;

    return findDivisibleByChild(node->right);
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

    TreeNode* result = findDivisibleByChild(tree.getRoot());
    if (result) {
        cout << "\nFound node: " << result->val;
        if (result->left && result->left->val != 0 && result->val % result->left->val == 0)
            cout << " (divisible by left child: " << result->left->val << ")\n";
        else
            cout << " (divisible by right child: " << result->right->val << ")\n";
    } else {
        cout << "\nNo such node found.\n";
    }
    return 0;
}