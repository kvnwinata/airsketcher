//
//  SpaceSpaceRotatingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 4/5/15.
//
//

#ifndef __airsketcher__SpaceSpaceRotatingMode__
#define __airsketcher__SpaceSpaceRotatingMode__

#include "AirControlMode.h"

class SpaceRotatingMode : public AirControlMode
{
public:
    
    SpaceRotatingMode();
    ~SpaceRotatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    
private:
    
    ofVec3f      currentVector;
    ofVec3f      originalVector;
    
    ofPoint      centerOfRotation;
    
    std::vector<ofQuaternion> originalOrientations;
    std::vector<ofPoint>      originalRelativePositions;
};

#endif /* defined(__airsketcher__SpaceSpaceRotatingMode__) */
