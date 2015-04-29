//
//  GrabResizingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__GrabResizingMode__
#define __airsketcher__GrabResizingMode__

#include "AirController.h"

class GrabResizingMode : public AirControlMode
{
public:
    
    GrabResizingMode();
    ~GrabResizingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

private:
    
    AirObject * resizingObject;

    ofPoint originalCenterOfResizing;
    ofPoint originalPosition;
    ofPoint relativePosition;
        
    float originalScale;
    float originalDistance;
};

#endif /* defined(__airsketcher__GrabResizingMode__) */
