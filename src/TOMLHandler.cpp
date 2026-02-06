#include "TOMLHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool TOMLHandler::load(std::string filename) {
    table.clear(); // Sama dengan CSV
    std::ifstream file(filename);
     if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return false;
    }

    std::string line;
    int currentRow = -1;

    while (std::getline(file, line)) {
        if (line.find("[[") != std::string::npos) {
            currentRow++;
            continue;
        }

        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            // Bersihkan spasi (trimming)
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            bool headerFound = false;
            for (size_t i = 0; i < table.size(); i++) {
                if (table[i][0] == key) {
                    // Pastikan ukuran kolom sinkron dengan baris sekarang
                    while (table[i].size() <= (size_t)currentRow + 1) {
                        table[i].push_back("");
                    }
                    table[i][currentRow + 1] = value;
                    headerFound = true;
                    break;
                }
            }

            if (!headerFound) {
                std::vector<std::string> newCol;
                newCol.push_back(key); // Index 0 sebagai header
                for (int j = 0; j < currentRow; j++) {
                    newCol.push_back("");
                }
                newCol.push_back(value);
                table.push_back(newCol);
            }
        }
    }
    file.close();
    return true;
}

std::vector<std::string> TOMLHandler::getColumn(std::string selector) {
    std::vector<std::string> results;
    // Mencari kolom berdasarkan nama header (selector)
    for (size_t i = 0; i < table.size(); i++) {
        if (table[i][0] == selector) {
            // Sesuai permintaan: Ambil data mulai index 1 (skip header)
            for (size_t j = 1; j < table[i].size(); j++) {
                results.push_back(table[i][j]);
            }
            break; 
        }
    }
    return results;
}

void TOMLHandler::appendColumn(std::string newHeader, const std::vector<std::string>& values) {
    std::vector<std::string> row; // Menggunakan nama 'row' agar mirip CSV walau ini kolom
    row.push_back(newHeader);
    for (const auto& v : values) {
        row.push_back(v);
    }
    table.push_back(row);
}

void TOMLHandler::save(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open() || table.empty()) return;

    size_t maxRows = 0;
    for (const auto& col : table) {
        if (col.size() > maxRows) maxRows = col.size();
    }

    // Menggunakan loop 'r' (row) dan 'c' (column) yang standar
    for (size_t j = 1; j < maxRows; j++) {
        file << "[[packets]]\n";
        for (size_t i = 0; i < table.size(); i++) {
            if (j < table[i].size() && !table[i][j].empty()) {
                file << table[i][0] << " = " << table[i][j] << "\n";
            }
        }
        file << "\n";
    }
    file.close();
}