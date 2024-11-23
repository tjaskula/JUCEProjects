#include "MainContentComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 700);
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
}