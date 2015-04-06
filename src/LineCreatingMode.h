//
//  LineCreatingMode.h
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//
//

#ifndef __airsketcher__LineCreatingMode__
#define __airsketcher__LineCreatingMode__

#include <stdio.h>

#include "AirControlMode.h"

class LineCreatingMode : public AirControlMode
{
public:
    
    LineCreatingMode();
    ~LineCreatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    
private:
    
    ofPoint startPosition; //start of line
    ofPoint endPosition; //end of line
};


#endif /* defined(__airsketcher__LineCreatingMode__) */
