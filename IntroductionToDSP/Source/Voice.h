#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>
#include "CustomOscillator.h"

class Voice  : public juce::MPESynthesiserVoice
{
public:
    Voice()
    {
        auto& masterGain = processorChain.get<masterGainIndex>();
        masterGain.setGainLinear (0.7f);
    }

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        tempBlock = juce::dsp::AudioBlock<float> (heapBlock, spec.numChannels, spec.maximumBlockSize);
        processorChain.prepare (spec);
    }

    //==============================================================================
    void noteStarted() override
    {
        auto velocity = getCurrentlyPlayingNote().noteOnVelocity.asUnsignedFloat();
        auto freqHz = (float) getCurrentlyPlayingNote().getFrequencyInHertz();

        processorChain.get<osc1Index>().setFrequency (freqHz, true);
        processorChain.get<osc1Index>().setLevel (velocity);
    }

    //==============================================================================
    void notePitchbendChanged() override
    {
        auto freqHz = (float) getCurrentlyPlayingNote().getFrequencyInHertz();
        processorChain.get<osc1Index>().setFrequency (freqHz);
    }

    //==============================================================================
    void noteStopped (bool) override
    {
        clearCurrentNote();
    }

    //==============================================================================
    void notePressureChanged() override {}
    void noteTimbreChanged()   override {}
    void noteKeyStateChanged() override {}

    //==============================================================================
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
    {
        auto block = tempBlock.getSubBlock (0, (size_t) numSamples);
        block.clear();
        juce::dsp::ProcessContextReplacing<float> context (block);
        processorChain.process (context);

        juce::dsp::AudioBlock<float> (outputBuffer)
                .getSubBlock ((size_t) startSample, (size_t) numSamples)
                .add (tempBlock);
    }

private:
    //==============================================================================
    juce::HeapBlock<char> heapBlock;
    juce::dsp::AudioBlock<float> tempBlock;

    enum
    {
        osc1Index,
        masterGainIndex
    };

    juce::dsp::ProcessorChain<CustomOscillator<float>, juce::dsp::Gain<float>> processorChain;

    static constexpr size_t lfoUpdateRate = 100;
};