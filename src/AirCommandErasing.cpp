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
, _ownObject(false)
{
}

AirCommandErasing::~AirCommandErasing()
{
    if (_ownObject && (NULL != _object))
    {
        delete _object;
    }
}

bool AirCommandErasing::execute()
{
    _objectManager.getObjectOwnership(_object);
    _ownObject = true;
    return true;
}

void AirCommandErasing::unexecute()
{
    _objectManager.addObject(_object);
    _ownObject = false;
}