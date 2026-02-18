#include "PluginEditor.h"

UltraPunchKickModuleAudioProcessorEditor::UltraPunchKickModuleAudioProcessorEditor(UltraPunchKickModuleAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(800, 500);
}

UltraPunchKickModuleAudioProcessorEditor::~UltraPunchKickModuleAudioProcessorEditor() {}

void UltraPunchKickModuleAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff1a1a1a));
    g.setColour(juce::Colours::white);
    g.setFont(16.0f);
    g.drawFittedText("Ultra-Punch Kick Module", getLocalBounds(), juce::Justification::centred, 1);
}

void UltraPunchKickModuleAudioProcessorEditor::resized()
{
}
