#include "SimulationWindow.h"
#include "csvHandling.h"
#include <algorithm>
#include <iostream>
#include <cmath>

SimulationWindow::SimulationWindow(const std::string& filename, int numOfBars) 
    : exitButton{{padding, graphHeight + xAxisSpace + padding}, 100, 20, "Exit"}
{
    exitButton.setCallback([this]() {this->exitButtonCallback();});
    dataset_ = std::make_unique<std::vector<double>>(readFromCSV(filename));
    std::sort(dataset_->begin(), dataset_->end());
    drawHistogram(*dataset_, numOfBars);
    add(exitButton);
}

void SimulationWindow::exitButtonCallback() {
    exit(0);
}

void SimulationWindow::drawHistogram(const std::vector<double>& data, int numOfBars, int numOfxAxisMarks, int numOfyAxisMarks) {
    int barWidth = graphWidth/numOfBars;
    double firstxValue = data.front();
    double lastxValue = data.back();
    // What span of x-values each bar covers
    double barxValueIncrement = (lastxValue - firstxValue)/static_cast<double>(numOfBars);
    // Number of x-values that have been drawn so far
    int xValuesCovered = 0;

    // vector for amount of x-values belonging to each bar
    std::vector<int> barPopulations;
    for (int i = 0; i < numOfBars; i++) {
        barPopulations.push_back(0);
        for (int j = xValuesCovered; data.at(j) < firstxValue + (i + 1) * barxValueIncrement; j++) {
            barPopulations.at(i) ++;
            xValuesCovered++;
        }
    }
    // Draws the rectangles, scaled
    int largestPopulation = *std::max_element(barPopulations.begin(), barPopulations.end());
    float barScale = maxBarHeight / static_cast<float>(largestPopulation);
    for(int i = 0; i < numOfBars; i++) {
        draw_rectangle(
            {
                padding + yAxisSpace + barWidth * i, 
                graphHeight - padding - xAxisSpace
            }, 
            barWidth, 
            -static_cast<int>(barPopulations.at(i)*barScale), 
            TDT4102::Color::dark_slateblue, 
            TDT4102::Color::black
        );
    }
    //Draws axes: 

    // Scale of axes to values
    float xAxisScale = graphWidth / (lastxValue - firstxValue);
    float yAxisScale = maxBarHeight / static_cast<float>(largestPopulation);

    // Axis marks - x axis is simply rounded down and up respectively
    int lowestxAxisMark = static_cast<int>(firstxValue);

    int lowestyAxisMark = 0; // Important for correct proportions

    float xAxisMarkSize = (lastxValue - firstxValue) / numOfxAxisMarks;
    float yAxisMarkSize = largestPopulation / numOfyAxisMarks;

    // Draws x-axis marks
    for (int i = 0; i <= numOfxAxisMarks; i++) {
        draw_text(
            {
                static_cast<int>(padding + yAxisSpace + (i - 0.5) * xAxisMarkSize * xAxisScale), 
                graphHeight-padding
            }, // x-axis label must be created in a convoluted way to write an appropriate number of decimals
            (std::ostringstream() << std::fixed << std::setprecision(xAxisDecimalCount) << lowestxAxisMark + i * xAxisMarkSize).str(), 
            TDT4102::Color::black, 
            fontSize
        );
        draw_line(
            {
                static_cast<int>(padding + yAxisSpace + i * xAxisMarkSize * xAxisScale), 
                graphHeight - xAxisSpace
            }, 
            {
                static_cast<int>(padding + yAxisSpace + i * xAxisMarkSize * xAxisScale), 
                graphHeight - xAxisSpace - padding
            }
        );
    }
    // Draws y-axis marks
    for (int i = 0; i <= numOfyAxisMarks; i++) {
        draw_text(
            {
                padding, 
                static_cast<int>(graphHeight - padding - xAxisSpace - i * yAxisMarkSize * yAxisScale)
            }, 
            std::to_string(static_cast<int>(lowestyAxisMark + i * yAxisMarkSize)), 
            TDT4102::Color::black, 
            fontSize
        );
        draw_line(
            {
                yAxisSpace, 
                static_cast<int>(graphHeight - padding - xAxisSpace - i * yAxisMarkSize * yAxisScale)
            }, 
            {
                padding + yAxisSpace, 
                static_cast<int>(graphHeight - padding - xAxisSpace - i * yAxisMarkSize * yAxisScale)
            }
        );
    }
}