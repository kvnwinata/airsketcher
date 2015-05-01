//
//  GrabCopyingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 5/1/15.
//
//

#ifndef __airsketcher__GrabCopyingMode__
#define __airsketcher__GrabCopyingMode__

#include "AirController.h"

class GrabCopyingMode : public AirControlMode
{
public:
    
    GrabCopyingMode();
    ~GrabCopyingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
    
private:
    
    AirObject* objectCopy;
    AirObject* copiedObject;
};

#endif /* defined(__airsketcher__GrabCopyingMode__) */
