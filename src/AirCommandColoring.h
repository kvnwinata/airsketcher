//
//  AirCommandColoring.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandColoring__
#define __airsketcher__AirCommandColoring__

#include "AirCommand.h"

class AirCommandColoring : public AirCommand
{
public:
    AirCommandColoring(AirObject* object, ofColor prevColor, ofColor newColor);
    ~AirCommandColoring();
    
    bool execute() override;
    void unexecute() override;
    
private:
    AirObject* _object; // should be a valid pointer
    const ofColor _prevColor;
    const ofColor _newColor;
};

#endif /* defined(__airsketcher__AirCommandColoring__) */
