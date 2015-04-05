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
        THUMB_DIP = 0,  THUMB_MCP = 1,  THUMB_PIP = 2,  THUMB_TIP = 3,
        INDEX_DIP = 4,  INDEX_MCP = 5,  INDEX_PIP = 6,  INDEX_TIP = 7,
        MIDDLE_DIP = 8, MIDDLE_MCP = 9, MIDDLE_PIP = 10,MIDDLE_TIP = 11,
        RING_DIP = 12,  RING_MCP = 13,  RING_PIP = 14,  RING_TIP = 15,
        PINKY_DIP = 16, PINKY_MCP = 17, PINKY_PIP = 18, PINKY_TIP = 19,
        Joint_Count = 20,
    };
    
public:
    
    LeapHand();
    
    void draw();
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
