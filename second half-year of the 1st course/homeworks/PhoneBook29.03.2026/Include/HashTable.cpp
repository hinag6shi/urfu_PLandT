#include "HashTable.hpp"
#include <bits/stdc++.h>

using namespace std;

Node::Node(const string& key, const string& value, Node* next) {
    this->key = key;
    this->value = value;
    this->next = next;
}

void HashTable::rehash(int newBucketCount) {
    if (newBucketCount < 1) return;
    Node** newBuckets = new Node*[newBucketCount];
    for (int i = 0; i < newBucketCount; i++) {
        newBuckets[i] = nullptr;
    }

    for (int i = 0; i < bucketCount; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            size_t index = hash(curr->key) % newBucketCount; // перерасчёт для нод
            curr->next = newBuckets[index];
            newBuckets[index] = curr;
            curr = nextNode;
        }
    }
    delete[] buckets;
    buckets = newBuckets;
    bucketCount = newBucketCount;
}

size_t HashTable::defhash(const string& key) { // Дефолтный хэш приводит всё к нижнему регистру
    size_t h = 0;
    const size_t p = 131;
    for (unsigned char c : key) {
        if ('A' <= c && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        h = (h * p + c);
    }
    return h;
}

bool HashTable::defvalidKey(const string& key) {
    if (key.empty()) return false;

    for (unsigned char c : key) {
        if (!((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool HashTable::defvalidValue(const string& value) {
    return !value.empty();
}

HashTable::HashTable(int size) {
    bucketCount = size;
    countElements = 0;

    buckets = new Node*[bucketCount];

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr;
    }
    hash = defhash;
    validKey = defvalidKey;
    validValue = defvalidValue;
}

HashTable::HashTable(int size, size_t (*hash_)(const string& x)) {
    bucketCount = size;
    countElements = 0;
    buckets = new Node*[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr;
    }

    hash = hash_;
    validKey = defvalidKey;
    validValue = defvalidValue;
}

HashTable::HashTable(re
        int size, bool (*validKey_)(const string& x), bool (*validValue_)(const string& x)) {
    bucketCount = size;
    countElements = 0;
    buckets = new Node*[bucketCount];
    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr;
    }
    hash = defhash;
    validKey = validKey_;
    validValue = validValue_;
}

HashTable::HashTable(int size, size_t (*hash_)(const string& x),
        bool (*validKey_)(const string& x), bool (*validValue_)(const string& x)) {
    bucketCount = size;
    countElements = 0;
    buckets = new Node*[bucketCount];

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = nullptr;
    }
    hash = hash_;
    validKey = validKey_;
    validValue = validValue_;
}

HashTable::~HashTable() {
    clear();
    delete[] buckets;
}

void HashTable::clear() {
    for (int i = 0; i < bucketCount; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        buckets[i] = nullptr;
    }
    countElements = 0;
}

double HashTable::loadFactor() const {
    if (bucketCount == 0) return 0.0;
    return static_cast<double>(countElements) / bucketCount;
}

void HashTable::setLoadFactor(double factor) {
    if (factor <= 0.0) return;   // можно заменить на throw
    maxLoadFactor = factor;
}

bool HashTable::add(const string& key, const string& value) { // Если ключ один и тот же -- перезаписывает значение
    if (loadFactor() > maxLoadFactor) {
        rehash(bucketCount * 2);
    }
    if (!validKey(key) || !validValue(value)) {
        return false;
    }
    
    size_t index = hash(key) % bucketCount;
    Node* curr = buckets[index];

    while (curr != nullptr) {
        if (curr->key == key) {
            curr->value = value;
            return true;
        }
        curr = curr->next;
    }
    Node* newNode = new Node(key, value, buckets[index]);
    buckets[index] = newNode;
    countElements++;

    return true;
}

bool HashTable::find(const string& key) {
    if (!validKey(key)) return false;

    size_t index = hash(key) % bucketCount;

    Node* curr = buckets[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

bool HashTable::remove(const string& key) {
    if (!validKey(key)) return false;
    size_t index = hash(key) % bucketCount;

    Node* curr = buckets[index];
    Node* prev = nullptr;

    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) {
                buckets[index] = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            delete curr;
            countElements--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

string HashTable::get(const string& key) {
    if (!validKey(key)) return "";
    size_t index = hash(key) % bucketCount;
    Node* curr = buckets[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    return "";
}

void HashTable::show() {
    for (int i = 0; i < bucketCount; i++) {
        cout << "[" << i << "]: ";
        Node* curr = buckets[i];
        while (curr != nullptr) {
            cout << "("
                << curr->key
                << " : "
                << curr->value
                << ") -> ";
            curr = curr->next;
        }
        cout << "nullptr\n";
    }
}