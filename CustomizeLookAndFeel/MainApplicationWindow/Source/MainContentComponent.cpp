#include "MainContentComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
    setLookAndFeel (&otherLookAndFeel); // customized look and feel
    dial1.setSliderStyle (juce::Slider::Rotary);
    dial1.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible (dial1);

    dial2.setSliderStyle (juce::Slider::Rotary);
    dial2.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible (dial2);

    // getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::red);
    // or
    //otherLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colours::red);
    // dial1.setLookAndFeel (&otherLookAndFeel);

    button1.setButtonText ("Button 1");
    addAndMakeVisible (button1);

    button2.setButtonText ("Button 2");
    addAndMakeVisible (button2);

    setSize (300, 200);
}

MainContentComponent::~MainContentComponent()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void MainContentComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    // scene.setBounds (0, 0, getWidth(), getHeight()); or
    auto border = 4;

    auto area = getLocalBounds();

    auto dialArea = area.removeFromTop (area.getHeight() / 2);
    dial1.setBounds (dialArea.removeFromLeft (dialArea.getWidth() / 2).reduced (border));
    dial2.setBounds (dialArea.reduced (border));

    auto buttonHeight = 30;

    button1.setBounds (area.removeFromTop (buttonHeight).reduced (border));
    button2.setBounds (area.removeFromTop (buttonHeight).reduced (border));
}