#pragma once
#include "BinaryTree.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename K, typename V>
class TreeMap {
private:
    struct Pair {
        K key;
        V value;

        Pair() = default;

        Pair(const K& key, const V& value) : key(key), value(value) {}

        bool operator<(const Pair& other) const {
            return key < other.key;
        }

        bool operator>(const Pair& other) const {
            return key > other.key;
        }

        bool operator==(const Pair& other) const {
            return key == other.key;
        }
    };

    BinaryTree<Pair> mapTree;
    int mapSize;

public:
    TreeMap() : mapSize(0) {}

    void clear() {
        mapTree.clear();
        mapSize = 0;
    }

    bool containsKey(const K& key) {
        try {
            Pair searchKey(key, V{});
            mapTree.get(searchKey);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    V& get(const K& key) {
        Pair searchKey(key, V{});
        return mapTree.get(searchKey).value;
    }

   
};
