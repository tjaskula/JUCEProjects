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

        auto& filter = processorChain.get<filterIndex>();
        filter.setCutoffFrequencyHz (1000.0f);
        filter.setResonance (0.7f);

        lfo.initialise ([] (float x) { return std::sin(x); }, 128);
        lfo.setFrequency (3.0f);
    }

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        tempBlock = juce::dsp::AudioBlock<float> (heapBlock, spec.numChannels, spec.maximumBlockSize);
        processorChain.prepare (spec);

        lfo.prepare ({ spec.sampleRate / lfoUpdateRate, spec.maximumBlockSize, spec.numChannels });
    }

    //==============================================================================
    void noteStarted() override
    {
        auto velocity = getCurrentlyPlayingNote().noteOnVelocity.asUnsignedFloat();
        auto freqHz = (float) getCurrentlyPlayingNote().getFrequencyInHertz();

        processorChain.get<osc1Index>().setFrequency (freqHz, true);
        processorChain.get<osc1Index>().setLevel (velocity);

        processorChain.get<osc2Index>().setFrequency (freqHz * 1.01f, true);
        processorChain.get<osc2Index>().setLevel (velocity);
    }

    //==============================================================================
    void notePitchbendChanged() override
    {
        auto freqHz = (float) getCurrentlyPlayingNote().getFrequencyInHertz();
        processorChain.get<osc1Index>().setFrequency (freqHz);
        processorChain.get<osc2Index>().setFrequency (freqHz * 1.01f);
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
        auto output = tempBlock.getSubBlock (0, (size_t) numSamples);
        output.clear();

        for (size_t pos = 0; pos < (size_t) numSamples;)
        {
            auto max = juce::jmin ((size_t) numSamples - pos, lfoUpdateCounter);
            auto block = output.getSubBlock (pos, max);

            juce::dsp::ProcessContextReplacing<float> context (block);
            processorChain.process (context);

            pos += max;
            lfoUpdateCounter -= max;

            if (lfoUpdateCounter == 0)
            {
                lfoUpdateCounter = lfoUpdateRate;
                auto lfoOut = lfo.processSample (0.0f);                                 // [5]
                auto curoffFreqHz = juce::jmap (lfoOut, -1.0f, 1.0f, 100.0f, 2000.0f);  // [6]
                processorChain.get<filterIndex>().setCutoffFrequencyHz (curoffFreqHz);  // [7]
            }
        }

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
        osc2Index,
        filterIndex,
        masterGainIndex
    };

    juce::dsp::ProcessorChain<CustomOscillator<float>, CustomOscillator<float>,
            juce::dsp::LadderFilter<float>, juce::dsp::Gain<float>> processorChain;

    static constexpr size_t lfoUpdateRate = 100;
    size_t lfoUpdateCounter = lfoUpdateRate;
    juce::dsp::Oscillator<float> lfo;
};