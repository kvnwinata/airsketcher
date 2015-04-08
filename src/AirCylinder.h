//
//  AirCylinder.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__AirCylinder__
#define __airsketcher__AirCylinder__

#include "AirObject.h"

class AirCylinder : public AirObject
{
public:
    
    AirCylinder();
    ~AirCylinder();
    
    bool isInsideNormalized(ofPoint location) const override;
    
    void setup(ofPoint centerPosition, float radius, float height, ofColor color);
    
    float getHeight() const;
    float getRadius() const;
    void setHeight(float height);
    void setRadius(float radius);
    
    void drawNormalized()             const override;
    void drawHighlightNormalized()    const override;
    
    AirObject* getCopy() const override;
    
    std::string getDescription() const override;
    
private:
    
    float height;
    float radius;
};

#endif /* defined(__airsketcher__AirCylinder__) */
