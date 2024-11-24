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
    }

private:
    //==============================================================================
    void renderNextSubBlock (juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples) override
    {
        MPESynthesiser::renderNextSubBlock (outputAudio, startSample, numSamples);
    }
};