//
//  AirCommand.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommand__
#define __airsketcher__AirCommand__

#include "AirObject.h"

class AirCommand
{
public:
    AirCommand() {}
    virtual ~AirCommand() {}
    
    virtual bool execute() = 0;
    virtual void unexecute() = 0;
};

#endif /* defined(__airsketcher__AirCommand__) */