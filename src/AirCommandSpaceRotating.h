//
//  AirCommandSpaceRotating.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/15/15.
//
//

#ifndef __airsketcher__AirCommandSpaceRotating__
#define __airsketcher__AirCommandSpaceRotating__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandSpaceRotating : public AirCommand
{
public:
    AirCommandSpaceRotating(AirObject* object, float prevScale, float newScale);
    ~AirCommandSpaceRotating();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObject* _object; // should be a valid pointer
    const float _prevScale;
    const float _newScale;
};

#endif /* defined(__airsketcher__AirCommandSpaceRotating__) */
