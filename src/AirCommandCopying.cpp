//
//  AirCommandCopying.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandCopying.h"

AirCommandCopying::AirCommandCopying(AirObjectManager& objectManager, AirObject* copiedObject)
: AirCommand()
, _objectManager(objectManager)
, _copiedObject(copiedObject)
, _objectCopy(NULL)
, _ownObject(false)
{
    _objectCopy = _copiedObject->getCopy();
}

AirCommandCopying::~AirCommandCopying()
{
    
}

bool AirCommandCopying::execute()
{
    if (NULL == _objectCopy)
    {
        return false;
    }
    _objectManager.addObject(_objectCopy);
    _objectManager.switchHighlightedObject(_objectCopy, _objectCopy->getPosition());
    _ownObject = true;
    return true;
}

void AirCommandCopying::unexecute()
{
    _objectManager.getObjectOwnership(_objectCopy);
    _ownObject = false;
}