//
//  AirCommandSphere.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommandSphere.h"

AirCommandSphere::AirCommandSphere(AirObjectManager& objectManager, ofPoint centroid, float radius)
: AirCommand()
, _objectManager(objectManager)
, _centroid(centroid)
, _radius(radius)
, _object(NULL)
{
}

AirCommandSphere::~AirCommandSphere()
{
    
}

bool AirCommandSphere::execute()
{
    AirSphere* sphere = new AirSphere();
    if (NULL == sphere)
    {
        return false;
    }
    sphere->setup(_centroid, _radius, ofColor::gray); // Default color: gray
    _objectManager.addObject(sphere);
    _object = sphere;
    return true;
}

void AirCommandSphere::unexecute()
{
    _objectManager.deleteObject(_object);
    _object = NULL;
}