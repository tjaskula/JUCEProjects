#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    cachedBgColor = processorRef.bgColor->get();
    setSize (400, 300);

    startTimerHz(20);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    AudioPluginAudioProcessor::UpdateAutomatableParameter(processorRef.shouldPlaySound, false);
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    update();
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).interpolatedWith(Colours::red, cachedBgColor));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void AudioPluginAudioProcessorEditor::mouseUp(const juce::MouseEvent &e)
{
    AudioPluginAudioProcessor::UpdateAutomatableParameter(processorRef.shouldPlaySound, !processorRef.shouldPlaySound->get());
}

void AudioPluginAudioProcessorEditor::mouseDown(const juce::MouseEvent &e)
{
    //processorRef.shouldPlaySound = true;
    lastClickPos = e.getPosition();
}

void AudioPluginAudioProcessorEditor::mouseDrag(const juce::MouseEvent &e)
{
    auto clickPos = e.getPosition();

    DBG( clickPos.toString() );

    auto difY = jmap((double)clickPos.y, 0.0, (double)getHeight(), 1.0, 0.0);

    DBG( "difY: " << difY);

    AudioPluginAudioProcessor::UpdateAutomatableParameter(processorRef.bgColor, difY);
    update();
}

void AudioPluginAudioProcessorEditor::update()
{
    cachedBgColor = processorRef.bgColor->get();
    repaint();
}