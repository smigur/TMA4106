#include "csvHandling.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

std::vector<double> readFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cant open file: " + filename);
    }

    std::vector<double> values;
    std::string valueStr;
        
    // Split by commas
    while (getline(file, valueStr, ',')) {
        try {
            if (!valueStr.empty()) {
                values.push_back(std::stod(valueStr));
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Failed to parse value: " + valueStr);
        }
    }

    if (values.empty()) {
        throw std::runtime_error("No valid data found in file");
    }

    return values;
}


void saveToCSV(const std::vector<double>& values, 
               const std::string& filename) {
    
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Configure precision (6 decimal places by default)
    outFile << std::fixed << std::setprecision(6);

    // Write values
    for (int i = 0; i < values.size(); ++i) {
        outFile << values[i];
        if (i != values.size() - 1) {
            outFile << ",";  // No trailing comma
        }
    }

    outFile.close();
}