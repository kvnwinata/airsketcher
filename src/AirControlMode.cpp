//
//  AirControlMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#include "AirControlMode.h"

AirControlMode::AirControlMode()
: hasCompleted(true)
{
    
}

AirControlMode::~AirControlMode()
{
    
}

bool AirControlMode::getHasCompleted() const
{
    return hasCompleted;
}