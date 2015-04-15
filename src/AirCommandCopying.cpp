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
{
}

bool AirCommandCopying::execute()
{
    _objectCopy = _copiedObject->getCopy();
    if (NULL == _objectCopy)
    {
        return false;
    }
    _objectManager.addObject(_objectCopy);
    _objectManager.switchHighlightedObject(_objectCopy, _objectCopy->getPosition());
    return true;
}

void AirCommandCopying::unexecute()
{
    _objectManager.deleteObject(_objectCopy);
    _objectCopy = NULL;
}