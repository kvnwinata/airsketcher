//
//  MovingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#ifndef __airsketcher__MovingMode__
#define __airsketcher__MovingMode__

#include "AirController.h"

class MovingMode : public AirControlMode
{
public:
    
    MovingMode();
    ~MovingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

    
private:
    
    AirObject * movingObject;
    
    ofPoint originalPosition;
    ofVec3f offset;
    
    float startTime;
    std::string completeTag    = "voice-move";
    std::string lostTag        = "voice-move-lost";
    std::string cancelTag      = "voice-move-cancel";
};

#endif /* defined(__airsketcher__MovingMode__) */
