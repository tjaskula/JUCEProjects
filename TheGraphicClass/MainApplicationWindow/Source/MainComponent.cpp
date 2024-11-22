#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (400, 300);
}

MainComponent::~MainComponent()
{

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (backgroundColor);

    g.setColour (juce::Colours::darkblue);
    g.setFont (20.0f);
    g.drawText (currentSizeAsString, getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    currentSizeAsString = juce::String (getWidth()) + " x " + juce::String (getHeight());

    // Change the background color randomly every time the component is resized
    backgroundColor = juce::Colour::fromRGB (juce::Random::getSystemRandom().nextInt (256),
                                             juce::Random::getSystemRandom().nextInt (256),
                                             juce::Random::getSystemRandom().nextInt (256));

    repaint(); // Trigger a repaint to reflect the new color
}