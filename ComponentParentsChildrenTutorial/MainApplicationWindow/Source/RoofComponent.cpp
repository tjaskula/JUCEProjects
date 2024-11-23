#include "RoofComponent.h"

//==============================================================================
RoofComponent::RoofComponent()
{
    setSize (600, 700);
}

RoofComponent::~RoofComponent()
{

}

//==============================================================================
void RoofComponent::paint (juce::Graphics& g)
{
}

void RoofComponent::resized()
{
    // This is called when the RoofComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}