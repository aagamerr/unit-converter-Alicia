#ifndef TOMLHANDLER_H
#define TOMLHANDLER_H

#include "FileHandler.h"
#include <sstream>
#include <iostream>

class TOMLHandler : public FileHandler {
private:
    using Table = std::vector<std::vector<std::string>>;
    Table table;

public:
    bool load(std::string filename) override;

    // Selector: TOML column number
    std::vector<std::string> getColumn(std::string selector) override ;

    void appendColumn(std::string newHeader, const std::vector<std::string>& values) override;

    void save(std::string filename) override;
};

#endif