#include "WallComponent.h"

//==============================================================================
WallComponent::WallComponent()
{
}

WallComponent::~WallComponent()
{

}

//==============================================================================
void WallComponent::paint (juce::Graphics& g)
{
    g.fillCheckerBoard (getLocalBounds().toFloat(), 30, 10,
                        juce::Colours::sandybrown, juce::Colours::saddlebrown);
}

void WallComponent::resized()
{
    // This is called when the WallComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}