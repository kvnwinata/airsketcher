//
//  AirCommandRotating.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/15/15.
//
//

#ifndef __airsketcher__AirCommandRotating__
#define __airsketcher__AirCommandRotating__

#include "AirCommand.h"

class AirCommandRotating : public AirCommand
{
public:
    AirCommandRotating(AirObject* object, ofQuaternion prevOrientation, ofQuaternion newOrientation);
    ~AirCommandRotating();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObject* _object; // should be a valid pointer
    const ofQuaternion _prevOrientation;
    const ofQuaternion _newOrientation;
};

#endif /* defined(__airsketcher__AirCommandRotating__) */
