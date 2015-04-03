//
//  AirObject.h
//  airsketcher
//
//  Created by Kevin Wong on 3/19/15.
//  Last update by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__AirObject__
#define __airsketcher__AirObject__

#include "ofMain.h"

class AirObject
{
public:
    
    AirObject();
    virtual ~AirObject(){};
    
    bool isInside(ofPoint location) const;
    virtual bool isInsideNormalized(ofPoint location) const = 0; // true if location is inside object
    
    virtual void setPosition(ofPoint pos){position = pos;};
    virtual ofPoint getPosition() const {return position;};
    
    virtual void setColor(ofColor col){color = col;};
    virtual ofColor getColor() const {return color;};
    
    void draw()             const; // draw object
    void drawHighlight()    const; // draw highlight (e.g. bounding box)
    
    // center at (0,0,0), normalized w.r.t rotation and translation
    virtual void drawNormalized()             const = 0; // draw object
    virtual void drawHighlightNormalized()    const = 0; // draw highlight (e.g. bounding box)
    
    virtual AirObject* getCopy() const = 0; // return copy of this object; transfer ownership to the caller
    
    virtual std::string getDescription() const = 0;
    
protected:
    
    ofQuaternion    orientation;
    ofPoint         position;
    float           scale;
    ofColor         color;
    int             id;
    
    void copyData(AirObject* object) const {
        object->orientation = orientation;
        object->position = position;
        object->color = color;
    }
    
private:
    static int nextAvalaibleId;
    
    int assignId() {
        int id = nextAvalaibleId;
        nextAvalaibleId++;
        return id;
    }
};

#endif /* defined(__airsketcher__AirObject__) */