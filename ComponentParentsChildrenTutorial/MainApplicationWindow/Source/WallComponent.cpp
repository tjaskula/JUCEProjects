#include "WallComponent.h"

//==============================================================================
WallComponent::WallComponent()
{
    setSize (600, 700);
}

WallComponent::~WallComponent()
{

}

//==============================================================================
void WallComponent::paint (juce::Graphics& g)
{
}

void WallComponent::resized()
{
    // This is called when the WallComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}