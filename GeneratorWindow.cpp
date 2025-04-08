#include "GeneratorWindow.h"
#include "RandomDistribution.h"
#include "csvHandling.h"
#include "SimulationWindow.h"
#include <iostream>
#include <string>
#include <stdexcept>

GeneratorWindow::GeneratorWindow() 
    :   distSelector{{10, 50}, stdElementWidth, stdElementHeight, RandomDistribution::getAllDistributionNames()}, 
        distSelectButton{{10, 10}, stdElementWidth, stdElementHeight, "Simulate"}, 
        numOfSimsInfo{{350, 10}, stdElementWidth, stdElementHeight, "Number of simulations:"}, 
        numOfSimsInput{{350, 40}, stdElementWidth, stdElementHeight}, 
        firstParamInfo{{350, 80}, stdElementWidth, stdElementHeight, "Lower bound"}, 
        firstParamInput{{350, 110}, stdElementWidth, stdElementHeight}, 
        secondParamInfo{{350, 150}, stdElementWidth, stdElementHeight, "Upper bound"}, 
        secondParamInput{{350, 180}, stdElementWidth, stdElementHeight}, 
        showGraphButton{{10, 250}, stdElementWidth, stdElementHeight, "Generate histogram"}, 
        numOfBarsInfo{{10, 290}, stdElementWidth, stdElementHeight, "Number of bars: "}, 
        numOfBarsSelector{{10, 320}, stdElementWidth, stdElementHeight, 1, 30, 15}
    {
    add(distSelector);
    distSelectButton.setCallback([this]() { this->distButtonCallback();});
    distSelector.setCallback([this]() { this->distSelectorCallback();});
    showGraphButton.setCallback([this]() { this->showGraphButtonCallback();});
    numOfBarsSelector.setCallback([this]() { this->numOfBarsSelectorCallback();});
    add(distSelectButton);
    add(numOfSimsInfo);
    add(numOfSimsInput);
    add(firstParamInfo);
    add(firstParamInput);
    add(secondParamInfo);
    add(secondParamInput);
    add(showGraphButton);
    add(numOfBarsInfo);
    add(numOfBarsSelector);
}

void GeneratorWindow::distButtonCallback() {
    // If exponential is chosen, fills in 0 as a placeholder (usually changes nothing, prevents crash if secondParamInput is empty)
    if (distSelector.getSelectedValue() == "exponential") {
        secondParamInput.setText("0");
    };
    std::cout << firstParamInput.getText() << std::endl;
    double firstParam;
    double secondParam;
    int numOfSims;

    // Does not work, reason unknown
    try {
        firstParam = std::stod(firstParamInput.getText());
        secondParam = std::stod(secondParamInput.getText());
        numOfSims = std::stoi(numOfSimsInput.getText());
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return;
    }
    std::vector<double> simulationResults = RandomDistribution::getDistribution(distSelector.getSelectedValue()).generate(firstParam, secondParam, numOfSims);
    saveToCSV(simulationResults, "simulation_results.csv");
}

void GeneratorWindow::distSelectorCallback() {
    // Sets correct parameter names
    firstParamInfo.setText(RandomDistribution::getDistribution(distSelector.getSelectedValue()).getParamNames().first);
    secondParamInfo.setText(RandomDistribution::getDistribution(distSelector.getSelectedValue()).getParamNames().second);
    // Checks if it's exponential, hides the second parameter
    if(distSelector.getSelectedValue() == "exponential"){
        secondParamInfo.setVisible(false);
        secondParamInput.setVisible(false);
    }
    else{
        secondParamInfo.setVisible(true);
        secondParamInput.setVisible(true);
    }
}

void GeneratorWindow::showGraphButtonCallback() {
    SimulationWindow simWin("simulation_results.csv", numOfBarsSelector.getValue());
    simWin.wait_for_close();
}

void GeneratorWindow::numOfBarsSelectorCallback() {
    numOfBarsInfo.setText("Number of bars: " + std::to_string(numOfBarsSelector.getValue()));
}