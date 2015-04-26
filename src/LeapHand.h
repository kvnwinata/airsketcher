//
//  LeapHand.h
//  airsketcher
//
//  Created by Kevin Wong on 3/23/15.
//
//

#ifndef __airsketcher__LeapHand__
#define __airsketcher__LeapHand__

#include "ofMain.h"
#include "Leap.h"

class LeapHand
{
public:
    
    enum fingerType {
        THUMB = 0,
        INDEX = 1,
        MIDDLE = 2,
        RING = 3,
        PINKY = 4
    };
    
    enum Joint
    {
        THUMB_MCP = 0,  THUMB_PIP = 1,  THUMB_DIP = 2,  THUMB_TIP = 3,
        INDEX_MCP = 4,  INDEX_PIP = 5,  INDEX_DIP = 6,  INDEX_TIP = 7,
        MIDDLE_MCP = 8, MIDDLE_PIP = 9, MIDDLE_DIP = 10,MIDDLE_TIP = 11,
        RING_MCP = 12,  RING_PIP = 13,  RING_DIP = 14,  RING_TIP = 15,
        PINKY_MCP = 16, PINKY_PIP = 17, PINKY_DIP = 18, PINKY_TIP = 19,
        Joint_Count = 20,
    };
    
public:
    
    LeapHand();
    
    void draw();
    void drawShadow();
    void drawJoints();
    void updateHand(const Leap::Hand &handObject);
    ofPoint getTipLocation();
    bool getIsActive() const;
    void setInactive();
    
    float getPinchStrength()    const; // returns 0 if inactive
    float getGrabStrength()     const; // returns 0 if inactive
    
    bool getIsPinching() const;
    
private:
    bool isActive;
    
    static const int smoothing = 5;
    std::deque<bool> pinchHistory;
    bool isPinching; // will be smoothed
    void updateIsPinching();
    
    
    float pinchStrength;
    float grabStrength;
    
    vector<ofPoint> joints;
    
    ofPoint positionToOfPoint(const Leap::Vector &vector);

};


#endif /* defined(__airsketcher__LeapHand__) */
