#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    /*addAndMakeVisible (consoleBox);
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

    runExample();*/

    // visualization
    //setSize (600, 600);

    /*colours.add (juce::Colours::white);
    colours.add (juce::Colours::orange);
    colours.add (juce::Colours::lightgreen);

    setSize (400, 400);*/

    // weighted distributions
    colours.add (juce::Colours::white);
    weights.add (0.7f);

    colours.add (juce::Colours::orange);
    weights.add (0.25f);

    colours.add (juce::Colours::lightgreen);
    weights.add (0.05f);

    setSize (400, 400);
}

//==============================================================================
// randomly generated rectangles
void MainComponent::paint (juce::Graphics& g)
{
    /*g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::orange);

    auto& random = juce::Random::getSystemRandom();
    juce::Rectangle<int> rect (0, 0, 20, 20);

    for (auto i = 0; i < 100; ++i)
    {
        rect.setCentre (random.nextInt (getWidth()), random.nextInt (getHeight()));
        g.drawRect (rect);
    }*/

    // randomizing the size of the rectangles
    /*g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::orange);

    auto& random = juce::Random::getSystemRandom();
    juce::Rectangle<int> rect (0, 0, 20, 20);

    *//*for (auto i = 0; i < 100; ++i)
    {
        rect.setSize (random.nextInt (getWidth() / 4), random.nextInt (getHeight() / 4));
        rect.setCentre (random.nextInt (getWidth()), random.nextInt (getHeight()));
        g.drawRect (rect);
    }*//*

    for (auto i = 0; i < 100; ++i)
    {
        auto size = random.nextInt (juce::jmin (getWidth(), getHeight()) / 4);
        rect.setSize (size, size);
        rect.setCentre (random.nextInt (getWidth()), random.nextInt (getHeight()));
        g.drawRect (rect);
    }*/

    // randomizing colours
    /*g.fillAll (juce::Colours::black);

    auto& random = juce::Random::getSystemRandom();
    juce::Rectangle<int> rect (0, 0, 20, 20);*/

    /*for (auto i = 0; i < 100; ++i)
    {
        *//*juce::Colour colour (random.nextInt (256),
                             random.nextInt (256),
                             random.nextInt (256));*//*

        // randomizing just two components of colours limits the palette
        juce::Colour colour (random.nextInt (juce::Range<int> (100, 256)),
                             random.nextInt (juce::Range<int> (50,  200)),
                             200);

        g.setColour (colour);

        rect.setCentre (random.nextInt (getWidth()), random.nextInt (getHeight()));
        g.drawRect (rect);
    }*/

    // the oranges are at a hue of around 30° (or 0.083 in the 0 .. 1 range).
    // If we generate random hues in the range 0.05 .. 0.15 these should all be different shades of orange.
    /*for (auto i = 0; i < 100; ++i)
    {
        auto hue = juce::jmap (random.nextFloat(), 0.05f, 0.15f);
        g.setColour (juce::Colour::fromHSV (hue, 0.9f, 0.9f, 1.0f));

        rect.setCentre (random.nextInt (getWidth()), random.nextInt (getHeight()));
        g.drawRect (rect);
    }*/

    // choosing randomly from an array
    /*g.fillAll (juce::Colours::black);

    auto& random = juce::Random::getSystemRandom();
    juce::Rectangle<float> rect (0.0f, 0.0f, 5.0f, 5.0f);

    for (auto i = 0; i < 1000; ++i)
    {
        g.setColour (colours[random.nextInt (colours.size())]);
        rect.setCentre ((float) random.nextInt (getWidth()),
                        (float) random.nextInt (getHeight()));
        g.drawEllipse (rect, 1.0f);
    }*/

    /*// 1,000 circles distributed uniformly across the window
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::orange);

    auto& random = juce::Random::getSystemRandom();
    juce::Rectangle<float> rect (0.0f, 0.0f, 5.0f, 5.0f);*/

    /*for (auto i = 0; i < 1000; ++i)
    {
        rect.setCentre ((float) random.nextInt (getWidth()),
                        (float) random.nextInt (getHeight()));
        g.drawEllipse (rect, 1.0f);
    }*/

    /*// we generate linearly-distributed values for both the x and y coordinates of the circles
    for (auto i = 0; i < 1000; ++i)
    {
        auto x = random.nextInt (random.nextInt (juce::Range<int> (1, getWidth())));
        auto y = random.nextInt (random.nextInt (juce::Range<int> (1, getHeight())));

        rect.setCentre (x, y);
        g.drawEllipse (rect, 1.0f);
    }*/

    // to focus the circles around the centre we could change the code like
    /*auto centreX = getWidth()  / 2;
    auto centreY = getHeight() / 2;

    for (auto i = 0; i < 1000; ++i)
    {
        auto x0 = random.nextInt (juce::Range<int> (1, getWidth()  / 2));
        auto x  = random.nextInt (juce::Range<int> (centreX - x0, centreX + x0));
        auto y0 = random.nextInt (juce::Range<int> (1, getHeight() / 2));
        auto y  = random.nextInt (juce::Range<int> (centreY - y0, centreY + y0));

        rect.setCentre (x, y);
        g.drawEllipse (rect, 1.0f);
    }*/

    g.fillAll (juce::Colours::black);

    juce::Random random;
    juce::Rectangle<float> rect (0.0f, 0.0f, 5.0f, 5.0f);

    auto sumOfWeights = sumFloatArray (weights); // [1]

    for (auto i = 0; i < 1000; ++i)
    {
        g.setColour (colourAtQuantile (random.nextFloat() * sumOfWeights)); // [2]

        rect.setCentre ((float) random.nextInt (getWidth()),
                        (float) random.nextInt (getHeight()));

        g.drawEllipse (rect, 1.0f);
    }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    consoleBox.setBounds (getLocalBounds().reduced (10));
}

void MainComponent::runExample()
{
    /*logMessage ("------------------------- START --------------------------");

    for (auto iteration = 0; iteration < 100; ++iteration)
    {
        auto randomInt = juce::Random::getSystemRandom().nextInt64();

        logMessage (juce::String (randomInt));
    }

    logMessage ("----------------------- FINISHED -------------------------");*/

    /*logMessage ("------------------------- START --------------------------");

    juce::BigInteger maximumValue;
    maximumValue.setBit (256);

    for (auto iteration = 0; iteration < 100; ++iteration)
    {
        auto randomInt = juce::Random::getSystemRandom().nextLargeNumber (maximumValue);
        logMessage (randomInt.toString (10));
    }

    logMessage ("----------------------- FINISHED -------------------------");*/

    logMessage ("------------------------- START --------------------------");

    for (auto iteration = 0; iteration < 100; ++iteration)
    {
        //auto randomValue = juce::Random::getSystemRandom().nextFloat();
        auto randomValue = juce::Random::getSystemRandom().nextDouble();

        logMessage (juce::String (randomValue));
    }

    logMessage ("----------------------- FINISHED -------------------------");
}

float MainComponent::sumFloatArray (const juce::Array<float>& values)
{
    auto sum = 0.0f;

    for (auto value : values)
        sum += value;

    return sum;
}

static int indexOfQuantile (const juce::Array<float>& weights, float quantile)
{
    auto runningTotal = 0.0f; // [4]

    for (auto weight : weights)
    {
        runningTotal += weight;

        if (quantile < runningTotal) // [5]
            return weights.indexOf (weight);
    }

    return -1;
}

juce::Colour MainComponent::colourAtQuantile (float quantile) const  // [3]
{
    auto index = indexOfQuantile (weights, quantile);
    return index < 0 ? juce::Colours::transparentBlack : colours[index];
}

void MainComponent::logMessage (const juce::String& m)
{
    consoleBox.moveCaretToEnd();
    consoleBox.insertTextAtCaret (m + juce::newLine);
}