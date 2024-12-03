#include "MainContentComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
        : startTime (juce::Time::getMillisecondCounterHiRes() * 0.001)
{
    addAndMakeVisible (bassDrumButton);
    bassDrumButton.setButtonText ("Bass Drum (36)");
    bassDrumButton.onClick = [this] { setNoteNumber (36); };

    addAndMakeVisible (snareDrumButton);
    snareDrumButton.setButtonText ("Snare Drum (38)");
    snareDrumButton.onClick = [this] { setNoteNumber (38); };

    addAndMakeVisible (closedHiHatButton);
    closedHiHatButton.setButtonText ("Closed HH (42)");
    closedHiHatButton.onClick = [this] { setNoteNumber (42); };

    addAndMakeVisible (openHiHatButton);
    openHiHatButton.setButtonText ("Open HH (46)");
    openHiHatButton.onClick = [this] { setNoteNumber (46); };

    addAndMakeVisible (volumeLabel);
    volumeLabel.setText ("Volume (CC7)", juce::dontSendNotification);

    addAndMakeVisible (volumeSlider);
    volumeSlider.setRange (0, 127, 1);
    volumeSlider.onValueChange = [this]
    {
        auto message = juce::MidiMessage::controllerEvent (10, 7, (int) volumeSlider.getValue());
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        addMessageToBuffer (message);
    };

    addAndMakeVisible (midiMessagesBox);
    midiMessagesBox.setMultiLine (true);
    midiMessagesBox.setReturnKeyStartsNewLine (true);
    midiMessagesBox.setReadOnly (true);
    midiMessagesBox.setScrollbarsShown (true);
    midiMessagesBox.setCaretVisible (false);
    midiMessagesBox.setPopupMenuEnabled (true);
    midiMessagesBox.setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x32ffffff));
    midiMessagesBox.setColour (juce::TextEditor::outlineColourId, juce::Colour (0x1c000000));
    midiMessagesBox.setColour (juce::TextEditor::shadowColourId, juce::Colour (0x16000000));

    setSize (800, 300);
    startTimer (1);
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
    auto halfWidth = getWidth() / 2;

    auto buttonsBounds = getLocalBounds().withWidth (halfWidth).reduced (10);

    bassDrumButton   .setBounds (buttonsBounds.getX(), 10,  buttonsBounds.getWidth(), 20);
    snareDrumButton  .setBounds (buttonsBounds.getX(), 40,  buttonsBounds.getWidth(), 20);
    closedHiHatButton.setBounds (buttonsBounds.getX(), 70,  buttonsBounds.getWidth(), 20);
    openHiHatButton  .setBounds (buttonsBounds.getX(), 100, buttonsBounds.getWidth(), 20);
    volumeLabel      .setBounds (buttonsBounds.getX(), 190, buttonsBounds.getWidth(), 20);
    volumeSlider     .setBounds (buttonsBounds.getX(), 220, buttonsBounds.getWidth(), 20);

    midiMessagesBox.setBounds (getLocalBounds().withWidth (halfWidth).withX (halfWidth).reduced (10));
}