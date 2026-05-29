#pragma once

#include <iostream>

class stack {
private:
    struct Node {
        int val;
        Node* next;
        Node(int v) : val(v), next(nullptr) {}
    };

    int sz;
    Node* head;

    void destroy(Node* head){
        if (!head) return;
        destroy(head->next);
        delete head;
    }
public:
    stack() : sz(0), head(nullptr) {};
    ~stack() { destroy(head); head = nullptr; sz = 0; }
    
    void push(int val) {
        Node* nn = new Node(val);
        nn->next = head;
        head = nn;
        sz ++;
    }

    int top() {
        if (!head) throw std::runtime_error("Stack is empty. Cannot access top element.");
        return head->val;
    }
    int pop() {
        if (!head) throw std::runtime_error("Stack is empty. Cannot pop element.");
        int tval = head->val;
        Node* tNode = head;
        head = head->next;
        delete tNode;

        sz -= 1;
        return tval;
    }
};
