/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
TutorialProcessor::TutorialProcessor()
        : parameters (*this, nullptr, juce::Identifier ("APVTSTutorial"),
                      {
                              std::make_unique<juce::AudioParameterFloat> ("gain",            // parameterID
                                                                           "Gain",            // parameter name
                                                                           0.0f,              // minimum value
                                                                           1.0f,              // maximum value
                                                                           0.5f),             // default value
                              std::make_unique<juce::AudioParameterBool> ("invertPhase",      // parameterID
                                                                          "Invert Phase",     // parameter name
                                                                          false)              // default value
                      })
{
    phaseParameter = parameters.getRawParameterValue ("invertPhase");
    gainParameter  = parameters.getRawParameterValue ("gain");
}

TutorialProcessor::~TutorialProcessor()
{
}

//==============================================================================
const juce::String TutorialProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TutorialProcessor::acceptsMidi() const
{
    return true;
}

bool TutorialProcessor::producesMidi() const
{
   return false;
}

bool TutorialProcessor::isMidiEffect() const
{
    return false;
}

double TutorialProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TutorialProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TutorialProcessor::getCurrentProgram()
{
    return 0;
}

void TutorialProcessor::setCurrentProgram (int index)
{
}

const juce::String TutorialProcessor::getProgramName (int index)
{
    return {};
}

void TutorialProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TutorialProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    auto phase = *phaseParameter < 0.5f ? 1.0f : -1.0f;
    previousGain = *gainParameter * phase;
}

void TutorialProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool TutorialProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{

    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
}

void TutorialProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    auto phase = *phaseParameter < 0.5f ? 1.0f : -1.0f;
    auto currentGain = *gainParameter * phase;

    if (juce::approximatelyEqual (currentGain, previousGain))
    {
        buffer.applyGain (currentGain);
    }
    else
    {
        buffer.applyGainRamp (0, buffer.getNumSamples(), previousGain, currentGain);
        previousGain = currentGain;
    }
}

//==============================================================================
bool TutorialProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TutorialProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void TutorialProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void TutorialProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TutorialProcessor();
}
