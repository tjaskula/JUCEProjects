/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DSPTutorialAudioProcessorEditor::DSPTutorialAudioProcessorEditor (DSPTutorialAudioProcessor& p)
    : AudioProcessorEditor (&p), dspProcessor (p), scopeComponent (dspProcessor.getAudioBufferQueue())
{
    addAndMakeVisible (midiKeyboardComponent);
    addAndMakeVisible (scopeComponent);

    setSize (400, 300);

    auto area = getLocalBounds();
    scopeComponent.setTopLeftPosition (0, 80);
    scopeComponent.setSize (area.getWidth(), area.getHeight() - 100);

    midiKeyboardComponent.setMidiChannel (2);
    midiKeyboardState.addListener (&dspProcessor.getMidiMessageCollector());
}

DSPTutorialAudioProcessorEditor::~DSPTutorialAudioProcessorEditor()
{
    midiKeyboardState.removeListener (&dspProcessor.getMidiMessageCollector());
}

//==============================================================================
void DSPTutorialAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void DSPTutorialAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    midiKeyboardComponent.setBounds (area.removeFromTop (80).reduced (8));
}