//
//  ColoringMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#ifndef __airsketcher__ColoringMode__
#define __airsketcher__ColoringMode__

#include "AirControlMode.h"

class ColoringMode : public AirControlMode
{
public:
    
    ColoringMode();
    ~ColoringMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() const override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    
private:
    
    ofColor getColorFromString(std::string colorString);
};

#endif /* defined(__airsketcher__ColoringMode__) */
