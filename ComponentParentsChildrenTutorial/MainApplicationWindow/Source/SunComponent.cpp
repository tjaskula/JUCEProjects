#include "SunComponent.h"

//==============================================================================
SunComponent::SunComponent()
{
    setSize (600, 700);
}

SunComponent::~SunComponent()
{

}

//==============================================================================
void SunComponent::paint (juce::Graphics& g)
{
}

void SunComponent::resized()
{
    // This is called when the SunComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}