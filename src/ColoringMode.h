//
//  ColoringMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#ifndef __airsketcher__ColoringMode__
#define __airsketcher__ColoringMode__

#include "AirController.h"

class ColoringMode : public AirControlMode
{
public:
    
    ColoringMode();
    ~ColoringMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

    
private:
    
    ofColor getColorFromString(std::string colorString);
    float startTime;
    std::string completeTag    = "color";
};

#endif /* defined(__airsketcher__ColoringMode__) */
