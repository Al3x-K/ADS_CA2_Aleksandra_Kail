#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

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

int main() {
    string filename = "data.csv";
    auto data = loadCSV(filename);

    if (data.empty()) {
        cout << "No data loaded from file. Exiting." << endl;
        return 1;
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

    return 0;
}
