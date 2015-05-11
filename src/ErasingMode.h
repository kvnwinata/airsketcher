//
//  ErasingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__ErasingMode__
#define __airsketcher__ErasingMode__

#include "AirController.h"

class ErasingMode : public AirControlMode
{
public:
    
    ErasingMode();
    ~ErasingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

    int getEraseCount const { return eraseCount; };

private:
	int eraseCount;
};

#endif /* defined(__airsketcher__ErasingMode__) */
