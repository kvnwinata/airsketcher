//
//  AirCommandMoving.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandMoving__
#define __airsketcher__AirCommandMoving__

#include "AirCommand.h"

class AirCommandMoving : public AirCommand
{
public:
    AirCommandMoving(AirObject* object, ofPoint prevPosition, ofPoint newPosition);
    ~AirCommandMoving();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObject* _object; // should be a valid pointer
    const ofPoint _prevPosition;
    const ofPoint _newPosition;
};

#endif /* defined(__airsketcher__AirCommandMoving__) */
