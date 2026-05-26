#pragma once
#include <iostream>

struct LevelNode {
    int count;
    LevelNode* next;

    LevelNode(int c) {
        count = c;
        next = nullptr;
    }
};

class LevelList {
private:
    LevelNode* head;
    LevelNode* tail;
    int sz;

public:
    LevelList() {
        head = nullptr;
        tail = nullptr;
        sz = 0;
    }

    ~LevelList() {
        LevelNode* cur = head;
        while (cur) {
            LevelNode* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    void add(int count) {
        LevelNode* node = new LevelNode(count);
        if (!head)
            head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
        sz++;
    }

    void print(std::ostream& out) const {
        int level = 0;
        for (LevelNode* p = head; p != nullptr; p = p->next, ++level)
            out << "Level " << level << ": " << p->count << " node(s)\n";
    }

    int size() const {
        return sz;
    }
};