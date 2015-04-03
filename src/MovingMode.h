//
//  MovingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#ifndef __airsketcher__MovingMode__
#define __airsketcher__MovingMode__

#include "AirControlMode.h"

class MovingMode : public AirControlMode
{
public:
    
    MovingMode();
    ~MovingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    
private:
    
    AirObject * movingObject;
    
    ofPoint originalPosition;
};

#endif /* defined(__airsketcher__MovingMode__) */
