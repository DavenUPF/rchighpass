#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class RCHighPassPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    RCHighPassPluginAudioProcessorEditor(RCHighPassPluginAudioProcessor&);
    ~RCHighPassPluginAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    RCHighPassPluginAudioProcessor& audioProcessor;

    // === A�adimos un slider para el cutoff y su conexi�n (Attachment) ===
    juce::Slider cutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RCHighPassPluginAudioProcessorEditor)
};
