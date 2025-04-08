#pragma once

#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/DropdownList.h"
#include "widgets/TextInput.h"
#include "widgets/TextBox.h"
#include "widgets/Slider.h"
#include <vector>
#include <string>

class GeneratorWindow : public TDT4102::AnimationWindow {
    private:
        
        // Standard element dimentions
        static const int stdElementWidth = 200;
        static const int stdElementHeight = 20;
        // Selection of distribution
        TDT4102::DropdownList distSelector;
        TDT4102::Button distSelectButton;
        // Info-boxes for parameters
        TDT4102::TextBox numOfSimsInfo;
        TDT4102::TextBox firstParamInfo;
        TDT4102::TextBox secondParamInfo;
        TDT4102::TextBox numOfBarsInfo;
        

        // Input-boxes for parameters
        TDT4102::TextInput numOfSimsInput;
        TDT4102::TextInput firstParamInput;
        TDT4102::TextInput secondParamInput;
        TDT4102::Slider numOfBarsSelector;

        TDT4102::Button showGraphButton;

        // Callback functions for elements
        void distButtonCallback();
        void distSelectorCallback();
        void showGraphButtonCallback();
        void numOfBarsSelectorCallback();

    public:
        GeneratorWindow();
        ~GeneratorWindow() = default;
};