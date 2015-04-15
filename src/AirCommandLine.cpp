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
{
}

AirCommandLine::~AirCommandLine()
{
    
}

bool AirCommandLine::execute()
{
    AirLine* line = new AirLine();
    if (NULL == line)
    {
        return false;
    }
    line->setup(_startPoint, _endPoint, ofColor::gray); // Default color: gray
    _objectManager.addObject(line);
    _object = line;
    return true;
}

void AirCommandLine::unexecute()
{
    _objectManager.deleteObject(_object);
    _object = NULL;
}