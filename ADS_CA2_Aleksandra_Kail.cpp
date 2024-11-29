#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include "TreeMap.h"

using namespace std;

struct Row {
    int id;
    string make;
    string model;
    int year; // Changed from 'production_year'
    string vin; // Changed from 'VIN_number'
};


// Load data from the CSV file
static vector<Row> loadCSV(const string& filename) {
    vector<Row> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return data;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Row row;

        getline(ss, token, ','); row.id = stoi(token);
        getline(ss, row.make, ',');
        getline(ss, row.model, ',');
        getline(ss, token, ','); row.year = stoi(token);
        getline(ss, row.vin, ',');

        data.push_back(row);
    }
    return data;
}

// Create an index based on a specified field
static void createIndex(const vector<Row>& data, const string& field) {
    unordered_map<string, vector<Row>> index;

    for (const auto& row : data) {
        string key;
        if (field == "Make") key = row.make;
        else if (field == "Model") key = row.model;
        else if (field == "Year") key = to_string(row.year);

        index[key].push_back(row);
    }

    // Replace structured binding with iterator-based loop
    for (auto it = index.begin(); it != index.end(); ++it) {
        const string& key = it->first;
        const vector<Row>& rows = it->second;

        cout << key << ": " << rows.size() << " rows" << endl;
    }
}

// Search for entries based on a field and a value
static void searchByField(const vector<Row>& data, const string& field, const string& value) {
    for (const auto& row : data) {
        if ((field == "Make" && row.make == value) ||
            (field == "Model" && row.model == value) ||
            (field == "Year" && to_string(row.year) == value) ||
            (field == "VIN" && row.vin == value)) {
            cout << "ID: " << row.id << ", Make: " << row.make
                << ", Model: " << row.model << ", Year: " << row.year
                << ", VIN: " << row.vin << endl;
        }
    }
}

void mainUserSearch() {
    string filename = "data.csv";
    auto data = loadCSV(filename);

    if (data.empty()) {
        cout << "No data loaded from file. Exiting." << endl;
        return;
    }

    cout << "Choose an index field (Make/Model/Year): ";
    string field;
    cin >> field;

    createIndex(data, field);

    cout << "Enter value to search: ";
    string value;
    cin.ignore(); // Clear input buffer
    getline(cin, value);

    searchByField(data, field, value);

}


// Function to process the file and populate the TreeMap
void processFile(const string& filename, TreeMap<char, BinaryTree<string>>& wordMap) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file \"" << filename << "\"." << endl;
        return;
    }

    string line, token;
    getline(file, line); // Skip the header row

    while (getline(file, line)) {
        stringstream ss(line);
        Row row;

        // Read fields into the Row struct
        getline(ss, token, ','); row.id = stoi(token);
        getline(ss, row.make, ','); // Process only the "make" field

        // Normalize the "make" field
        string normalizedMake;
        for (char c : row.make) {
            if (isalnum(c)) {
                normalizedMake += tolower(c);
            }
        }

        if (normalizedMake.empty()) continue;

        // Get the first letter
        char firstLetter = normalizedMake[0];

        // Add the make to the appropriate BinaryTree in the TreeMap
        if (!wordMap.containsKey(firstLetter)) {
            BinaryTree<string> newTree;
            newTree.add(normalizedMake);
            wordMap.put(firstLetter, newTree);
        }
        else {
            wordMap.get(firstLetter).add(normalizedMake);
        }
    }

    file.close();
}

// Function to display the organized makes
void displayWordMap(TreeMap<char, BinaryTree<string>>& wordMap) {
    BinaryTree<char> keys = wordMap.keySet();
    auto letters = keys.toArray();

    cout << "\nMakes organized by first letter:\n";
    cout << endl;
    for (int i = 0; i < wordMap.size(); ++i) {
        char letter = letters[i];
        cout << letter << ": ";
        wordMap.get(letter).printInOrderWithCustomOutput([](const string& make) {
            cout << make << " ";
            });
        cout << endl;
    }
    delete[] letters;
}


void mainOrganizeUniqueWords()
{
    TreeMap<char, BinaryTree<string>> wordMap;
    string filename = "data.csv";
    // Process the file to populate the TreeMap
    processFile(filename, wordMap);

    // Display the organized makes
    displayWordMap(wordMap);
}

int main() 
{
	mainOrganizeUniqueWords();
	//mainUserSearch();
	return 0;
}
