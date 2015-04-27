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
    AirSphere* sphere = new AirSphere();
    if (NULL != sphere)
    {
        sphere->setup(_centroid, _radius, ofColor::gray); // Default color: gray
    }
    _object = sphere;
}

AirCommandSphere::~AirCommandSphere()
{
    
}

bool AirCommandSphere::execute()
{
    _objectManager.addObject(_object);
    return true;
}

void AirCommandSphere::unexecute()
{
    _objectManager.getObjectOwnership(_object);
}