//
//  UndoMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__UndoMode__
#define __airsketcher__UndoMode__

#include "AirControlMode.h"

class UndoMode : public AirControlMode
{
public:
    
    UndoMode();
    ~UndoMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
};

#endif /* defined(__airsketcher__UndoMode__) */
