//
//  AirCommandBox.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/15/15.
//
//

#include "AirCommandBox.h"

AirCommandBox::AirCommandBox(AirObjectManager& objectManager, ofPoint centroid, ofVec3f sizeXYZ)
: AirCommand()
, _objectManager(objectManager)
, _centroid(centroid)
, _sizeXYZ(sizeXYZ)
, _object(NULL)
, _ownObject(false)
{
    AirBox* box = new AirBox();
    if (NULL == box)
    {
        return false;
    }
    box->setup(_centroid, _sizeXYZ, ofColor::gray); // Default color: gray
    _object = box;
}

AirCommandBox::~AirCommandBox()
{
    if (_ownObject && (NULL != _object))
    {
        delete _object;
    }
}

bool AirCommandBox::execute()
{
    _objectManager.addObject(_object);
    _ownObject = true;
    return true;
}

void AirCommandBox::unexecute()
{
    _objectManager.getObjectOwnership(_object);
    _ownObject = false;
}