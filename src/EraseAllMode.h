//
//  EraseAllMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/27/15.
//
//

#ifndef __airsketcher__EraseAllMode__
#define __airsketcher__EraseAllMode__

#include "AirController.h"

class EraseAllMode : public AirControlMode
{
public:
    
    EraseAllMode();
    ~EraseAllMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:
	int eraseAllCount;
};

#endif /* defined(__airsketcher__EraseAllMode__) */
