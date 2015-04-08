//
//  AirCylinder.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#include "AirCylinder.h"

AirCylinder::AirCylinder()
: AirObject()
{
}

AirCylinder::~AirCylinder()
{
    
}

bool AirCylinder::isInsideNormalized(ofPoint location) const
{
    return (ofVec2f(location.x, location.y).length() < radius) && (abs(location.z) < height/2);
}

void AirCylinder::setup(ofPoint centerPosition, float r, float h, ofColor c)
{
    position = centerPosition;
    color = c;
    radius = r;
    height = h;
    
    ofSetCylinderResolution(20, 10);
}

void AirCylinder::drawNormalized() const
{
    ofSetColor(255,255,255);
    ofSetColor(color);
    ofRotate(90, 1, 0, 0);
    ofDrawCylinder(ofPoint(0,0,0), radius, height);
    ofSetColor(255, 255, 255);
}

void AirCylinder::drawHighlightNormalized() const
{
    ofSetColor(color);
    ofNoFill();
    ofRotate(90, 1, 0, 0);
    ofDrawCylinder(ofPoint(0,0,0), radius, height);
    ofSetColor(255,255,255);
    ofFill();
}

AirObject* AirCylinder::getCopy() const
{
    AirCylinder* newCylinder = new AirCylinder();
    newCylinder->height = height;
    newCylinder->radius = radius;
    this->copyData(newCylinder);
    return newCylinder;
}

std::string AirCylinder::getDescription() const
{
    std::stringstream msg;
    msg << "Cylinder ";
    msg << id;
    
    return msg.str();
}

float AirCylinder::getHeight() const {return height;}
float AirCylinder::getRadius() const {return radius;}
void AirCylinder::setHeight(float h) {height = h;}
void AirCylinder::setRadius(float r) {radius = r;}
