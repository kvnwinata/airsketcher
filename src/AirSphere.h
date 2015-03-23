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
    
    bool isInside(ofPoint location) const override;
    
    void setup(ofPoint centerPosition, float radius, ofColor color);
    
    void draw()             const override;
    void drawHighlight()    const override;
    
    std::string getDescription() const;
    
private:
    
    float   radius;
};

#endif /* defined(__airsketcher__AirSphere__) */
