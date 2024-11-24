/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DSPTutorialAudioProcessor::DSPTutorialAudioProcessor()
        : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

DSPTutorialAudioProcessor::~DSPTutorialAudioProcessor()
{
}

//==============================================================================
const juce::String DSPTutorialAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DSPTutorialAudioProcessor::acceptsMidi() const
{
    return true;
}

bool DSPTutorialAudioProcessor::producesMidi() const
{
   return false;
}

bool DSPTutorialAudioProcessor::isMidiEffect() const
{
    return false;
}

double DSPTutorialAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DSPTutorialAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DSPTutorialAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DSPTutorialAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DSPTutorialAudioProcessor::getProgramName (int index)
{
    return {};
}

void DSPTutorialAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DSPTutorialAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    audioEngine.prepare ({ sampleRate, (juce::uint32) samplesPerBlock, 2 });
    midiMessageCollector.reset (sampleRate);
}

void DSPTutorialAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool DSPTutorialAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{

    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void DSPTutorialAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    midiMessageCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    audioEngine.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
    scopeDataCollector.process (buffer.getReadPointer (0), (size_t) buffer.getNumSamples());
}

//==============================================================================
bool DSPTutorialAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DSPTutorialAudioProcessor::createEditor()
{
    return new DSPTutorialAudioProcessorEditor (*this);
}

//==============================================================================
void DSPTutorialAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DSPTutorialAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DSPTutorialAudioProcessor();
}
