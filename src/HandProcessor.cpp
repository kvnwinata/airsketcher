//
//  HandProcessor.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#include "HandProcessor.h"

HandProcessor::HandProcessor()
{
    hands.push_back(LeapHand());
    hands.push_back(LeapHand());
    
    leapImage.loadImage("leap.png");
    plane.set(500, 500, 50, 50);

}

HandProcessor::~HandProcessor()
{
    
}

void HandProcessor::drawHands()
{
    for (int i = 0; i < hands.size(); i++)
    {
        hands[i].draw();
    }
    
    if (controller.isConnected())
    {
        ofSetColor(255, 255, 255);
        ofPushMatrix();
        ofScale(0.5,0.5,0.5);
        //ofRotate(-90, 1, 0, 0);
        leapImage.draw(-leapImage.getWidth()/2, -leapImage.getHeight()/2, 0, leapImage.getWidth(), leapImage.getHeight());
        
        ofScale(2,2,2);
        ofTranslate(0,0,-10);
        plane.drawVertices();
        ofTranslate(0,0, 10);

        ofPopMatrix();
    }
}

LeapHand* HandProcessor::getHandAtIndex(int i)
{
    if (i < hands.size())
    {
        return &hands[i];
    }
    else
    {
        return 0;
    }
}

std::string HandProcessor::getStatusMessage()
{
    std::stringstream msg;
    msg << "[HAND]: ";
    msg << "status message\n";
    
    return msg.str();
}

void HandProcessor::update()
{
    if (!controller.isConnected())
    {
        for (int i = 0; i < hands.size(); i++)
        {
            hands[i].setInactive();
        }
    }

    Leap::Frame frame = controller.frame();
    
    if (frame.id() == lastFrameId) return;
    
    lastFrameId = frame.id();
    processCurrentFrame(frame);
}

void HandProcessor::processCurrentFrame(const Leap::Frame &frame)
{
    Leap::HandList handList = frame.hands();
    
    if (handList.count() >= 1)
    {
        hands[0].updateHand(handList[0]);
    }
    else
    {
        hands[0].setInactive();
    }
    
    if (handList.count() >= 2)
    {
        hands[1].updateHand(handList[1]);
    }
    else
    {
        hands[1].setInactive();
    }
}

void HandProcessor::onConnect(const Leap::Controller &leapController)
{
    std::cout << "Connected" << std::endl;
    
    // ENABLE GESTURES HERE:
    //leapController.enableGesture(Leap::Gesture::TYPE_SWIPE);
}