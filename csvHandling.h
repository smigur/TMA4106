#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

// Reads a double vector from a csv file
std::vector<double> readFromCSV(const std::string& filename);


// Take a wild guess, buddy (compatible with readFromCSV())
void saveToCSV(const std::vector<double>& values, 
               const std::string& filename);

