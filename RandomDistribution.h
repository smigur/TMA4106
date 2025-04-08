#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

// File is generally AI-generated, with human tweaks

#include <vector>
#include <string>
#include <random>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <memory>

class RandomDistribution {
public:
    using GeneratorFunc = std::function<double(double, double, std::mt19937&)>;
    
    // Constructor
    RandomDistribution(const std::string& name, 
                      const std::pair<std::string, std::string>& paramNames,
                      GeneratorFunc generator);
    
    // Generate numbers
    std::vector<double> generate(double firstParam, double secondParam, int numSamples) const;
    
    // Accessors
    std::string getName() const { return name_; }
    std::pair<std::string, std::string> getParamNames() const { return paramNames_; }
    
    // Static interface
    static std::vector<std::string>& getAllDistributionNames();
    static RandomDistribution& getDistribution(const std::string& name);

private:
    std::string name_;
    std::pair<std::string, std::string> paramNames_;
    GeneratorFunc generator_;
    mutable std::mt19937 gen_{std::random_device{}()};
    
    // Static members
    static std::vector<std::string> distributionNames_;
    static std::unordered_map<std::string, std::unique_ptr<RandomDistribution>> distributionMap_;
    
    // Initialization
    static void initializeDistributions();
};

#endif // RANDOM_GENERATOR_H