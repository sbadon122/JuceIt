/*
  ==============================================================================

    FilterComponent.h
    Created: 8 Jul 2020 8:46:46pm
    Author:  Sebastian Badon

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent();
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown  (const juce::MouseEvent &event)  override;
    void mouseDrag  (const juce::MouseEvent &event)  override;
    

private:
    void fillFilterBackground(juce::Graphics&, juce::Point<float> );
    float xPosition, yPosition;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
