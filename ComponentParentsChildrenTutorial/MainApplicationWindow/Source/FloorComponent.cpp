#include "FloorComponent.h"

//==============================================================================
FloorComponent::FloorComponent()
{
    setSize (600, 700);
}

FloorComponent::~FloorComponent()
{

}

//==============================================================================
void FloorComponent::paint (juce::Graphics& g)
{
}

void FloorComponent::resized()
{
    // This is called when the FloorComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}