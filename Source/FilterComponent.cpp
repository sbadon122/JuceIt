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

//==============================================================================
FilterComponent::FilterComponent() :
xPosition(266.0f), yPosition(58.0f)
{
    
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    const float filterHeight = 160.0f;
    //Paint Gradient Background
    const float ratio = juce::jmap(yPosition, 0.f, 354.0f, 1.f,-2.7f);
    const float ratio2 = juce::jmap(yPosition, 0.f, 354.0f, 0.f,1.5f);
    juce::ColourGradient borderGradient(JuceItFilterBackground_Colour2,0,0,JuceItFilterBackground_Colour1,0, getHeight()*.75, false);
    g.setGradientFill(borderGradient);
    g.fillAll();
    
    
    //Path Filter Variables
    juce::Path filterPath;
    juce::PathStrokeType stroke (6.0f, juce::PathStrokeType::curved, juce::PathStrokeType::EndCapStyle::rounded);
    juce::Point<float> startingPoint(0.f, getHeight());
    juce::Point<float> startingOutlinePoint(-6.f, filterHeight);
    juce::Point<float> midPoint0(xPosition-80.0,  filterHeight);
    juce::Point<float> midPoint1(xPosition-40.0*ratio2,  filterHeight);
    juce::Point<float> midPoint2(xPosition+(60*ratio2), filterHeight-(ratio*100));
    juce::Point<float> resonancePoint(xPosition, yPosition-20);
    juce::Point<float> endingOutlinePoint(xPosition+80.0f, getHeight()+5);
    
    //Fill Filter background
    juce::ColourGradient filterFillGradient(JuceItFilterFillBackground_Colour1,0,filterHeight,JuceItFilterFillBackground_Colour2,0, getHeight(), false);
    filterPath.startNewSubPath (startingPoint);
    filterPath.lineTo(startingOutlinePoint);;
    filterPath.cubicTo(midPoint0, midPoint1, resonancePoint);
    filterPath.quadraticTo(midPoint2, endingOutlinePoint);
    filterPath.closeSubPath();
    
    g.setGradientFill(filterFillGradient);
    g.fillPath(filterPath);
    
    //Draw Outline
    filterPath.clear();
    filterPath.startNewSubPath(startingOutlinePoint);
    filterPath.cubicTo(midPoint0, midPoint1, resonancePoint);
    filterPath.quadraticTo(midPoint2, endingOutlinePoint);
    
    g.setColour(juce::Colours::white);
    g.strokePath(filterPath.createPathWithRoundedCorners(2000.0f),stroke);
    
    
}

void FilterComponent::resized()
{
    
}

void FilterComponent::mouseDown(const juce::MouseEvent &event)
{
   
    xPosition = event.getMouseDownX();
    yPosition = event.getMouseDownY();
    if(xPosition>getWidth())
    {
        xPosition = getWidth();
    }
    else if(xPosition<0)
    {
        xPosition=0;
    }
    
    if(yPosition>216)
    {
        yPosition = 216;
    }
    else if(yPosition<0)
    {
        yPosition=0;
    }
    repaint();
}

void FilterComponent::mouseDrag(const juce::MouseEvent &event)
{
    xPosition = event.getPosition().getX();
    yPosition = event.getPosition().getY();
    std::cout<< yPosition << std::endl;
    if(xPosition>getWidth())
    {
        xPosition = getWidth();
    }
    else if(xPosition<0)
    {
        xPosition=0;
    }
    
    if(yPosition>216)
    {
        yPosition = 216;
    }
    else if(yPosition<2)
    {
        yPosition=2;
    }
    
    repaint();
}
