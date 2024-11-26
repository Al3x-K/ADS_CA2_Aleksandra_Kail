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

    BinaryTree<K> keySet() {
        BinaryTree<K> keys;
        auto arr = mapTree.toArray();
        for (int i = 0; i < mapTree.count(); ++i) {
            keys.add(arr[i].key);
        }
        delete[] arr;
        return keys;
    }

    void put(const K& key, const V& value) {
        Pair newPair(key, value);
        try {
            Pair& existing = mapTree.get(newPair);
            existing.value = value; // Update value
        }
        catch (...) {
            mapTree.add(newPair); // Add new entry
            ++mapSize;
        }
    }

    int size() const {
        return mapSize;
    }

    bool removeKey(const K& key) {
        Pair target(key, V{});
        if (mapTree.remove(target)) {
            --mapSize;
            return true;
        }
        return false;
    }

    V& operator[](const K& key) {
        try {
            return get(key);
        }
        catch (...) {
            throw logic_error("Key not found.");
        }
    }
};
