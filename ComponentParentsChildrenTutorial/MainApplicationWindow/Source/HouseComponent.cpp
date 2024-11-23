#include "HouseComponent.h"

//==============================================================================
HouseComponent::HouseComponent()
{
    setSize (600, 700);
}

HouseComponent::~HouseComponent()
{

}

//==============================================================================
void HouseComponent::paint (juce::Graphics& g)
{
}

void HouseComponent::resized()
{
    // This is called when the HouseComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}