//
//  AirCommandResizing.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandResizing__
#define __airsketcher__AirCommandResizing__

#include "AirCommand.h"

class AirCommandResizing : public AirCommand
{
public:
    AirCommandResizing(AirObject* object, float prevScale, float newScale);
    ~AirCommandResizing();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObject* _object; // should be a valid pointer
    const float _prevScale;
    const float _newScale;
};

#endif /* defined(__airsketcher__AirCommandResizing__) */
