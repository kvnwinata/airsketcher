//
//  BoxCreatingMode.h
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//
//

#ifndef __airsketcher__BoxCreatingMode__
#define __airsketcher__BoxCreatingMode__

#include <stdio.h>

#include "AirControlMode.h"

class BoxCreatingMode : public AirControlMode
{
public:
    
    BoxCreatingMode();
    ~BoxCreatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    
private:
    
    ofPoint startPosition; //corner1 position
    ofPoint endPosition; //corner2 position
};


#endif /* defined(__airsketcher__BoxCreatingMode__) */
