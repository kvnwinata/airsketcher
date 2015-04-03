//
//  AirObject.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/19/15.
//  Last update by Patricia Suriana on 3/31/15.
//
//

#include "AirObject.h"

int AirObject::nextAvalaibleId = 0;

AirObject::AirObject()
: position(0.f, 0.f, 0.f)
, scale(1.f)
, orientation(0.f, 0.f, 0.f, 1.f)
{
    id = assignId();
};


bool AirObject::isInside(ofPoint location) const
{
    ofPoint normalizedLocation;
    
    // normalize translation
    normalizedLocation = location - position;
    
    // normalize rotation
    float rotationAngle;
    ofVec3f rotationAxis;
    orientation.getRotate(rotationAngle, rotationAxis);
    normalizedLocation.rotate(-rotationAngle, rotationAxis);
    
    // normalize scaling
    normalizedLocation /= scale;
    
    return isInsideNormalized(normalizedLocation);
}


void AirObject::draw() const
{
    ofPushMatrix();
    
    // apply translation
    ofTranslate(position);
    
    // apply rotation
    float rotationAngle;
    ofVec3f rotationAxis;
    orientation.getRotate(rotationAngle, rotationAxis);
    ofRotate(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
    
    // apply scaling
    ofScale(scale, scale, scale);
    
    // draw
    drawNormalized();
    
    ofPopMatrix();
}

void AirObject::drawHighlight() const
{
    ofPushMatrix();
    
    // apply translation
    ofTranslate(position);
    
    // apply rotation
    float rotationAngle;
    ofVec3f rotationAxis;
    orientation.getRotate(rotationAngle, rotationAxis);
    ofRotate(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
    
    // apply scaling
    ofScale(scale, scale, scale);
    
    // draw
    drawHighlightNormalized();
    
    ofPopMatrix();
}
