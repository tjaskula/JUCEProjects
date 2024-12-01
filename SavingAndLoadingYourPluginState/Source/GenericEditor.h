#pragma once

#include <JuceHeader.h>

//==============================================================================
class GenericEditor : public juce::AudioProcessorEditor
{
public:
    enum
    {
        paramControlHeight = 40,
        paramLabelWidth    = 80,
        paramSliderWidth   = 300
    };

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    GenericEditor (juce::AudioProcessor& parent, juce::AudioProcessorValueTreeState& vts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label gainLabel;
    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainAttachment;

    juce::ToggleButton invertButton;
    std::unique_ptr<ButtonAttachment> invertAttachment;
};