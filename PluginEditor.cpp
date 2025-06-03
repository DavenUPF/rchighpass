#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// LookAndFeel personalizado (puedes moverlo a un archivo separado si prefieres)


//==============================================================================

RCHighPassPluginAudioProcessorEditor::RCHighPassPluginAudioProcessorEditor(RCHighPassPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 200);

    // Aplicar LookAndFeel
    setLookAndFeel(&customLook);

    // ============ Cutoff Slider (Rotary) ============
    cutoffSlider.setSliderStyle(juce::Slider::Rotary);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cutoffSlider.setRange(20.0, 20000.0, 1.0);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0);
    addAndMakeVisible(cutoffSlider);

    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "cutoff", cutoffSlider);

    // ============ Resonance Slider (Vertical) ============
    resonanceSlider.setSliderStyle(juce::Slider::LinearVertical);
    resonanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    resonanceSlider.setRange(0.1f, 10.0f, 0.1f);
    addAndMakeVisible(resonanceSlider);

    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "resonance", resonanceSlider);
}

RCHighPassPluginAudioProcessorEditor::~RCHighPassPluginAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================

void RCHighPassPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkmagenta);
    g.setColour(juce::Colours::white);
    g.setFont(16.0f);
    g.drawFittedText("RC High-Pass Filter", getLocalBounds(), juce::Justification::centredTop, 1);
}

void RCHighPassPluginAudioProcessorEditor::resized()
{
    cutoffSlider.setBounds(50, 60, 100, 100);
    resonanceSlider.setBounds(200, 60, 60, 100);
}
