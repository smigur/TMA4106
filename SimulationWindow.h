#pragma once
#include "AnimationWindow.h"
#include <memory>
#include <vector>
#include <string>
#include "widgets/Button.h"

class SimulationWindow : public TDT4102::AnimationWindow {
    private:
    // Data from simulation
    std::unique_ptr<std::vector<double>> dataset_;

    // Graphics
    int padding = 20;
    int yAxisSpace = 100;
    int xAxisSpace = 50;
    int maxBarHeight = 400;
    int graphWidth = 500;
    int graphHeight = 500;
    int xAxisDecimalCount = 2;
    int fontSize = 14;

    // Exit-button
    TDT4102::Button exitButton;

    void exitButtonCallback();

    public:
    SimulationWindow(const std::string& filename, int numOfBars = 15);
    ~SimulationWindow() = default;
    void drawHistogram(const std::vector<double>& data, int numOfBars = 15, int numOfxAxisMarks = 10, int numOfyAxisMarks = 5);
};