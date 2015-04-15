//
//  AirCommandLine.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandLine__
#define __airsketcher__AirCommandLine__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandLine : public AirCommand
{
public:
    AirCommandLine(AirObjectManager& objectManager, ofPoint startPoint, ofPoint endPoint);
    ~AirCommandLine();
    
    bool execute() override;
    void unexecute() override;
    
    AirObject* getObject() { return _object; }
    
private:
    AirObjectManager& _objectManager;
    const ofPoint _startPoint;
    const ofPoint _endPoint;
    AirObject* _object;
};

#endif /* defined(__airsketcher__AirCommandLine__) */
