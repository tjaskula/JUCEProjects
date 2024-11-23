#include "SunComponent.h"

//==============================================================================
SunComponent::SunComponent()
{
}

SunComponent::~SunComponent()
{

}

//==============================================================================
void SunComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::yellow);

    auto lineThickness = 3.0f;
    g.drawEllipse (lineThickness * 0.5f,
                   lineThickness * 0.5f,
                   (float) getWidth()  - lineThickness * 2,
                   (float) getHeight() - lineThickness * 2,
                   lineThickness);
}

void SunComponent::resized()
{
    // This is called when the SunComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}