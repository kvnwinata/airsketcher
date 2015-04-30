//
//  AirBox.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__AirBox__
#define __airsketcher__AirBox__

#include "AirObject.h"

class AirBox : public AirObject
{
public:
    
    AirBox();
    ~AirBox();
    
    bool isInsideNormalized(ofPoint location) const override;
    
    void setup(ofPoint centerPosition, ofVec3f sizeXYZ, ofColor color);
    
    void drawNormalized()             const override;
    void drawHighlightNormalized()    const override;
    
    AirObject* getCopy() const override;
    
    std::string getDescription() const override;
    
    ofVec3f getSize() const;
    void setSize(ofVec3f size);
    
private:
    
    ofVec3f   size;
};

#endif /* defined(__airsketcher__AirBox__) */
