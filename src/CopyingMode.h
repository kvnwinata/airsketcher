//
//  CopyingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__CopyingMode__
#define __airsketcher__CopyingMode__

#include "AirController.h"

class CopyingMode : public AirControlMode
{
public:
    
    CopyingMode();
    ~CopyingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

    
private:
    
    AirObject* objectCopy;
    AirObject* copiedObject;

    std::string completeTag    = "voice-copy";
    std::string lostTag        = "voice-copy-lost";
    std::string cancelTag      = "voice-copy-cancel";
};

#endif /* defined(__airsketcher__CopyingMode__) */
