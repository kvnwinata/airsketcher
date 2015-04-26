//
//  AirCommandSphere.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandSphere__
#define __airsketcher__AirCommandSphere__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandSphere : public AirCommand
{
public:
    AirCommandSphere(AirObjectManager& objectManager, ofPoint centroid, float radius);
    ~AirCommandSphere();
    
    bool execute() override;
    void unexecute() override;
    
    AirSphere* getObject() { return _object; }
    
private:
    AirObjectManager& _objectManager;
    const ofPoint _centroid;
    const float _radius;
    AirSphere* _object;
};


#endif /* defined(__airsketcher__AirCommandSphere__) */
