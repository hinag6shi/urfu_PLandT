#include "tree_utils.hpp"

int findMax(Node* root) {
    if (!root) return INT_MIN;
    return max({ root->val, findMax(root->left), findMax(root->right) });
}

int countVal(Node* root, int target) {
    if (!root) return 0;
    return (root->val == target ? 1 : 0)
         + countVal(root->left,  target)
         + countVal(root->right, target);
}

int countMaxOccurrences(Node* root) {
    if (!root) return 0;
    return countVal(root, findMax(root));
}

int main() {
    Node* tree = readTree();

    int mx = findMax(tree);
    int cnt = countMaxOccurrences(tree);

    cout << "max el: " << mx << "\n";
    cout << "number of occurrences: " << cnt << "\n";

    destroy(tree);
    return 0;
}