/*
  ==============================================================================

    JuceItParameterDefines.h
    Created: 8 Jul 2020 5:32:00pm
    Author:  Sebastian Badon

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/**
    This header files is for definition of constants for related to the audio plugin interface
 */

//Global Bounds
#define JUCEIT_SIZE 596
#define JUCEIT_PADDING 120
#define JUCEIT_FILTER_BOUNDS 354

//Filter Component Constants
#define FILTER_COORDINATES_OFFSET 3.0f
#define MAX_Y_COORDINATE_POSITION 172.0f
#define FILTER_HEIGHT 160.0f
#define MAX_X_COORDINATE_POSITION JUCEIT_FILTER_BOUNDS-FILTER_COORDINATES_OFFSET

//Color definitions
const juce::Colour JuceItBorder_Colour1 =               juce::Colours::white;
const juce::Colour JuceItBorder_Colour2 =               juce::Colours::black;
const juce::Colour JuceItRectBorder_Colour1 =           juce::Colour(173, 173, 173);
const juce::Colour JuceItFilterBackground_Colour1 =     juce::Colour(89, 120, 182);
const juce::Colour JuceItFilterBackground_Colour2 =     juce::Colours::black;
const juce::Colour JuceItFilterFillBackground_Colour1 = juce::Colour(105, 250, 235);
const juce::Colour JuceItFilterFillBackground_Colour2 = juce::Colour(117, 208, 251);


