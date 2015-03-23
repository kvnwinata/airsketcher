//
//  AirObject.h
//  airsketcher
//
//  Created by Kevin Wong on 3/19/15.
//
//

#ifndef __airsketcher__AirObject__
#define __airsketcher__AirObject__

#include "ofMain.h"

class AirObject
{
public:
    
    AirObject(){};
    ~AirObject(){};
    
    virtual bool isInside(ofPoint location) const = 0; // true if location is inside object

    virtual void setPosition(ofPoint pos){position = pos;};
    virtual ofPoint getPosition(){return position;};
    
    virtual void setColor(ofColor col){color = col;};
    virtual ofColor getColor(){return color;};
    
    virtual void draw()             const = 0; // draw object, center at (0,0,0)
    virtual void drawHighlight()    const = 0; // draw highlight (e.g. bounding box), centered at (0,0,0)
    
protected:
    
    ofQuaternion    orientation;
    ofPoint         position;
    
    ofColor         color;

};

#endif /* defined(__airsketcher__AirObject__) */
