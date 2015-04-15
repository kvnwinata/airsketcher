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
{
}

bool AirCommandBox::execute()
{
    AirBox* box = new AirBox();
    if (NULL == box)
    {
        return false;
    }
    box->setup(_centroid, _sizeXYZ, ofColor::gray); // Default color: gray
    _objectManager.addObject(box);
    _object = box;
    return true;
}

void AirCommandBox::unexecute()
{
    _objectManager.deleteObject(_object);
    _object = NULL;
}