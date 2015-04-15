//
//  AirCommandResizing.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandResizing.h"

AirCommandResizing::AirCommandResizing(AirObject* object, float prevScale, float newScale)
: AirCommand()
, _object(object)
, _prevScale(prevScale)
, _newScale(newScale)
{
}

AirCommandResizing::~AirCommandResizing()
{
    
}

bool AirCommandResizing::execute()
{
    _object->setScale(_newScale);
    return true;
}

void AirCommandResizing::unexecute()
{
    _object->setScale(_prevScale);
}