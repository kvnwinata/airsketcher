//
//  AirSphere.h
//  airsketcher
//
//  Created by Kevin Wong on 3/19/15.
//
//

#ifndef __airsketcher__AirSphere__
#define __airsketcher__AirSphere__

#include "AirObject.h"

class AirSphere : public AirObject
{
public:
    
    AirSphere();
    ~AirSphere();
    
    bool isInsideNormalized(ofPoint location) const override;
    
    void setup(ofPoint centerPosition, float radius, ofColor color);
    
    void drawNormalized()             const override;
    void drawHighlightNormalized()    const override;
    
    AirObject* getCopy() const override;
    
    std::string getDescription() const override;
    
    float getRadius() const { return radius; };
    void setRadius(float newRadius) { radius = newRadius; };
    
private:
    
    float   radius;
};

#endif /* defined(__airsketcher__AirSphere__) */