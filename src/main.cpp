#include "Converter.h"
#include "Length.h"

#include "FileHandler.h"
#include "CsvHandler.h"
#include "TOMLHandler.h"

#include <iostream>
#include <string>

FileHandler* getFileHandler(std::string filename) {
    if (filename.find(".csv") != std::string::npos) {
        return new CsvHandler();
    } else if (filename.find(".toml") != std::string::npos) {
        return new TOMLHandler();
    }else {
        std::cerr << "File format is not supported!\n";
        return nullptr;
    }
}

int main(){
    std::string filename;
    std::cout << "Enter file location: ";
    std::cin >> filename;

    FileHandler* fileHandler = getFileHandler(filename);
    if (fileHandler == nullptr) return -1;
    
    if (!fileHandler->load(filename)) {
        std::cerr << "Failed to load file! Exiting.\n";
        delete fileHandler;
        return -1;
    }

    std::string selector;
    std::cout << "Enter Column Index: ";
    std::cin >> selector;

    std::string unitOrigin;
    std::string unitTarget;

    std::cout << "Enter original unit: ";
    std::cin >> unitOrigin;

    std::cout << "Enter target unit: ";
    std::cin >> unitTarget;


    Converter* converter = new Length();
    std::vector<std::string> originalCol = fileHandler->getColumn(selector);
    std::vector<std::string> resultCol;

    for (const auto& raw : originalCol)
    {
        try{

            double inputVal = std::stod(raw);
            double baseVal = converter->toBase(inputVal, unitOrigin);
            double result = converter->fromBase(baseVal, unitTarget);
            resultCol.push_back(std::to_string(result));
        }
        catch (...) {
            resultCol.push_back("Error");
        }
    }

    std::string newHeader = unitTarget + "_converted"; 
    fileHandler->appendColumn(newHeader, resultCol);

    // Handle filename and its path
    std::size_t indexSeperator = filename.find_last_of("/") + 1;
    std::string dir = filename.substr(0, indexSeperator);
    std::string file = filename.substr(indexSeperator, filename.length());

    std::string outputFile = dir + "converted_" + file;
    fileHandler->save(outputFile);
    std::cout << "Success! Saved to " << outputFile << "\n";

    // Clean up memory
    delete converter;
    delete fileHandler;


    return 0;
}