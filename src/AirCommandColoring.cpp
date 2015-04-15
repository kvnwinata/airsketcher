//
//  AirCommandColoring.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandColoring.h"

AirCommandColoring::AirCommandColoring(AirObject* object, ofColor prevColor, ofColor newColor)
: AirCommand()
, _object(object)
, _prevColor(prevColor)
, _newColor(newColor)
{
}

AirCommandColoring::~AirCommandColoring()
{
    
}

bool AirCommandColoring::execute()
{
    _object->setColor(_newColor);
    return true;
}

void AirCommandColoring::unexecute()
{
    _object->setColor(_prevColor);
}