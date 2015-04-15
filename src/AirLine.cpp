//
//  AirLine.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#include "AirLine.h"

const float AirLine::interactionRadius = 30.f;

AirLine::AirLine()
: AirObject()
{
}

AirLine::~AirLine()
{
    
}

bool AirLine::isInsideNormalized(ofPoint location) const
{
    return (ofVec2f(location.x, location.y).length() < interactionRadius/scale) && (abs(location.z) < length/2);
}

void AirLine::setup(ofPoint endPoint1, ofPoint endPoint2, ofColor c, float width)
{
    color = c;
    updateEndPoints(endPoint1, endPoint2);
    lineWidth = width;
}

void AirLine::updateEndPoints(ofPoint endPoint1, ofPoint endPoint2)
{
    position = (endPoint1 + endPoint2)/2;
    length = (endPoint1 - endPoint2).length();
    
    ofVec3f zAxis(0,0,1.f);
    
    float rotationAngle;
    ofVec3f rotationAxis;
    rotationAxis = zAxis.crossed(endPoint2 - endPoint1).normalized();
    rotationAngle = zAxis.angle(endPoint2 - endPoint1);
    
    ofQuaternion currentRotation;
    currentRotation.makeRotate(rotationAngle, rotationAxis);
    
    orientation = currentRotation;
}

void AirLine::setOrientation(ofQuaternion orientation_)
{
    orientation = orientation_;
    
    float rotationAngle;
    ofVec3f rotationAxis;
    orientation.getRotate(rotationAngle, rotationAxis);
    
    ofVec3f direction = ofVec3f(0,0,1.f).rotated(rotationAngle, rotationAxis).normalized();
    
    endPoints[0] = position + direction * length/2;
    endPoints[1] = position - direction * length/2;
}

void AirLine::getEndPoints(ofPoint* &endpoints)
{
    endpoints = endPoints;
}

void AirLine::drawNormalized() const
{
    ofSetColor(255,255,255);
    ofSetColor(color);
    ofRotate(90, 1, 0, 0);
    ofDrawCylinder(ofPoint(0,0,0), lineWidth/scale, length);

    ofSetColor(255, 255, 255);
}

void AirLine::drawHighlightNormalized() const
{
    ofRotate(90, 1, 0, 0);
    ofSetColor(color);
    ofDrawCylinder(ofPoint(0,0,0), lineWidth/scale, length);
    ofNoFill();
    ofDrawCylinder(ofPoint(0,0,0), interactionRadius/scale, length);
    ofSetColor(255,255,255);
    ofFill();
}

AirObject* AirLine::getCopy() const
{
    AirLine* newLine = new AirLine();
    newLine->endPoints[0] = endPoints[0];
    newLine->endPoints[1] = endPoints[1];
    newLine->length = length;
    newLine->lineWidth = lineWidth;
    this->copyData(newLine);
    return newLine;
}

std::string AirLine::getDescription() const
{
    std::stringstream msg;
    msg << "Line ";
    msg << id;
    
    return msg.str();
}