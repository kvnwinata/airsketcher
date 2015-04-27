//
//  AirCommandLine.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandLine.h"

AirCommandLine::AirCommandLine(AirObjectManager& objectManager, ofPoint startPoint, ofPoint endPoint)
: AirCommand()
, _objectManager(objectManager)
, _startPoint(startPoint)
, _endPoint(endPoint)
, _object(NULL)
, _ownObject(false)
{
    AirLine* line = new AirLine();
    if (NULL == line)
    {
        return false;
    }
    line->setup(_startPoint, _endPoint, ofColor::gray); // Default color: gray
    _object = line;
}

AirCommandLine::~AirCommandLine()
{
    if (_ownObject && (NULL != _object))
    {
        delete _object;
    }
}

bool AirCommandLine::execute()
{
    _objectManager.addObject(_object);
    _ownObject = true;
    return true;
}

void AirCommandLine::unexecute()
{
    _objectManager.getObjectOwnership(_object);
    _ownObject = false;
}