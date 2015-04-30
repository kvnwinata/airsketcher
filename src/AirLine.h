//
//  AirLine.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__AirLine__
#define __airsketcher__AirLine__

#include "AirObject.h"

class AirLine : public AirObject
{
public:
    
    AirLine();
    ~AirLine();
    
    bool isInsideNormalized(ofPoint location) const override;
    
    void setup(ofPoint endPoint1, ofPoint endPoint2, ofColor color, float lineWidth = 5.f);

    float getLength() const;
    void setOrientation(ofQuaternion orientation) override;
    
    void getEndPoints(ofPoint* &endPoints);
    void updateEndPoints(ofPoint endPoint1, ofPoint endPoint2);
    
    void drawNormalized()             const override;
    void drawHighlightNormalized()    const override;
    
    AirObject* getCopy() const override;
    std::string getDescription() const override;
    
private:
    // redundant info: line is basically a thin cylinder
    static const float interactionRadius;
    float lineWidth;
    float length;
    
    // endpoints are stored so can be updated later
    ofPoint endPoints[2];

};

#endif /* defined(__airsketcher__AirLine__) */
