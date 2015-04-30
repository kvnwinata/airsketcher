//
//  AirCommandSnapObjects.h
//  airsketcher
//
//  Created by Pramod Kandel on 4/29/15.
//
//

#ifndef __airsketcher__AirCommandSnapObjects__
#define __airsketcher__AirCommandSnapObjects__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandSnapObjects : public AirCommand
{
public:
    AirCommandSnapObjects(AirObjectManager& objectManager);
    ~AirCommandSnapObjects();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObjectManager& _objectManager;
    std::vector<AirObject*> _objects; // should all be valid pointers
    bool _ownObjects;
};


#endif /* defined(__airsketcher__AirCommandSnapObjects__) */
