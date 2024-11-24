#pragma once

#include <JuceHeader.h>
#include "Voice.h"

class AudioEngine  : public juce::MPESynthesiser
{
public:
    static constexpr auto maxNumVoices = 4;

    //==============================================================================
    AudioEngine()
    {
        for (auto i = 0; i < maxNumVoices; ++i)
            addVoice (new Voice);

        setVoiceStealingEnabled (true);
    }

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec) noexcept
    {
        setCurrentPlaybackSampleRate (spec.sampleRate);

        for (auto* v : voices)
            dynamic_cast<Voice*> (v)->prepare (spec);

        fxChain.prepare (spec);
    }

private:
    //==============================================================================
    void renderNextSubBlock (juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples) override
    {
        MPESynthesiser::renderNextSubBlock (outputAudio, startSample, numSamples);

        auto block = juce::dsp::AudioBlock<float> (outputAudio);
        auto blockToUse = block.getSubBlock ((size_t) startSample, (size_t) numSamples);
        auto contextToUse = juce::dsp::ProcessContextReplacing<float> (blockToUse);
        fxChain.process (contextToUse);
    }

    enum
    {
        reverbIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Reverb> fxChain;
};