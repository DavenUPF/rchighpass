#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
struct CustomLookAndFeel : public juce::LookAndFeel_V4
{
    CustomLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::orange);
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightblue);
        setColour(juce::Slider::trackColourId, juce::Colours::lightgrey);
    }
};

class RCHighPassPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    RCHighPassPluginAudioProcessorEditor(RCHighPassPluginAudioProcessor&);
    ~RCHighPassPluginAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    RCHighPassPluginAudioProcessor& audioProcessor;

    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;

    CustomLookAndFeel customLook;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RCHighPassPluginAudioProcessorEditor)
};

