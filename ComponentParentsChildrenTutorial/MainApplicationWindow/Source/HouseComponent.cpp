#include "HouseComponent.h"

//==============================================================================
HouseComponent::HouseComponent()
{
    addAndMakeVisible (wall);
    addAndMakeVisible (roof);
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
    auto separation = juce::jlimit (2, 10, getHeight() / 20);                                           // [1]

    roof.setBounds (0, 0, getWidth(), (int) (getHeight() * 0.2) - separation / 2);                                          // [2]
    wall.setBounds (0, (int) (getHeight() * 0.20) + separation / 2, getWidth(), (int) (getHeight() * 0.80) - separation);   // [3]
}