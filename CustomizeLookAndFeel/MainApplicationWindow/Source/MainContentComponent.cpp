#include "MainContentComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
    addAndMakeVisible (scene);
    setSize (600, 400);
}

MainContentComponent::~MainContentComponent()
{

}

//==============================================================================
void MainContentComponent::paint (juce::Graphics& g)
{
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    // scene.setBounds (0, 0, getWidth(), getHeight()); or
}