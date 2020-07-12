/*
  ==============================================================================

    JuceItParameters.h
    Created: 10 Jul 2020 2:45:16pm
    Author:  Sebastian Badon

  ==============================================================================
*/

#pragma once
using namespace juce;

/**
    This header file serves as a means of tracking all parameters and its fields in the audio component.
 */

enum JuceItParameters {
    jParameter_Frequency = 0,
    jParameter_Resonance,
    jParameter_TotalParamNums
};

static String JuceItParameterID [jParameter_TotalParamNums] =
{
    "frequency",
    "resonance",
};

static String JuceItParameterLabel [jParameter_TotalParamNums] =
{
    "Frequency",
    "Resonance",
};

static float JuceItParameterDefaultValue [jParameter_TotalParamNums] =
{
    0.75f,
    0.65f,
};


static float JuceItParameterMinValue [jParameter_TotalParamNums] =
{
    0.0f,
    0.0f,
};

static float JuceItParameterMaxValue [jParameter_TotalParamNums] =
{
    1.0f,
    1.0f,
};
