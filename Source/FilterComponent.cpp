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
    
    //Thread safe way of reading values
    frequency = params.getRawParameterValue(JuceItParameterID[jParameter_Frequency]);
    resonance = params.getRawParameterValue(JuceItParameterID[jParameter_Resonance]);
    
    //Setting this component to listen for parameter changes for repainting purposes
    params.addParameterListener(JuceItParameterID[jParameter_Frequency], this);
    params.addParameterListener(JuceItParameterID[jParameter_Resonance], this);
}

FilterComponent::~FilterComponent()
{
    //Don't forget to remove those listeners!
    auto& params = jProcessor->parameters;
    params.removeParameterListener(JuceItParameterID[jParameter_Frequency], this);
    params.removeParameterListener(JuceItParameterID[jParameter_Resonance], this);
}


void FilterComponent::paint (juce::Graphics& g)
{
    //Paint Component Background
    paintComponentBackground(g);
    
    //Map parameter values to coordinates in the filter space
    const float xPosition = juce::jmap((float)*frequency, MIN_X_COORDINATE_POSITION, MAX_X_COORDINATE_POSITION);
    const float yPosition = juce::jmap((float)*resonance, MAX_Y_COORDINATE_POSITION, MIN_Y_COORDINATE_POSITION);
    
    //Variable used to control characteristics of filter movement
    const float ratio =  juce::jmap(yPosition, 0.f, (float)JUCEIT_FILTER_BOUNDS, 0.f, 0.75f);
    
    //Path variables
    juce::Path filterPath;
    juce::PathStrokeType stroke (6.0f, juce::PathStrokeType::beveled, juce::PathStrokeType::EndCapStyle::rounded);
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
    juce::Point<float> endingOutlinePoint(endPointXPosition, getHeight()+2);
    
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
 of the possible area the filter can move in. We then jmap the coordinates and update the
 frequency and response parameters.
 */
void FilterComponent::setMousePosition(const juce::MouseEvent& event)
{
    //Prevent duplicate events. Concept was copied from slider event listeners
    if(lastMouseTime != event.eventTime){
        lastMouseTime = event.eventTime;
        
        //Get mouse position
        float xPosition = event.getPosition().getX();
        float yPosition = event.getPosition().getY();
        
        //Set the xPosition within the possible desired bounds of the component
        if(xPosition>MAX_X_COORDINATE_POSITION)
        {
            xPosition = MAX_X_COORDINATE_POSITION;
        }
        else if(xPosition<MIN_X_COORDINATE_POSITION)
        {
            xPosition=MIN_X_COORDINATE_POSITION;
        }
        
        //Set the yPosition within the possible desired bounds of the component
        if(yPosition>MAX_Y_COORDINATE_POSITION)
        {
            yPosition = MAX_Y_COORDINATE_POSITION;
        }
        else if(yPosition<MIN_Y_COORDINATE_POSITION)
        {
            yPosition=MIN_Y_COORDINATE_POSITION;
        }
        
        //Map the coordinates to values within the range of frequency
        float frequencyValueMap = juce::jmap(xPosition,
                                            MIN_X_COORDINATE_POSITION,
                                            MAX_X_COORDINATE_POSITION,
                                            JuceItParameterMinValue[jParameter_Frequency],
                                            JuceItParameterMaxValue[jParameter_Frequency]);
        
        //Map the coordinates to values within the range of Resonace
        float resonanceValueMap = juce::jmap(yPosition,
                                            MAX_Y_COORDINATE_POSITION,
                                            MIN_Y_COORDINATE_POSITION,
                                            JuceItParameterMinValue[jParameter_Resonance],
                                            JuceItParameterMaxValue[jParameter_Resonance]);
        
        //Update parameters
        auto& params = jProcessor->parameters;
        juce::Value freq = params.getParameterAsValue(JuceItParameterID[jParameter_Frequency]);
        juce::Value res = params.getParameterAsValue(JuceItParameterID[jParameter_Resonance]);
        freq.setValue(frequencyValueMap);
        res.setValue(resonanceValueMap);
        
    }

}

/**
 Repaint filter if Frequency or Resonance parameters change. Since there's a lot of callbacks that can occur,
 I use the MessageManager to call repaint safely on the message thread.
 */
void FilterComponent::parameterChanged (const String &parameterID, float newValue)
{
    if(parameterID == JuceItParameterID[jParameter_Frequency] ||
       parameterID == JuceItParameterID[jParameter_Resonance])
    {
        MessageManager::callAsync([this]{
            repaint();
        });
    }
}

/**
 Paints blue graident background behind filter component
 */
void FilterComponent::paintComponentBackground(juce::Graphics& g)
{
    //Paint Gradient Background
    juce::ColourGradient backgroundGradient(JuceItFilterBackground_Colour2,0,0,JuceItFilterBackground_Colour1,0, getHeight()*.75, false);
    g.setGradientFill(backgroundGradient);
    g.fillAll();
}



