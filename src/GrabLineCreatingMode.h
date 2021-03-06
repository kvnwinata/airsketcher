//
//  GrabLineCreatingMode.h
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//
//

#ifndef __airsketcher__GrabLineCreatingMode__
#define __airsketcher__GrabLineCreatingMode__

#include <stdio.h>

#include "AirController.h"

class GrabLineCreatingMode : public AirControlMode
{
public:
    
    GrabLineCreatingMode();
    ~GrabLineCreatingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:
    enum DRAWING_MODE {
        DRAW = 0,
        DONE,
        NONE
    };
    
    AirLine* line;
    std::string drawCommand = "draw line";
    
    std::vector<ofPoint> traces;
    
    DRAWING_MODE drawLineMode;
    
    bool createLine(AirController* controller, AirObjectManager &objectManager);
    
    inline ofPoint getStartPoint()
    {
        ofPoint startPoint(0.0, 0.0, 0.0);
        if (traces.size() > 0){
            startPoint = traces[0];
        }
        return startPoint;
    }
    
    inline ofPoint getEndPoint()
    {
        ofPoint endPoint(0.0, 0.0, 0.0);
        if (traces.size()>0){
            endPoint = traces[traces.size() -1];
        }
        return endPoint;
    }
    std::string completeTag    = "grab-line-box";
    std::string lostTag        = "grab-line-lost";
    std::string cancelTag      = "grab-line-cancel";
    
};


#endif /* defined(__airsketcher__GrabLineCreatingMode__) */
