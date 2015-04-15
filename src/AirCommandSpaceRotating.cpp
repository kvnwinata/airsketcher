//
//  AirCommandSpaceRotating.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/15/15.
//
//

#include "AirCommandSpaceRotating.h"

AirCommandSpaceRotating::AirCommandSpaceRotating(AirObject* object, float prevScale, float newScale)
: AirCommand()
, _object(object)
, _prevScale(prevScale)
, _newScale(newScale)
{
}

AirCommandSpaceRotating::~AirCommandSpaceRotating()
{
    
}

bool AirCommandSpaceRotating::execute()
{
    _object->setScale(_newScale);
    return true;
}

void AirCommandSpaceRotating::unexecute()
{
    _object->setScale(_prevScale);
}