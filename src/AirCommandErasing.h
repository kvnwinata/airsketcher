//
//  AirCommandErasing.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandErasing__
#define __airsketcher__AirCommandErasing__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandErasing : public AirCommand
{
public:
    AirCommandErasing(AirObjectManager& objectManager, AirObject* object);
    ~AirCommandErasing();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObjectManager& _objectManager;
    AirObject* _object; // should be a valid pointer
    bool _ownObject;
};

#endif /* defined(__airsketcher__AirCommandErasing__) */
