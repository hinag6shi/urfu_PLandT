#pragma once

#include <stdexcept>
#include <ostream>
#include <cstddef>

template<typename K, typename V>
class hashtable {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(K _key, V _value, Node* _next) : next(_next), key(_key), value(_value) {};
    };

    Node** buckets;
    int bucketCount;
    int countElements;

    double maxLoadFactor = 0.75;
    void rehash(int newBucketCount) {
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

    void swap(hashtable& other) {
        std::swap(buckets, other.buckets);
        std::swap(bucketCount, other.bucketCount);
        std::swap(countElements, other.countElements);
        std::swap(maxLoadFactor, other.maxLoadFactor);
        std::swap(hash, other.hash);
    }

    size_t (*hash)(K key);
public:
    hashtable(int size, size_t (*_hash)(K key)) : hash(_hash) {
        if (!_hash) throw std::invalid_argument("hash function is null");
        if (size < 1) throw std::invalid_argument("size must be >= 1");

        bucketCount = size;
        countElements = 0;

        buckets = new Node*[bucketCount];

        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = nullptr;
        }
    }
    hashtable(const hashtable& other) : bucketCount(other.bucketCount),
              countElements(0), maxLoadFactor(other.maxLoadFactor), hash(other.hash) {
        buckets = new Node*[bucketCount];
        for (int i = 0; i < bucketCount; i++)
            buckets[i] = nullptr;

        for (int i = 0; i < bucketCount; i++) {
            Node* curr = other.buckets[i];
            Node** dst = &buckets[i];
            while (curr != nullptr) {
                *dst = new Node(curr->key, curr->value, nullptr);
                dst = &(*dst)->next;
                curr = curr->next;
            }
        }
        countElements = other.countElements;
    }
    hashtable& operator=(const hashtable& other) {
        if (this == &other) return *this;
        hashtable tmp(other);
        swap(tmp);
        return *this;
    }

    ~hashtable() {
        clear();
        delete[] buckets;
    }

    void clear() {
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

    double loadFactor() const {
        if (bucketCount == 0) return 0.0;
        return (double)(countElements) / bucketCount;
    }
    void setMaxLoadFactor(double factor) {
        maxLoadFactor = factor;
    }

    bool add(K key, V value) {
        if (loadFactor() > maxLoadFactor) rehash(bucketCount * 2);
        
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
    
    bool find(K key) const {
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
    bool remove(K key) {
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

    int get(K key) const {
        size_t index = hash(key) % bucketCount;
        Node* curr = buckets[index];
        while (curr != nullptr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        throw std::invalid_argument("No key exist");
    }

    void show(std::ostream& out) const {
        for (int i = 0; i < bucketCount; i++) {
            Node* curr = buckets[i];
            if (curr != nullptr) {
                out << "[" << i << "]: ";
                while (curr != nullptr) {
                    out << "("
                        << curr->key
                        << " : "
                        << curr->value
                        << ") -> ";
                    curr = curr->next;
                }
                out << "nullptr\n";
            }
        }
    }
};