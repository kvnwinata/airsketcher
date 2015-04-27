//
//  AirCommandCylinder.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandCylinder.h"

AirCommandCylinder::AirCommandCylinder(AirObjectManager& objectManager, ofPoint centroid, float radius, float height)
: AirCommand()
, _objectManager(objectManager)
, _centroid(centroid)
, _radius(radius)
, _height(height)
, _object(NULL)
{
    AirCylinder* cylinder = new AirCylinder();
    if (NULL == cylinder)
    {
        return false;
    }
    cylinder->setup(_centroid, _radius, _height, ofColor::gray); // Default color: gray
    _object = cylinder;
}

AirCommandCylinder::~AirCommandCylinder()
{
    
}

bool AirCommandCylinder::execute()
{
    _objectManager.addObject(_object);
    return true;
}

void AirCommandCylinder::unexecute()
{
    _objectManager.getObjectOwnership(_object);
}