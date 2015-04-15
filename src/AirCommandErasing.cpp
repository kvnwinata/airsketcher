//
//  AirCommandErasing.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandErasing.h"

AirCommandErasing::AirCommandErasing(AirObjectManager& objectManager, AirObject* object)
: AirCommand()
, _objectManager(objectManager)
, _object(object)
{
}

AirCommandErasing::~AirCommandErasing()
{
    
}

bool AirCommandErasing::execute()
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

void AirCommandErasing::unexecute()
{
    _objectManager.addObject(_object);
}