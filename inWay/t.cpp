#include "./structures/hashtable.hpp"
#include <bits/stdc++.h>

using namespace std;

size_t _hash(string key) {
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

int main() {
    hashtable<string, int> table(512, _hash);

    table.add("rt", 12);
    table.add("re", 82923);

    table.show(cout);
    return 0;
}