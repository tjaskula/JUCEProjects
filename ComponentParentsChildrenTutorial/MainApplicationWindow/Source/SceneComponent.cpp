#include "SceneComponent.h"

//==============================================================================
SceneComponent::SceneComponent()
{
    addAndMakeVisible (floor);
    addAndMakeVisible (house);
    addAndMakeVisible (smallHouse);
    addAndMakeVisible (sun);
}

SceneComponent::~SceneComponent()
{

}

//==============================================================================
void SceneComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::lightblue);
}

void SceneComponent::resized()
{
    // This is called when the SceneComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    floor     .setBounds (10, 297, 580, 5);
    house     .setBounds (300, 70, 200, 220);
    smallHouse.setBounds (50,  50, 50,  50); // [9]
    sun       .setBounds (530, 10, 60,  60);
}