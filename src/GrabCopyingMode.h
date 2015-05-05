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
    
    enum DRAWING_MODE {
        NONE = 0,
        DRAW,
        DONE
    };
    
    DRAWING_MODE copyingMode;    
    AirObject* objectCopy;
    AirObject* copiedObject;

    std::string completeTag    = "grab-copy";
    std::string lostTag        = "grab-copy-lost";
    std::string cancelTag      = "grab-copy-cancel";
};

#endif /* defined(__airsketcher__GrabCopyingMode__) */
