//
//  AirCommandBox.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/15/15.
//
//

#ifndef __airsketcher__AirCommandBox__
#define __airsketcher__AirCommandBox__

#include "AirCommand.h"
#include "AirObjectManager.h"

class AirCommandBox : public AirCommand
{
public:
    AirCommandBox(AirObjectManager& objectManager, ofPoint centroid, ofVec3f sizeXYZ);
    ~AirCommandBox();
    
    bool execute() override;
    void unexecute() override;
    
    AirObject* getObject() { return _object; }
    
private:
    AirObjectManager& _objectManager;
    const ofPoint _centroid;
    const ofPoint _sizeXYZ;
    AirObject* _object;
    bool _ownObject;
};

#endif /* defined(__airsketcher__AirCommandBox__) */
