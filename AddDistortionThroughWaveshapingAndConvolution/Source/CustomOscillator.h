#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>

template <typename Type>
class CustomOscillator
{
public:
    //==============================================================================
    CustomOscillator()
    {
//        auto& osc = processorChain.template get<oscIndex>();
//        osc.initialise ([] (Type x) { return std::sin (x); }, 128);

        // sawtooth
        auto& osc = processorChain.template get<oscIndex>();
        osc.initialise ([] (Type x)
                        {
                            return juce::jmap (x,
                                               Type (-juce::MathConstants<double>::pi),
                                               Type (juce::MathConstants<double>::pi),
                                               Type (-1),
                                               Type (1));
                        }, 2);
    }

    //==============================================================================
    void setFrequency (Type newValue, bool force = false)
    {
        auto& osc = processorChain.template get<oscIndex>();
        osc.setFrequency (newValue, force);
    }

    //==============================================================================
    void setLevel (Type newValue)
    {
        auto& gain = processorChain.template get<gainIndex>();
        gain.setGainLinear (newValue);
    }

    //==============================================================================
    void reset() noexcept
    {
        processorChain.reset();
    }

    //==============================================================================
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        processorChain.process (context);
    }

    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {
        processorChain.prepare (spec);
    }

private:
    //==============================================================================
    enum
    {
        oscIndex,
        gainIndex   // [2]
    };

    juce::dsp::ProcessorChain<juce::dsp::Oscillator<Type>, juce::dsp::Gain<Type>> processorChain; // [1]
};