//
//  AirCommandRotating.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/15/15.
//
//

#include "AirCommandRotating.h"

AirCommandRotating::AirCommandRotating(AirObject* object, ofQuaternion prevOrientation, ofQuaternion newOrientation)
: AirCommand()
, _object(object)
, _prevOrientation(prevOrientation)
, _newOrientation(newOrientation)
{
}

bool AirCommandRotating::execute()
{
    _object->setOrientation(_newOrientation);
    return true;
}

void AirCommandRotating::unexecute()
{
    _object->setOrientation(_prevOrientation);
}