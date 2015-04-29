//
//  GrabMovingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#ifndef __airsketcher__GrabMovingMode__
#define __airsketcher__GrabMovingMode__

#include "AirController.h"

class GrabMovingMode : public AirControlMode
{
public:
    
    GrabMovingMode();
    ~GrabMovingMode();
    
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
};

#endif /* defined(__airsketcher__GrabMovingMode__) */
