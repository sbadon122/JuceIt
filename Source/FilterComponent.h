/*
  ==============================================================================

    FilterComponent.h
    Created: 8 Jul 2020 8:46:46pm
    Author:  Sebastian Badon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class FilterComponent  : public juce::Component, public juce::Timer
{
public:
    FilterComponent(JuceItAudioProcessor* inProcessor);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown  (const juce::MouseEvent& event)  override;
    void mouseDrag  (const juce::MouseEvent& event)  override;
    void timerCallback() override;

private:
    void setMousePosition(const juce::MouseEvent& event);
    void paintComponentBackground(juce::Graphics& g);
    std::atomic<float>* frequency;
    std::atomic<float>* resonance;
    JuceItAudioProcessor* jProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
