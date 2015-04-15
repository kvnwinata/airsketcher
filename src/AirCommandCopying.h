//
//  AirCommandCopying.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommandCopying__
#define __airsketcher__AirCommandCopying__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandCopying : public AirCommand
{
public:
    AirCommandCopying(AirObjectManager& objectManager, AirObject* copiedObject);
    ~AirCommandCopying();
    
    bool execute() override;
    void unexecute() override;
    
    AirObject* getObjectCopy() { return _objectCopy; }
    
private:
    AirObjectManager& _objectManager;
    const AirObject* _copiedObject; // should be a valid pointer
    AirObject* _objectCopy;
};

#endif /* defined(__airsketcher__AirCommandCopying__) */
