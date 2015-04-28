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
        
        joints[j*4+0] = positionToOfPoint(finger.jointPosition(finger.JOINT_MCP));
        joints[j*4+1] = positionToOfPoint(finger.jointPosition(finger.JOINT_PIP));
        joints[j*4+2] = positionToOfPoint(finger.jointPosition(finger.JOINT_DIP));
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

void LeapHand::drawJoints() // OLD, not being used
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

void LeapHand::draw()
{
    if (!isActive) return;
    
    ofSetColor(64,64, 255, 255);
    for (int i = 0; i < Joint_Count; i++)
    {
        ofDrawSphere(joints[i], 5);
    }
    
    for (int finger = 0; finger < 5; finger++)
    {
        for (int segment = 0; segment < 3; segment++)
        {
            ofPoint joint1 = joints[finger * 4 + segment];
            ofPoint joint2 = joints[finger * 4 + segment + 1];
            
            ofSetColor(255, 255, 255, 255);
            ofPushMatrix();
            ofTranslate((joint1 + joint2)/2);
            
            ofVec3f zAxis(0,0,1.f);
            
            float rotationAngle;
            ofVec3f rotationAxis;
            rotationAxis = zAxis.crossed(joint2 - joint1).normalized();
            rotationAngle = zAxis.angle(joint2 - joint1);
            ofRotate(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
            ofRotate(90, 1, 0, 0);
            ofDrawCylinder(5, (joint1-joint2).length());
            ofPopMatrix();
        }
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
    
    ofDrawSphere(tip, 8);
    
    //ofSetColor(50, 50, 50);
    //ofLine(tip, ofPoint(tip.x, tip.y, 0));
};

void LeapHand::drawShadow()
{
    if (!isActive) return;
    
    ofSetColor(20,20, 20, 255);
    for (int i = 0; i < Joint_Count; i++)
    {
        ofCircle(joints[i].x, joints[i].y, 0, 5);
    }
    ofSetLineWidth(5.f);

    for (int finger = 0; finger < 5; finger++)
    {
        for (int segment = 0; segment < 3; segment++)
        {
            ofPoint joint1 = joints[finger * 4 + segment];
            ofPoint joint2 = joints[finger * 4 + segment + 1];
            
            ofLine(joint1.x, joint1.y, joint2.x, joint2.y);
        }
    }
    ofSetLineWidth(1.f);
}


ofPoint LeapHand::positionToOfPoint(const Leap::Vector &vector)
{
    return ofPoint(vector.x, vector.z, vector.y); // flip coord
}
