#include "RandomDistribution.h"

// Initialize static members
std::vector<std::string> RandomDistribution::distributionNames_;
std::unordered_map<std::string, std::unique_ptr<RandomDistribution>> RandomDistribution::distributionMap_;

// Constructor
RandomDistribution::RandomDistribution(const std::string& name,
                                    const std::pair<std::string, std::string>& paramNames,
                                    GeneratorFunc generator)
    : name_(name), paramNames_(paramNames), generator_(generator) {}

// Static initialization
void RandomDistribution::initializeDistributions() {
    if (!distributionMap_.empty()) return;

    // Create distributions using new + unique_ptr

    distributionMap_["lognormal"] = std::unique_ptr<RandomDistribution>(
        new RandomDistribution(
            "lognormal",
            {"Log mean", "Log stddev"},
            [](double logMean, double logStddev, std::mt19937& gen) {
                if (logStddev <= 0) throw std::invalid_argument("Lognormal: log stddev must be > 0");
                std::lognormal_distribution<double> dist(logMean, logStddev);
                return dist(gen);
            }
        )
    );

    distributionMap_["exponential"] = std::unique_ptr<RandomDistribution>(
        new RandomDistribution(
            "exponential",
            {"Rate", "(Unused)"},
            [](double rate, double, std::mt19937& gen) {
                if (rate <= 0) throw std::invalid_argument("Exponential: rate must be > 0");
                std::exponential_distribution<double> dist(rate);
                return dist(gen);
            }
        )
    );

    distributionMap_["normal"] = std::unique_ptr<RandomDistribution>(
        new RandomDistribution(
            "normal",
            {"Mean", "Standard deviation"},
            [](double mean, double stddev, std::mt19937& gen) {
                if (stddev <= 0) throw std::invalid_argument("Normal: standard deviation must be > 0");
                std::normal_distribution<double> dist(mean, stddev);
                return dist(gen);
            }
        )
    );

    distributionMap_["uniform"] = std::unique_ptr<RandomDistribution>(
        new RandomDistribution(
            "uniform",
            {"Lower bound", "Upper bound"},
            [](double a, double b, std::mt19937& gen) {
                if (a >= b) throw std::invalid_argument("Uniform: lower bound must be < upper bound");
                std::uniform_real_distribution<double> dist(a, b);
                return dist(gen);
            }
        )
    );

    // Populate names vector
    for (const auto& pair : distributionMap_) {
        distributionNames_.push_back(pair.first);
    }
}


// Public static methods
std::vector<std::string>& RandomDistribution::getAllDistributionNames() {
    initializeDistributions();
    return distributionNames_;
}

RandomDistribution& RandomDistribution::getDistribution(const std::string& name) {
    initializeDistributions();
    auto it = distributionMap_.find(name);
    if (it == distributionMap_.end()) {
        throw std::invalid_argument("Unknown distribution: " + name);
    }
    return *it->second;
}

// Population generation method
std::vector<double> RandomDistribution::generate(double firstParam, double secondParam, int numSamples) const {
    std::vector<double> results;
    results.reserve(numSamples);
    
    try {
        for (int i = 0; i < numSamples; ++i) {
            results.push_back(generator_(firstParam, secondParam, gen_));
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Generation failed for ") + name_ + ": " + e.what());
    }
    
    return results;
}
