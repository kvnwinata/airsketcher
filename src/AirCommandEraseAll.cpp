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
, _ownObjects(false)
{
}

AirCommandEraseAll::~AirCommandEraseAll()
{
    if (_ownObjects)
    {
        for (AirObject* object : _objects) {
            if (NULL != object) {
                delete object;
            }
        }
    }
}

bool AirCommandEraseAll::execute()
{
    _objects = _objectManager.getOwnershipAll();
    _ownObjects = true;
    return true;
}

void AirCommandEraseAll::unexecute()
{
    for (AirObject* object : _objects)
    {
        _objectManager.addObject(object);
    }
    _ownObjects = false;
}