/*
 ==============================================================================
 
 FilterComponent.cpp
 Created: 8 Jul 2020 8:46:46pm
 Author:  Sebastian Badon
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "FilterComponent.h"
#include "JuceItInterfaceDefines.h"
#include "JuceItParameters.h"


//==============================================================================
FilterComponent::FilterComponent(JuceItAudioProcessor* inProcessor) :
jProcessor(inProcessor)
{
    auto& params = jProcessor->parameters;
    frequency = params.getRawParameterValue(JuceItParameterID[jParameter_Frequency]);
    resonance = params.getRawParameterValue(JuceItParameterID[jParameter_Resonance]);
    
    startTimer(10);
    
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    //Paint Component Background
    paintComponentBackground(g);
    const float xPosition = juce::jmap((float)*frequency, FILTER_COORDINATES_OFFSET, MAX_X_COORDINATE_POSITION-10);
    const float yPosition = juce::jmap((float)*resonance, MAX_Y_COORDINATE_POSITION, FILTER_COORDINATES_OFFSET);
    
    
    //Ratio used to control characteristics filter movement
    const float ratio =  juce::jmap(yPosition, 0.f, (float)JUCEIT_FILTER_BOUNDS, 0.f, 0.75f);
    
    //Path variables
    juce::Path filterPath;
    juce::PathStrokeType stroke (6.0f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded);
    const float midPointXPosition = xPosition+80*ratio < MAX_X_COORDINATE_POSITION ? xPosition+80*ratio : MAX_X_COORDINATE_POSITION;
    const float endPointXPosition = xPosition+60.0f < MAX_X_COORDINATE_POSITION ? xPosition+60.0f : MAX_X_COORDINATE_POSITION;
    const float midPoint2XPosition = xPosition+20*ratio < MAX_X_COORDINATE_POSITION ?  xPosition+20*ratio : MAX_X_COORDINATE_POSITION;
    
    //Points for Filter
    juce::Point<float> startingPoint(0.f, getHeight());
    juce::Point<float> startingOutlinePoint(-6.f, FILTER_HEIGHT);
    juce::Point<float> startingCurvePoint(xPosition-80.f, FILTER_HEIGHT);
    juce::Point<float> midPoint1(xPosition, FILTER_HEIGHT);
    juce::Point<float> midPoint2(midPoint2XPosition, yPosition+30*ratio);
    juce::Point<float> midPoint3(midPointXPosition,  (yPosition+getHeight())/2.0);
    juce::Point<float> resonancePoint(xPosition, yPosition);
    juce::Point<float> endingOutlinePoint(endPointXPosition, getHeight()+1);
    
    //Filter Path background
    juce::ColourGradient filterFillGradient(JuceItFilterFillBackground_Colour1,0,FILTER_HEIGHT,JuceItFilterFillBackground_Colour2,0, getHeight(), false);
    filterPath.startNewSubPath (startingPoint);
    filterPath.lineTo(startingOutlinePoint);
    filterPath.lineTo(startingCurvePoint);
    filterPath.cubicTo(midPoint1, resonancePoint, midPoint2);
    filterPath.quadraticTo(midPoint3, endingOutlinePoint);
    filterPath.closeSubPath();
    
    //Fill Filter Path Background
    g.setGradientFill(filterFillGradient);
    g.fillPath(filterPath);
    
    //Draw Outline for Filter
    filterPath.clear();
    filterPath.startNewSubPath(startingOutlinePoint);
    filterPath.lineTo(startingCurvePoint);
    filterPath.cubicTo(midPoint1, resonancePoint, midPoint2);
    filterPath.quadraticTo(midPoint3, endingOutlinePoint);
    
    //Fill Outline for Filter
    g.setColour(juce::Colours::white);
    g.strokePath(filterPath,stroke);
    

}

void FilterComponent::resized()
{
    
}

void FilterComponent::mouseDown(const juce::MouseEvent& event)
{
    setMousePosition(event);
}

void FilterComponent::mouseDrag(const juce::MouseEvent& event)
{
    setMousePosition(event);
}

/**
 After a desired mouse event, we get the mouse coorindates and put them within the bounds
 of the possible area the filter can move in. We then map the the coordinates and update the
 frequency and 
 */
void FilterComponent::setMousePosition(const juce::MouseEvent& event)
{
    float xPosition = event.getPosition().getX();
    float yPosition = event.getPosition().getY();
    
    if(xPosition>MAX_X_COORDINATE_POSITION)
    {
        xPosition = MAX_X_COORDINATE_POSITION;
    }
    else if(xPosition<FILTER_COORDINATES_OFFSET)
    {
        xPosition=FILTER_COORDINATES_OFFSET;
    }
    
    if(yPosition>MAX_Y_COORDINATE_POSITION)
    {
        yPosition = MAX_Y_COORDINATE_POSITION;
    }
    else if(yPosition<FILTER_COORDINATES_OFFSET)
    {
        yPosition=FILTER_COORDINATES_OFFSET;
    }
    
    *frequency = juce::jmap(xPosition,
                            FILTER_COORDINATES_OFFSET,
                            MAX_X_COORDINATE_POSITION,
                            0.f,
                            1.f);
    
    *resonance = juce::jmap(yPosition,
                            MAX_Y_COORDINATE_POSITION,
                            FILTER_COORDINATES_OFFSET,
                            0.f,
                            1.f);
    
}

/**
 Originally I added a repaint whenever the mouse position was moved but ended using
 timerCallback to account for other state changes from events like automation. I'm curious in trying
 in adding a AudioProcessor::Listener to catch any value changes to the processor and calling repaint using one its methods.
 */
void FilterComponent::timerCallback()
{
    repaint();
}

void FilterComponent::paintComponentBackground(juce::Graphics& g)
{
    //Paint Gradient Background
    juce::ColourGradient backgroundGradient(JuceItFilterBackground_Colour2,0,0,JuceItFilterBackground_Colour1,0, getHeight()*.75, false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();
}



