//
//  AirCommandMoving.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandMoving.h"

AirCommandMoving::AirCommandMoving(AirObject* object, ofPoint prevPosition, ofPoint newPosition)
: AirCommand()
, _object(object)
, _prevPosition(prevPosition)
, _newPosition(newPosition)
{
}

bool AirCommandMoving::execute()
{
    _object->setPosition(_newPosition);
    return true;
}

void AirCommandMoving::unexecute()
{
    _object->setPosition(_prevPosition);
}