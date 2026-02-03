#include "TOMLHandler.h"
#include <sstream>
#include <iostream>

bool TOMLHandler::load(std::string filename) {
    
    table.clear();
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return false;
    }

    std::string line;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue; 

        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        table.push_back(row);
    }

    file.close();
    return true;
}

std::vector<std::string> TOMLHandler::getColumn(std::string selector) {
    std::vector<std::string> results;
    int index = std::stoi(selector); 
    
    // Start at i=1 to skip header
    for (size_t i = 1; i < table.size(); i++) {
        if (index < table[i].size()) {
            results.push_back(table[i][index]);
        } else {
            results.push_back(""); // Handle empty
        }
    }
    return results;
}

void TOMLHandler::appendColumn(std::string newHeader, const std::vector<std::string>& values)  {
    // Add header to row 0
    table[0].push_back(newHeader);

    // Add values to subsequent rows
    for (size_t i = 1; i <= values.size(); i++) {
        table[i].push_back(values[i-1]);
    }
}

void TOMLHandler::save(std::string filename) {
    std::ofstream file(filename);
    
    for (const auto& row : table) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            // Add comma if it's not the last column
            if (i < row.size() - 1) file << ",";
        }
        file << "\n"; // New line at end of row
    }
}