//
//  AirSphere.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/19/15.
//  Last update by Patricia Suriana on 3/31/15.
//
//

#include "AirSphere.h"

AirSphere::AirSphere()
: AirObject()
{
}

AirSphere::~AirSphere()
{
    
}

bool AirSphere::isInsideNormalized(ofPoint location) const
{
    return (location).lengthSquared() < (radius * radius);
}

void AirSphere::setup(ofPoint centerPosition, float r, ofColor c)
{
    position = centerPosition;
    radius = r;
    color = c;
}

void AirSphere::drawNormalized() const
{
    ofDrawSphere(ofPoint(0,0,0), radius);
}

void AirSphere::drawHighlightNormalized() const
{
    ofNoFill();
    ofRotate(90, 1, 0, 0);
    ofDrawSphere(0,0,0, radius);
    ofFill();
}

AirObject* AirSphere::getCopy() const
{
    AirSphere* newSphere = new AirSphere();
    newSphere->radius = radius;
    this->copyData(newSphere);
    return newSphere;
}

std::string AirSphere::getDescription() const
{
    std::stringstream msg;
    msg << "Sphere ";
    msg << id;
    
    return msg.str();
}