#include "FloorComponent.h"

//==============================================================================
FloorComponent::FloorComponent()
{
}

FloorComponent::~FloorComponent()
{

}

//==============================================================================
void FloorComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::green);
    g.drawLine (0.0f, (float) getHeight() / 2.0f, (float) getWidth(), (float) getHeight() / 2.0f, 5.0f);
}

void FloorComponent::resized()
{
    // This is called when the FloorComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}