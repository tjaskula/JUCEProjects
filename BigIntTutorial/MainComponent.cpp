#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (consoleBox);
    consoleBox.setMultiLine (true);
    consoleBox.setReturnKeyStartsNewLine (true);
    consoleBox.setReadOnly (true);
    consoleBox.setScrollbarsShown (true);
    consoleBox.setCaretVisible (false);
    consoleBox.setPopupMenuEnabled (true);
    consoleBox.setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x32ffffff));
    consoleBox.setColour (juce::TextEditor::outlineColourId, juce::Colour (0x1c000000));
    consoleBox.setColour (juce::TextEditor::shadowColourId, juce::Colour (0x16000000));

    setSize (1200, 400);

    runExample();
}

//==============================================================================
void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    consoleBox.setBounds (10, 10, getWidth() - 20, getHeight() - 20);
}

void MainComponent::runExample()
{
    /*logMessage ("------------------------- START --------------------------");

    int base = 10;
    juce::BigInteger bigInt = 11;

    for (auto iteration = 0; iteration < 100; ++iteration)
    {
        logMessage (bigInt.toString (base));

        bigInt *= 11;
    }

    logMessage ("----------------------- FINISHED -------------------------");*/

    /*logMessage ("------------------------- START --------------------------");

    int base = 2;
    juce::BigInteger bigInt = 3;

    for (auto iteration = 0; iteration < 100; ++iteration)
    {
        logMessage (bigInt.toString (base));

        bigInt = bigInt << 1;
    }

    logMessage ("----------------------- FINISHED -------------------------");*/

    /*logMessage ("------------------------- START --------------------------");

    juce::BigInteger bigInt;

    for (auto bit = 0; bit < 60; bit += 2)
        bigInt.setBit (bit);

    logMessage (juce::String ("binary: ")  + bigInt.toString (2));
    logMessage (juce::String ("decimal: ") + bigInt.toString (10));
    logMessage (juce::String ("hex: ")     + bigInt.toString (16));
    logMessage (juce::String ("octal: ")   + bigInt.toString (8));


    logMessage ("----------------------- FINISHED -------------------------");*/

    /*logMessage ("------------------------- START --------------------------");

    int base = 10;
    juce::BigInteger bigInt = 11;

    for (auto iteration = 0; iteration < 100; ++iteration)
    {
        bool isBit3set = bigInt[3];
        logMessage (bigInt.toString (base) + " : " + (isBit3set ? "Bit 3 is set" : "Bit 3 is NOT set"));

        bigInt *= 11;
    }

    logMessage ("----------------------- FINISHED -------------------------");*/

    logMessage ("------------------------- START --------------------------");

    juce::String originalText ("BigInteger objects are really useful for cryptography");
    logMessage ("Original text: ");
    logMessage (originalText);
    logMessage (juce::newLine);

    juce::MemoryOutputStream originalData;
    originalData << originalText;

    juce::BigInteger originalInteger;
    originalInteger.loadFromMemoryBlock (originalData.getMemoryBlock());

    logMessage ("Original text as a BigInteger: ");
    logMessage (originalInteger.toString (10));
    logMessage (juce::newLine);

    juce::MemoryBlock convertedData (originalInteger.toMemoryBlock());
    juce::String convertedString (convertedData.toString());

    logMessage ("BigInteger converted back to a string: ");
    logMessage (convertedString);

    logMessage ("----------------------- FINISHED -------------------------");
}

void MainComponent::logMessage (const juce::String& m)
{
    consoleBox.moveCaretToEnd();
    consoleBox.insertTextAtCaret (m + juce::newLine);
}