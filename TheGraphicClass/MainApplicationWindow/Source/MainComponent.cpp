#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 700);
}

MainComponent::~MainComponent()
{

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::lightblue);

    g.setColour (juce::Colours::darkblue);
    g.setFont (juce::Font ("Times New Roman", 20.0f, juce::Font::italic));
    g.drawText ("Hello, World!", 20, 40, 200, 40, juce::Justification::centred, true);

    g.setColour (juce::Colours::green);
    g.drawLine (10, 300, 590, 300, 5);

    juce::Rectangle<float> house (300, 120, 200, 170);
    g.fillCheckerBoard (house, 30, 10, juce::Colours::sandybrown, juce::Colours::saddlebrown);

    g.setColour (juce::Colours::yellow);
    g.drawEllipse (getWidth() - 70, 10, 60, 60, 3);

    g.setColour (juce::Colours::red);

    Path roof;
    roof.addTriangle (300, 110, 500, 110, 400, 70);
    g.fillPath (roof);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}