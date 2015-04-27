//
//  AirCommandCylinder.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandCylinder__
#define __airsketcher__AirCommandCylinder__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandCylinder : public AirCommand
{
public:
    AirCommandCylinder(AirObjectManager& objectManager, ofPoint centroid, float radius, float height);
    ~AirCommandCylinder();
    
    bool execute() override;
    void unexecute() override;
    
    AirObject* getObject() { return _object; }
    
private:
    AirObjectManager& _objectManager;
    const ofPoint _centroid;
    const float _radius;
    const float _height;
    AirObject* _object;
    bool _ownObject;
};

#endif /* defined(__airsketcher__AirCommandCylinder__) */
