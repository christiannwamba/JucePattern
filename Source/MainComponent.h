#pragma once

#include <JuceHeader.h>

struct Widget: juce::Component
{
    Widget(int i): num(i)
    {
        
    }
    void paint(juce::Graphics& g)
    {
        g.fillAll(juce::Colours::red);
        g.setColour(juce::Colours::black);
        g.drawRect(getLocalBounds().reduced(2));
        
        g.drawFittedText(juce::String(num), getLocalBounds(), juce::Justification::centred, 1);
    }
    int num = 0;
    
};

struct OwnedArrayComponent: juce::Component
{
    
    OwnedArrayComponent()
    {
        for(int i = 0; i < 10; i++)
        {
            auto* widget = widgets.add(new Widget(i));
            addAndMakeVisible(widget);
        }
    }
    // Alternative to OwnedArray
    // std::verctor<std::unique_ptr<Comp>> list
    juce::OwnedArray<Widget> widgets;
    
    void resized() override
    {
        auto width = getWidth() / static_cast<float>(widgets.size());
        int x = 0;
        auto h = getHeight();
        for(auto* widget : widgets)
        {
            widget->setBounds(x, 0, width, h);
            x += width;
        }
    }
    
};

struct MyComp: juce::Component
{
    void resized() override {}
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::green);
    }
    
    void mouseEnter(const juce::MouseEvent& e) override
    {
        DBG("MyComp mouseEnter " << counter);
        ++counter;
    }
    void mouseExit(const juce::MouseEvent& e) override
    {
        DBG("MyComp mouseLeave " << counter);
        ++counter;
    }
    
    void mouseMove(const juce::MouseEvent& e) override
    {
        DBG("MyComp mouseMove " << counter);
        ++counter;
    }
private:
    int counter = 0;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void mouseEnter(const juce::MouseEvent& e) override
    {
        DBG("MainComponent mouseEnter " << counter);
        ++counter;
    }
    void mouseExit(const juce::MouseEvent& e) override
    {
        DBG("MainComponent mouseLeave " << counter);
        ++counter;
    }
    void mouseMove(const juce::MouseEvent& e) override
    {
        DBG("MainComponent mouseMove " << counter);
        ++counter;
    }

private:
    //==============================================================================
    // Your private member variables go here...
    int counter = 0;
    MyComp comp;
    OwnedArrayComponent ownedArrayComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
