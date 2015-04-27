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
    AirObject* _object; // should be a valid pointer
};

#endif /* defined(__airsketcher__AirCommandEraseAll__) */
