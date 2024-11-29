#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_CA2_Aleksandra_Kail/TreeMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TreeMapUnitTests
{
    TEST_CLASS(TreeMapUnitTests)
    {
    public:

        TEST_METHOD(TestPutAndGet)
        {
            TreeMap<int, std::string> map;

            // Add elements
            map.put(1, "One");
            map.put(2, "Two");

            // Check values
            Assert::AreEqual(std::string("One"), map.get(1));
            Assert::AreEqual(std::string("Two"), map.get(2));
        }

        TEST_METHOD(TestUpdateValue)
        {
            TreeMap<int, std::string> map;

            // Add and update elements
            map.put(1, "One");
            map.put(1, "Updated");

            // Check updated value
            Assert::AreEqual(std::string("Updated"), map.get(1));
        }

        TEST_METHOD(TestContainsKey)
        {
            TreeMap<int, std::string> map;

            // Add elements
            map.put(1, "One");

            // Check key presence
            Assert::IsTrue(map.containsKey(1));
            Assert::IsFalse(map.containsKey(2));
        }

        TEST_METHOD(TestRemoveKey)
        {
            TreeMap<int, std::string> map;

            // Add and remove elements
            map.put(1, "One");
            Assert::IsTrue(map.removeKey(1));
            Assert::IsFalse(map.containsKey(1));
            Assert::IsFalse(map.removeKey(2)); // Non-existent key
        }

        TEST_METHOD(TestSize)
        {
            TreeMap<int, std::string> map;

            // Add elements
            map.put(1, "One");
            map.put(2, "Two");

            // Check size
            Assert::AreEqual(2, map.size());

            // Remove an element and check size
            map.removeKey(1);
            Assert::AreEqual(1, map.size());
        }

        TEST_METHOD(TestClear)
        {
            TreeMap<int, std::string> map;

            // Add elements and clear
            map.put(1, "One");
            map.put(2, "Two");
            map.clear();

            // Check size and key presence
            Assert::AreEqual(0, map.size());
            Assert::IsFalse(map.containsKey(1));
        }

        TEST_METHOD(TestKeySet)
        {
            TreeMap<int, std::string> map;

            // Add elements
            map.put(1, "One");
            map.put(2, "Two");

            // Get key set
            auto keys = map.keySet().toArray();
            Assert::AreEqual(1, keys[0]);
            Assert::AreEqual(2, keys[1]);

            delete[] keys; // Clean up dynamic array
        }

        TEST_METHOD(TestOperatorSquareBrackets)
        {
            TreeMap<int, std::string> map;

            // Add elements and access with []
            map.put(1, "One");
            Assert::AreEqual(std::string("One"), map[1]);

            // Update using []
            map.put(1, "Updated");
            Assert::AreEqual(std::string("Updated"), map[1]);
        }
    };
}
