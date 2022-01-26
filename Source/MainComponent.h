#pragma once

#include <JuceHeader.h>

struct RepeatingThing;
struct DualButton : juce::Component
{
    DualButton(RepeatingThing&);
    void resized() override;
    RepeatingThing& timerThing;
private:
    juce::TextButton button1 {"button1"}, button2 {"button2"};
};

struct RepeatingThing : juce::Component, juce::Timer
{
    void timerCallback() override
    {
        drawRed = !drawRed;
        repaint();
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(drawRed ? juce::Colours::red : juce::Colours::green);
    }
    
    RepeatingThing()
    {
        startTimer(100);
    }
    ~RepeatingThing()
    {
        stopTimer();
    }
    
private:
    bool drawRed = true;
};

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

struct OwnedArrayComponent: juce::Component, juce::Button::Listener
{
    OwnedArrayComponent();
    ~OwnedArrayComponent();
    void resized() override;
    void buttonClicked(juce::Button*) override;
private:
    // Alternative to OwnedArray
    // std::verctor<std::unique_ptr<Comp>> list
    juce::OwnedArray<juce::TextButton> buttons;
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
//        DBG("MainComponent mouseEnter " << counter);
//        ++counter;
    }
    void mouseExit(const juce::MouseEvent& e) override
    {
//        DBG("MainComponent mouseLeave " << counter);
//        ++counter;
    }
    void mouseMove(const juce::MouseEvent& e) override
    {
//        DBG("MainComponent mouseMove " << counter);
//        ++counter;
    }
    
    void mouseDown(const juce::MouseEvent& e) override
    {
        DBG("you clicked the mouse");
    }

private:
    //==============================================================================
    // Your private member variables go here...
//    int counter = 0;
    MyComp comp;
    OwnedArrayComponent ownedArrayComp;
    RepeatingThing repeatingThing;
    DualButton dualButton {repeatingThing};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
