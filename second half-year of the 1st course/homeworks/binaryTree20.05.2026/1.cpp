#include "tree_utils.hpp"

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

Node* mirror(Node* root) {
    if (!root) return nullptr;
    Node* newNode = new Node(root->val);
    newNode->left = mirror(root->right);
    newNode->right = mirror(root->left);
    return newNode;
}

int main() {
    Node* tree = readTree();
    Node* mirrored = mirror(tree);

    cout << "mirror tree:\n";
    printTree(mirrored);
    cout << '\n';

    cout << "In-order: ";
    inorder(mirrored);
    cout << "\n";

    destroy(mirrored);
    destroy(tree);
    return 0;
}