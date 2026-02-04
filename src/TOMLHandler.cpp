#include "TOMLHandler.h"
#include "toml.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

bool TOMLHandler::load(std::string filename) {
    table.clear();
    try {
        auto config = toml::parse_file(filename);
        auto packets = config["packets"].as_array();
        
        if (!packets) {
            std::cerr << "Error: Could not open " << filename << "\n";
            return false;
        }

        // 1. Ambil Header secara otomatis
        std::vector<std::string> headers;
        if (packets->size() > 0) {
            auto first_packet = packets->at(0).as_table();
            for (auto&& [key, value] : *first_packet) {
                headers.push_back(std::string(key.str()));
            }
            table.push_back(headers);
        }

        // 2. Isi Data (Row)
        for (auto&& node : *packets) {
            auto packet_table = node.as_table();
            std::vector<std::string> row;
            
            for (const auto& h : headers) {
                std::stringstream ss;
                // Ambil value-nya dulu baru masukkan ke stringstream
                auto val = packet_table->at(h);
                ss << val.node();
                
                std::string s = ss.str();
                // Bersihkan kutip dua agar sama seperti CSV (polos)
                if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
                    s = s.substr(1, s.size() - 2);
                }
                row.push_back(s);
            }
            table.push_back(row);
        }
        return true;
    } catch (const toml::parse_error& err) {
        std::cerr << "Error: " << err << "\n";
        return false;
    }
}

std::vector<std::string> TOMLHandler::getColumn(std::string selector) {
    std::vector<std::string> results;
    int index = std::stoi(selector); 
    
    // Start at i=1 to skip header (Sama persis logic CSV kamu)
    for (size_t i = 1; i < table.size(); i++) {
        if (index < (int)table[i].size()) {
            results.push_back(table[i][index]);
        } else {
            results.push_back(""); 
        }
    }
    return results;
}

void TOMLHandler::appendColumn(std::string newHeader, const std::vector<std::string>& values)  {
    // Add header to row 0
    if (!table.empty()) {
        table[0].push_back(newHeader);

        // Add values to subsequent rows
        for (size_t i = 1; i < table.size(); i++) {
            if (i - 1 < values.size()) {
                table[i].push_back(values[i-1]);
            } else {
                table[i].push_back("");
            }
        }
    }
}

void TOMLHandler::save(std::string filename) {
    std::ofstream file(filename);
    
    for (const auto& row : table) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}