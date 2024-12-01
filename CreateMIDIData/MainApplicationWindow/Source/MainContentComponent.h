// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent final : public juce::Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    static juce::String getMidiMessageDescription (const juce::MidiMessage& m)
    {
        if (m.isNoteOn())           return "Note on "          + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
        if (m.isNoteOff())          return "Note off "         + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
        if (m.isProgramChange())    return "Program change "   + juce::String (m.getProgramChangeNumber());
        if (m.isPitchWheel())       return "Pitch wheel "      + juce::String (m.getPitchWheelValue());
        if (m.isAftertouch())       return "After touch "      + juce::MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + juce::String (m.getAfterTouchValue());
        if (m.isChannelPressure())  return "Channel pressure " + juce::String (m.getChannelPressureValue());
        if (m.isAllNotesOff())      return "All notes off";
        if (m.isAllSoundOff())      return "All sound off";
        if (m.isMetaEvent())        return "Meta event";

        if (m.isController())
        {
            juce::String name (juce::MidiMessage::getControllerName (m.getControllerNumber()));

            if (name.isEmpty())
                name = "[" + juce::String (m.getControllerNumber()) + "]";

            return "Controller " + name + ": " + juce::String (m.getControllerValue());
        }

        return juce::String::toHexString (m.getRawData(), m.getRawDataSize());
    }

    void setNoteNumber (int noteNumber)
    {
        auto message = juce::MidiMessage::noteOn (midiChannel, noteNumber, (juce::uint8) 100);
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        addMessageToList (message);
    }

    void logMessage (const juce::String& m)
    {
        midiMessagesBox.moveCaretToEnd();
        midiMessagesBox.insertTextAtCaret (m + juce::newLine);
    }

    void addMessageToList (const juce::MidiMessage& message)
    {
        auto time = message.getTimeStamp();

        auto hours   = ((int) (time / 3600.0)) % 24;
        auto minutes = ((int) (time / 60.0)) % 60;
        auto seconds = ((int) time) % 60;
        auto millis  = ((int) (time * 1000.0)) % 1000;

        auto timecode = juce::String::formatted ("%02d:%02d:%02d.%03d",
                                                 hours,
                                                 minutes,
                                                 seconds,
                                                 millis);

        logMessage (timecode + "  -  " + getMidiMessageDescription (message));
    }

    //==============================================================================
    juce::TextButton bassDrumButton;
    juce::TextButton snareDrumButton;
    juce::TextButton closedHiHatButton;
    juce::TextButton openHiHatButton;

    juce::Label volumeLabel;
    juce::Slider volumeSlider;

    juce::TextEditor midiMessagesBox;

    int midiChannel = 10;
    double startTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
