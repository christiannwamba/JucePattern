#include "MainComponent.h"

DualButton::DualButton()
{
    addAndMakeVisible(button1);
    addAndMakeVisible(button2);
    
//    button1.onClick = [this]()
//    {
//        DBG("Button 1's size: " << this->button1.getBounds().toString());
//        timerThing.startTimer(1000);
//    };
//
//    button2.onClick = [this]()
//    {
//        DBG("Button 2's size: " << this->button2.getBounds().toString());
//        timerThing.stopTimer();
//    };
}

void DualButton::resized()
{
    auto bounds = getLocalBounds();
    button1.setBounds(bounds.removeFromLeft(30));
    button2.setBounds(bounds);
}


void DualButton::setButton1Handler(std::function<void()> f)
{
    button1.onClick = f;
}

void DualButton::setButton2Handler(std::function<void()> f)
{
    button2.onClick = f;
}


OwnedArrayComponent::OwnedArrayComponent()
{
    for(int i = 0; i < 10; i++)
    {
        auto* widget = buttons.add(new juce::TextButton(juce::String(i)));
        addAndMakeVisible(widget);
        widget->addListener(this);
    }
}

OwnedArrayComponent::~OwnedArrayComponent()
{
    for(int i = 0; i < buttons.size(); i++)
    {
        auto* widget = buttons[i];
        widget->removeListener(this);
    }
}

void OwnedArrayComponent::resized()
{
    auto width = getWidth() / static_cast<float>(buttons.size());
    int x = 0;
    auto h = getHeight();
    for(auto* widget : buttons)
    {
        widget->setBounds(x, 0, width, h);
        x += width;
    }
}

void OwnedArrayComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
    
    if(buttonThatWasClicked == buttons.getFirst())
    {
        DBG("you clicked the first button");
    }
    else if (buttonThatWasClicked == buttons.getLast())
    {
        DBG("you clicekd the last button");
    }
    else
    {
        DBG("you clicked some other button");
    }
}

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(comp);
    addAndMakeVisible(ownedArrayComp);
    addAndMakeVisible(dualButton);
    addAndMakeVisible(repeatingThing);
    dualButton.setButton1Handler([this]()
                                     {
                                        repeatingThing.startTimer(1000);
                                    });
    dualButton.setButton2Handler([this]()
                                     {
                                        repeatingThing.stopTimer();
                                    });
//    comp.addMouseListener(this, false);
    ownedArrayComp.addMouseListener(this, true);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    comp.removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    comp.setBounds(30, 30, 100, 100);
    ownedArrayComp.setBounds(comp.getX(),
                                comp.getBottom() + 5,
                                getWidth() - comp.getX(),
                                getHeight() - comp.getBottom());
    dualButton.setBounds(comp.getBounds()
                         .withX(comp.getRight() + 5));
    repeatingThing.setBounds(comp.getBounds()
                             .withX(dualButton.getRight() + 5));
}
