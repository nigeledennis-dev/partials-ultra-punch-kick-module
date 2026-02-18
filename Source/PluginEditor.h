#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class UltraPunchKickModuleAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit UltraPunchKickModuleAudioProcessorEditor(UltraPunchKickModuleAudioProcessor&);
    ~UltraPunchKickModuleAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    UltraPunchKickModuleAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UltraPunchKickModuleAudioProcessorEditor)
};
