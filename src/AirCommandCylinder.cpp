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
}

AirCommandCylinder::~AirCommandCylinder()
{
    
}

bool AirCommandCylinder::execute()
{
    AirCylinder* cylinder = new AirCylinder();
    if (NULL == cylinder)
    {
        return false;
    }
    cylinder->setup(_centroid, _radius, _height, ofColor::gray); // Default color: gray
    _objectManager.addObject(cylinder);
    _object = cylinder;
    return true;
}

void AirCommandCylinder::unexecute()
{
    _objectManager.deleteObject(_object);
    _object = NULL;
}