//
//  RedoMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__RedoMode__
#define __airsketcher__RedoMode__

#include "AirControlMode.h"

class RedoMode : public AirControlMode
{
public:
    
    RedoMode();
    ~RedoMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
};

#endif /* defined(__airsketcher__RedoMode__) */
