//
//  AirCommandEraseAll.cpp
//  airsketcher
//
//  Created by Patricia Adriana Suriana on 4/27/15.
//
//

#include "AirCommandEraseAll.h"

AirCommandEraseAll::AirCommandEraseAll(AirObjectManager& objectManager)
: AirCommand()
, _objectManager(objectManager)
{
}

AirCommandEraseAll::~AirCommandEraseAll()
{
    
}

bool AirCommandEraseAll::execute()
{
    AirObject* copy = _object->getCopy();
    if (NULL == copy)
    {
        return false;
    }
    _objectManager.deleteObject(_object);
    _object = copy;
    return true;
}

void AirCommandEraseAll::unexecute()
{
    _objectManager.addObject(_object);
}