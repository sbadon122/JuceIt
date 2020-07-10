/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "JuceItInterfaceDefines.h"

//==============================================================================
JuceItAudioProcessorEditor::JuceItAudioProcessorEditor (JuceItAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (596, 596);
    mFilterComponent = std::make_unique<FilterComponent>();
    addAndMakeVisible(mFilterComponent.get());
    mFilterComponent->setBounds(JUCEIT_PADDING, JUCEIT_PADDING, JUCEIT_FILTER_BOUNDS, JUCEIT_FILTER_BOUNDS);
}

JuceItAudioProcessorEditor::~JuceItAudioProcessorEditor()
{
}

//==============================================================================
void JuceItAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient borderGradient(JuceItBorder_Colour1,getWidth()/2,0,JuceItBorder_Colour2,0,getHeight()*0.75f, true);
    g.setGradientFill(borderGradient);
    g.fillAll();
    
}

void JuceItAudioProcessorEditor::resized()
{
    
}
