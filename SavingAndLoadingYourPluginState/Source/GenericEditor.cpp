#pragma once

#include "GenericEditor.h"

GenericEditor::GenericEditor (juce::AudioProcessor& parent, juce::AudioProcessorValueTreeState& vts)
                    : AudioProcessorEditor (parent), valueTreeState (vts)
{
    gainLabel.setText ("Gain", juce::dontSendNotification);
    addAndMakeVisible (gainLabel);

    addAndMakeVisible (gainSlider);
    gainAttachment.reset (new SliderAttachment (valueTreeState, "gain", gainSlider));

    invertButton.setButtonText ("Invert Phase");
    addAndMakeVisible (invertButton);
    invertAttachment.reset (new ButtonAttachment (valueTreeState, "invertPhase", invertButton));

    setSize (paramSliderWidth + paramLabelWidth, juce::jmax (100, paramControlHeight * 2));
}

void GenericEditor::resized()
{
    auto r = getLocalBounds();

    auto gainRect = r.removeFromTop (paramControlHeight);
    gainLabel .setBounds (gainRect.removeFromLeft (paramLabelWidth));
    gainSlider.setBounds (gainRect);

    invertButton.setBounds (r.removeFromTop (paramControlHeight));
}

void GenericEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}
