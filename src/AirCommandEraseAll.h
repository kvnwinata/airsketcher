//
//  AirCommandEraseAll.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/27/15.
//
//

#ifndef __airsketcher__AirCommandEraseAll__
#define __airsketcher__AirCommandEraseAll__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandEraseAll : public AirCommand
{
public:
    AirCommandEraseAll(AirObjectManager& objectManager);
    ~AirCommandEraseAll();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObjectManager& _objectManager;
    std::vector<AirObject*> _objects; // should all be valid pointers
    bool _ownObjects;
};

#endif /* defined(__airsketcher__AirCommandEraseAll__) */
