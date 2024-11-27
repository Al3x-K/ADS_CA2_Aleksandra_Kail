#include "TreeMap.h"
#include <iostream>
#include <string>

using namespace std;

void runTests() 
{
    TreeMap<int, string> testMap;

    // Test put() and size()
    cout << "Adding entries..." << endl;
    testMap.put(1, "One");
    testMap.put(2, "Two");
    testMap.put(3, "Three");

    cout << "Size after adding entries: " << testMap.size() << endl;

    // Test get() and operator[]
    cout << "Value for key 1: " << testMap.get(1) << endl;
    cout << "Value for key 2: " << testMap[2] << endl;

    // Test containsKey()
    cout << "Contains key 2: " << (testMap.containsKey(2) ? "Yes" : "No") << endl;
    cout << "Contains key 4: " << (testMap.containsKey(4) ? "Yes" : "No") << endl;

    // Test remove()
    cout << "Removing key 2..." << endl;
    bool removed = testMap.removeKey(2);
    cout << "Key 2 removed: " << (removed ? "Yes" : "No") << endl;

    // Verify size and contents after removal
    cout << "Size after removal: " << testMap.size() << endl;
    cout << "Contains key 2 after removal: " << (testMap.containsKey(2) ? "Yes" : "No") << endl;

    // Test keySet()
    cout << "Keys in the map: ";
    BinaryTree<int> keys = testMap.keySet();
    keys.printInOrder();

    // Test clear()
    cout << "Clearing map..." << endl;
    testMap.clear();
    cout << "Size after clearing: " << testMap.size() << endl;
    cout << "Contains key 1 after clearing: " << (testMap.containsKey(1) ? "Yes" : "No") << endl;
}

int main() 
{
    cout << "Running TreeMap tests..." << endl;
    runTests();
    return 0;
}
