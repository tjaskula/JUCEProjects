#include "RoofComponent.h"

//==============================================================================
RoofComponent::RoofComponent()
{
}

RoofComponent::~RoofComponent()
{

}

//==============================================================================
void RoofComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::red);

    juce::Path roof;
    roof.addTriangle (0.0f, (float) getHeight(), (float) getWidth(), (float) getHeight(), (float) getWidth() / 2.0f, 0.0f);
    g.fillPath (roof);
}

void RoofComponent::resized()
{
    // This is called when the RoofComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}