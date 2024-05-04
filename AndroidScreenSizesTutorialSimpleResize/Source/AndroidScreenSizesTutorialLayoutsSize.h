/*
  ==============================================================================

   This file is part of the JUCE tutorials.
   Copyright (c) 2020 - Raw Material Software Limited

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES,
   WHETHER EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR
   PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

 name:             AndroidScreenSizesTutorialLayoutsSize
 version:          1.0.0
 vendor:           JUCE
 website:          http://juce.com
 description:      Layouts size on Android.

 dependencies:     juce_core, juce_data_structures, juce_events, juce_graphics,
                   juce_gui_basics
 exporters:        xcode_mac, vs2019, androidstudio

 type:             Component
 mainClass:        MainContentComponent

 useLocalCopy:     1

 END_JUCE_PIP_METADATA

*******************************************************************************/


#pragma once

//==============================================================================
class MainContentComponent   : public juce::Component
{
public:
    class ResizingComp  : public Component
    {
    public:
        ResizingComp()
        {
            juce::Array<juce::Colour> colours { juce::Colour (0xffb3c3Da), juce::Colour (0xff5973b8), juce::Colour (0xffd65667), juce::Colour (0xffd99154),
                                                juce::Colour (0xffe5ad6c), juce::Colour (0xffecc664), juce::Colour (0xffefe369), juce::Colour (0xffdddB74) };

            for (auto i = 0; i < 6; ++i)
            {
                auto* button = buttons.add (new juce::TextButton (juce::String ("Button ") + juce::String (i + 1)));

                button->setColour (juce::TextButton::buttonColourId,
                                   colours.getUnchecked (i % colours.size()));
            }

            for (auto i = 0; i < 6; ++i)
            {
                auto* slider = sliders.add (new juce::Slider());

                slider->setColour (juce::Slider::thumbColourId,
                                   colours.getUnchecked ((buttons.size() + i) % colours.size()));
                slider->setColour (juce::Slider::backgroundColourId,
                                   colours.getUnchecked ((buttons.size() + i + 2) % colours.size()).withAlpha (0.4f));
                slider->setColour (juce::Slider::trackColourId,
                                   colours.getUnchecked ((buttons.size() + i + 2) % colours.size()));
                slider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
            }

            setLookAndFeel (&lf);
        }

        ~ResizingComp() override
        {
            setLookAndFeel (nullptr);
        }

        void resized() override
        {
            if (holder.get() != nullptr)
            {
                removeChildComponent (holder.get());
                holder.reset();
            }

            auto minimumDimension = juce::jmin (getWidth(), getHeight());

            if (minimumDimension >= 480)
                layoutSinglePage();
            else
                layoutTabs();
        }

    private:
        //======================================================================
        class CustomLookAndFeel : public juce::LookAndFeel_V4
        {
        public:
            int getSliderThumbRadius (juce::Slider& slider) override
            {
                return juce::jmin (slider.getWidth(), slider.getHeight()) / 2;
            }
        };

        //======================================================================
        class ComponentHolder : public Component
        {
        public:
            ComponentHolder() {}

            void addComp (Component* comp)
            {
                comps.add (comp);
                addAndMakeVisible (comp);
            }

            void resized() override
            {
                if (getHeight() > getWidth())
                    resizedPortrait();
                else
                    resizedLandscape();
            }

            void paint (juce::Graphics& g) override
            {
                g.fillAll (juce::Colours::white);
                g.setColour (juce::Colour (0xff93c559));
                g.drawRoundedRectangle (0.0f, 0.0f, (float) getWidth(), (float) getHeight(), 0.0f, 8.0f);
            }

        private:
            void resizedPortrait()
            {
                auto space = 8;
                auto widgetHeight = (getHeight() - space) / comps.size() - space;

                for (auto* comp : comps)
                    comp->setBounds (space, space + (widgetHeight + space) * comps.indexOf (comp),
                                     getWidth() - space - space, widgetHeight);
            }

            void resizedLandscape()
            {
                auto space = 8;
                auto halfComps = comps.size() / 2;
                auto widgetHeight = (getHeight() - space) / halfComps - space;

                for (auto* comp : comps)
                {
                    auto index = comps.indexOf (comp);

                    if (index < halfComps)
                    {
                        comp->setBounds (space, space + (widgetHeight + space) * index,
                                         getWidth() / 2 - space - space, widgetHeight);
                    }
                    else
                    {
                        comp->setBounds (getWidth() / 2 + space, space + (widgetHeight + space) * (index - halfComps),
                                         getWidth() / 2 - space - space, widgetHeight);
                    }
                }
            }

            juce::Array<Component*> comps;
        };

        //======================================================================
        void layoutSinglePage()
        {
            holder.reset (new ComponentHolder());

            for (auto* button : buttons)
                dynamic_cast<ComponentHolder*> (holder.get())->addComp (button);

            for (auto* slider : sliders)
                dynamic_cast<ComponentHolder*> (holder.get())->addComp (slider);

            addAndMakeVisible (holder.get());
            holder->setBounds (getLocalBounds());
        }

        void layoutTabs()
        {
            auto orientation = getWidth() < getHeight() ? juce::TabbedButtonBar::TabsAtBottom
                                                        : juce::TabbedButtonBar::TabsAtLeft;

            holder.reset (new juce::TabbedComponent (orientation));         // [1]
            addAndMakeVisible (holder.get());                               // [2]

            auto* buttonTab = new ComponentHolder();                        // [3]
            auto* sliderTab = new ComponentHolder();

            dynamic_cast<juce::TabbedComponent*> (holder.get())->addTab ("Buttons", juce::Colours::white, buttonTab, true); // [4]
            dynamic_cast<juce::TabbedComponent*> (holder.get())->addTab ("Sliders", juce::Colours::white, sliderTab, true);

            for (auto* button : buttons)                                    // [5]
                buttonTab->addComp (button);

            for (auto* slider : sliders)                                    // [6]
                sliderTab->addComp (slider);

            holder->setBounds (getLocalBounds());                           // [7]
        }


        //==============================================================================
        juce::OwnedArray<juce::Button> buttons;
        juce::OwnedArray<juce::Slider> sliders;
        std::unique_ptr<Component> holder;
        CustomLookAndFeel lf;
    };

    //==============================================================================
    MainContentComponent()
    {
        resizingComp.reset (new ResizingComp());
        addAndMakeVisible (resizingComp.get());

        setSize (640, 480);
    }

    void resized() override
    {
        resizingComp->centreWithSize (getWidth(), getHeight());
    }

private:
    std::unique_ptr<ResizingComp> resizingComp;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
