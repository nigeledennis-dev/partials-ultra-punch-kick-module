#include "PluginProcessor.h"
#include "PluginEditor.h"

UltraPunchKickModuleAudioProcessor::UltraPunchKickModuleAudioProcessor()
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      ),
      apvts(*this, nullptr, "Parameters", createParameterLayout())
{
}

UltraPunchKickModuleAudioProcessor::~UltraPunchKickModuleAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout UltraPunchKickModuleAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"freq_start", 1}, "Initial Impact",
        juce::NormalisableRange<float>(100f, 800f), 350f,
        juce::AudioParameterFloatAttributes().withLabel("Hz")));
    param->range.setSkewForCentre(param->range.start + (param->range.end - param->range.start) * 0.25f);
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"freq_end", 1}, "Body Tuning",
        juce::NormalisableRange<float>(25f, 100f), 48f,
        juce::AudioParameterFloatAttributes().withLabel("Hz")));
    param->range.setSkewForCentre(param->range.start + (param->range.end - param->range.start) * 0.25f);
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"pitch_decay", 1}, "Snap",
        juce::NormalisableRange<float>(5f, 150f), 25f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));
    param->range.setSkewForCentre(param->range.start + (param->range.end - param->range.start) * 0.25f);
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"fold_amt", 1}, "Folding Depth",
        juce::NormalisableRange<float>(0f, 1f), 0f,
        juce::AudioParameterFloatAttributes().withLabel("")));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"bias_amt", 1}, "Symmetry Bias",
        juce::NormalisableRange<float>(-1f, 1f), 0f,
        juce::AudioParameterFloatAttributes().withLabel("")));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"stress", 1}, "STRESS",
        juce::NormalisableRange<float>(0f, 24f), 0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"click_lvl", 1}, "Click Transient",
        juce::NormalisableRange<float>(0f, 1f), 0.3f,
        juce::AudioParameterFloatAttributes().withLabel("")));
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"amp_decay", 1}, "Tail Decay",
        juce::NormalisableRange<float>(50f, 3000f), 450f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));
    param->range.setSkewForCentre(param->range.start + (param->range.end - param->range.start) * 0.25f);

    return layout;
}

void UltraPunchKickModuleAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void UltraPunchKickModuleAudioProcessor::releaseResources() {}

void UltraPunchKickModuleAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* UltraPunchKickModuleAudioProcessor::createEditor()
{
    return new UltraPunchKickModuleAudioProcessorEditor(*this);
}

void UltraPunchKickModuleAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void UltraPunchKickModuleAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UltraPunchKickModuleAudioProcessor();
}
