//
//  LineCreatingMode.h
//  airsketcher
//
//  Created by Pramod Kandel on 5/4/15.
//
//

#ifndef __airsketcher__LineCreatingMode__
#define __airsketcher__LineCreatingMode__

#include <stdio.h>


#include "AirController.h"

class LineCreatingMode : public AirControlMode
{
public:
    
    LineCreatingMode();
    ~LineCreatingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:
    AirLine* line;
    std::string drawCommand = "draw line";
    
    std::vector<ofPoint> traces;
    
    
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
    
};

#endif /* defined(__airsketcher__LineCreatingMode__) */
