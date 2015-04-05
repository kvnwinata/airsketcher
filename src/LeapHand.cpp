//
//  LeapHand.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/23/15.
//
//

#include "LeapHand.h"

LeapHand::LeapHand():isActive(false)
{
    ofPoint origin(0,0,0);
    
    for (int i = 0; i < Joint_Count; i++)
    {
        joints.push_back(origin);
    }
    
    for (int i = 0; i < smoothing; i++)
    {
        pinchHistory.push_back(false);
    }
};

void LeapHand::updateHand(const Leap::Hand &handObject)
{
    isActive = true;
    
    pinchStrength = handObject.pinchStrength();
    grabStrength  = handObject.grabStrength();
    
    
    for(int j = 0; j < 5; j++)
    {
        const Leap::Finger & finger = handObject.fingers()[j];
        
        joints[j*4+0] = positionToOfPoint(finger.jointPosition(finger.JOINT_DIP));
        joints[j*4+1] = positionToOfPoint(finger.jointPosition(finger.JOINT_MCP));
        joints[j*4+2] = positionToOfPoint(finger.jointPosition(finger.JOINT_PIP));
        joints[j*4+3] = positionToOfPoint(finger.jointPosition(finger.JOINT_TIP));
    }
    
    // updatePinching
    updateIsPinching();
};

void LeapHand::updateIsPinching()
{
    // check current value:
    bool shouldPinch = (pinchStrength + grabStrength) > 0.8;
    
    // update history
    pinchHistory.pop_front();
    pinchHistory.push_back(shouldPinch);
    
    // see if is pinching
    int count = 0;
    for (bool history : pinchHistory)
    {
        count += history ? 1 : 0;
    }
    
    isPinching = count > smoothing/2;
}

void LeapHand::setInactive()
{
    isActive = false;
    isPinching = false;
}
bool LeapHand::getIsActive() const {return isActive;}

float LeapHand::getPinchStrength() const {return isActive ? pinchStrength : 0.f; }
float LeapHand::getGrabStrength() const {return isActive ? grabStrength : 0.f; }

bool LeapHand::getIsPinching() const {return isPinching;}

ofPoint LeapHand::getTipLocation()
{
    return joints[INDEX_TIP];
}

void LeapHand::draw()
{
    if (!isActive) return;
    
    ofSetColor(128,128,128, 128);
    for (int i = 0; i < Joint_Count; i++)
    {
        ofDrawSphere(joints[i], 3);
    }
    
    ofPoint tip = joints[INDEX_TIP];
    
    if (isPinching)
    {
        ofSetColor(255,0,255);
    }
    else
    {
        ofSetColor(255,255,0);
    }

    ofDrawSphere(tip, 5);
    
    ofSetColor(50, 50, 50);
    ofLine(tip, ofPoint(tip.x, tip.y, 0));
};

ofPoint LeapHand::positionToOfPoint(const Leap::Vector &vector)
{
    return ofPoint(vector.x, vector.z, vector.y); // flip coord
}
