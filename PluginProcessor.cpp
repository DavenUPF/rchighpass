#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RCHighPassPluginAudioProcessor::RCHighPassPluginAudioProcessor()
    : juce::AudioProcessor(
        juce::AudioProcessor::BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, juce::Identifier("Params"), createParams()),
    filterL(44100.0f, 1000.0f),
    filterR(44100.0f, 1000.0f)
{
}

RCHighPassPluginAudioProcessor::~RCHighPassPluginAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout RCHighPassPluginAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "cutoff", "Cutoff", juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.5f), 1000.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "gain", "Gain", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f));

    return { params.begin(), params.end() };
}

const juce::String RCHighPassPluginAudioProcessor::getName() const { return JucePlugin_Name; }

bool RCHighPassPluginAudioProcessor::acceptsMidi() const { return false; }
bool RCHighPassPluginAudioProcessor::producesMidi() const { return false; }
bool RCHighPassPluginAudioProcessor::isMidiEffect() const { return false; }
double RCHighPassPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int RCHighPassPluginAudioProcessor::getNumPrograms() { return 1; }
int RCHighPassPluginAudioProcessor::getCurrentProgram() { return 0; }
void RCHighPassPluginAudioProcessor::setCurrentProgram(int) {}
const juce::String RCHighPassPluginAudioProcessor::getProgramName(int) { return {}; }
void RCHighPassPluginAudioProcessor::changeProgramName(int, const juce::String&) {}

void RCHighPassPluginAudioProcessor::prepareToPlay(double sampleRate, int)
{
    float cutoff = *parameters.getRawParameterValue("cutoff");
    filterL.prepare(sampleRate);
    filterL.setCutoff(cutoff);
    filterR.prepare(sampleRate);
    filterR.setCutoff(cutoff);
}

void RCHighPassPluginAudioProcessor::releaseResources() {}

void RCHighPassPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    auto numSamples = buffer.getNumSamples();
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getNumChannels() > 1 ? buffer.getWritePointer(1) : nullptr;

    float cutoff = *parameters.getRawParameterValue("cutoff");
    float gain = *parameters.getRawParameterValue("gain");
    filterL.setCutoff(cutoff);
    filterR.setCutoff(cutoff);

    for (int i = 0; i < numSamples; ++i)
    {
        left[i] = filterL.processSample(left[i]) * gain;
        if (right) right[i] = filterR.processSample(right[i]) * gain;
    }
}

bool RCHighPassPluginAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* RCHighPassPluginAudioProcessor::createEditor()
{
    return new RCHighPassPluginAudioProcessorEditor(*this);
}

void RCHighPassPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void RCHighPassPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));

    if (xml.get() != nullptr)
        if (xml->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RCHighPassPluginAudioProcessor();
}
