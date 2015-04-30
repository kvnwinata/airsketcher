//
//  AirBox.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#include "AirBox.h"

AirBox::AirBox()
: AirObject()
{
}

AirBox::~AirBox()
{
    
}

bool AirBox::isInsideNormalized(ofPoint location) const
{
    return (abs(location.x) < size.x/2) && (abs(location.y) < size.y/2) && (abs(location.z) < size.z/2);
}

void AirBox::setup(ofPoint centerPosition, ofVec3f s, ofColor c)
{
    position = centerPosition;
    size = s;
    color = c;
}

void AirBox::drawNormalized() const
{
    ofDrawBox(ofPoint(0,0,0), size.x, size.y, size.z);
}

void AirBox::drawHighlightNormalized() const
{
    ofSetLineWidth(4.f);
    ofNoFill();
    ofDrawBox(ofPoint(0,0,0), size.x, size.y, size.z);
    ofFill();
    ofSetColor(255, 255, 255, 64);
    ofDrawBox(ofPoint(0,0,0), size.x, size.y, size.z);
    ofSetLineWidth(1.f);
}

AirObject* AirBox::getCopy() const
{
    AirBox* newBox = new AirBox();
    newBox->size = size;
    this->copyData(newBox);
    return newBox;
}

std::string AirBox::getDescription() const
{
    std::stringstream msg;
    msg << "Box ";
    msg << id;
    
    return msg.str();
}

ofVec3f AirBox::getSize() const {return size;}
void AirBox::setSize(ofVec3f s){size = s;}