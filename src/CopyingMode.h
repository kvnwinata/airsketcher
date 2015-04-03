//
//  CopyingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__CopyingMode__
#define __airsketcher__CopyingMode__

#include "AirControlMode.h"

class CopyingMode : public AirControlMode
{
public:
    
    CopyingMode();
    ~CopyingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() const override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    
private:
    
    AirObject* objectCopy;
    AirObject const* copiedObject;
};

#endif /* defined(__airsketcher__CopyingMode__) */
