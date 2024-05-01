#pragma once

//#include "PluginProcessor.h"

struct AudioPluginAudioProcessor;

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Point<int> lastClickPos;
    AudioPluginAudioProcessor& processorRef;
    float cachedBgColor = 0.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
