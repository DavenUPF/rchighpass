#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RCHighPassPluginAudioProcessorEditor::RCHighPassPluginAudioProcessorEditor(RCHighPassPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 150);

    // === Configuración del slider ===
    cutoffSlider.setSliderStyle(juce::Slider::Rotary);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    cutoffSlider.setRange(20.0, 20000.0, 1.0);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0); // percepción más natural
    addAndMakeVisible(cutoffSlider);

    // === Conectar con el AudioProcessorValueTreeState ===
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "cutoff", cutoffSlider);
}

RCHighPassPluginAudioProcessorEditor::~RCHighPassPluginAudioProcessorEditor()
{
}

//==============================================================================
void RCHighPassPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("RC High-Pass Filter", getLocalBounds(), juce::Justification::centredTop, 1);
}

void RCHighPassPluginAudioProcessorEditor::resized()
{
    cutoffSlider.setBounds(150, 40, 100, 100);  // Posición del slider
}

