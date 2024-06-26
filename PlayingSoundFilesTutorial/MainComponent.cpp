#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : state(Stopped)
{
    addAndMakeVisible (&openButton);
    openButton.setButtonText ("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible (&playButton);
    playButton.setButtonText ("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour (juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled (false);

    addAndMakeVisible (&stopButton);
    stopButton.setButtonText ("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled (false);

    addAndMakeVisible (&loopingToggle);
    loopingToggle.setButtonText ("Loop");
    loopingToggle.onClick = [this] { loopButtonChanged(); };

    addAndMakeVisible (&currentPositionLabel);
    currentPositionLabel.setText ("Stopped", juce::dontSendNotification);

    setSize (300, 200);

    formatManager.registerBasicFormats();

    transportSource.addChangeListener (this);

    setAudioChannels (2, 2);
    startTimer (20);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    openButton.setBounds (10, 10, getWidth() - 20, 20);
    playButton.setBounds (10, 40, getWidth() - 20, 20);
    stopButton.setBounds (10, 70, getWidth() - 20, 20);
    loopingToggle.setBounds (10, 100, getWidth() - 20, 20);
    currentPositionLabel.setBounds (10, 130, getWidth() - 20, 20);
}

void MainComponent::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState (Playing);
        else if ((state == Stopping) || (state == Playing))
            changeState (Stopped);
        else if (Pausing == state)
            changeState (Paused);
    }
}

void MainComponent::timerCallback()
{
    if (transportSource.isPlaying())
    {
        juce::RelativeTime position (transportSource.getCurrentPosition());

        auto minutes = ((int) position.inMinutes()) % 60;
        auto seconds = ((int) position.inSeconds()) % 60;
        auto millis  = ((int) position.inMilliseconds()) % 1000;

        auto positionString = juce::String::formatted ("%02d:%02d:%03d", minutes, seconds, millis);

        currentPositionLabel.setText (positionString, juce::dontSendNotification);
    }
    else
    {
        currentPositionLabel.setText ("Stopped", juce::dontSendNotification);
    }
}

void MainComponent::updateLoopState (bool shouldLoop)
{
    if (readerSource != nullptr)
        readerSource->setLooping (shouldLoop);
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transportSource.getNextAudioBlock (bufferToFill);
}

//==============================================================================
void MainComponent::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser> ("Select a Wave file to play...",
                                                   juce::File{},
                                                   "*.wav");
    auto chooserFlags = juce::FileBrowserComponent::openMode
                        | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
    {
        auto file = fc.getResult();

        if (file != juce::File{})
        {
            auto* reader = formatManager.createReaderFor (file);

            if (reader != nullptr)
            {
                auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
                transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                readerSource.reset (newSource.release());
            }
        }
    });
}

void MainComponent::playButtonClicked()
{
    if ((state == Stopped) || (state == Paused))
        changeState (Starting);
    else if (state == Playing)
        changeState (Pausing);
}

void MainComponent::stopButtonClicked()
{
    if (state == Paused)
        changeState (Stopped);
    else
        changeState (Stopping);
}

void MainComponent::loopButtonChanged()
{
    updateLoopState (loopingToggle.getToggleState());
}

//==============================================================================
void MainComponent::changeState (MainComponent::TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
            case Stopped:
                stopButton.setEnabled (false);
                playButton.setEnabled (true);
                transportSource.setPosition (0.0);
                break;

            case Starting:
                playButton.setEnabled (false);
                transportSource.start();
                break;

            case Playing:
                playButton.setButtonText ("Pause");
                stopButton.setButtonText ("Stop");
                playButton.setEnabled (true);
                stopButton.setEnabled (true);
                break;

            case Pausing:
                transportSource.stop();
                break;

            case Paused:
                playButton.setButtonText ("Resume");
                stopButton.setButtonText ("Return to Zero");
                break;

            case Stopping:
                transportSource.stop();
                break;
        }
    }
}