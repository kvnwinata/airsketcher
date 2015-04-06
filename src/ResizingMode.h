//
//  ResizingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__ResizingMode__
#define __airsketcher__ResizingMode__

#include "AirControlMode.h"

class ResizingMode : public AirControlMode
{
public:
    
    ResizingMode();
    ~ResizingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    
private:
    
    AirObject * resizingObject;

    ofPoint originalCenterOfResizing;
    ofPoint originalPosition;
    ofPoint relativePosition;
        
    float originalScale;
    float originalDistance;
};

#endif /* defined(__airsketcher__ResizingMode__) */