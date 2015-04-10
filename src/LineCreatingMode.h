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
    enum DRAWING_MODE {
        DRAW = 0,
        DONE,
        NONE
    };
    
    std::string drawCommand = "draw line";
    
    std::vector<ofPoint> traces;
    
    DRAWING_MODE drawLineMode;
    
    bool createLine(AirObjectManager &objectManager);
    
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
    
    ofPoint startPosition; //start of line
    ofPoint endPosition; //end of line
};


#endif /* defined(__airsketcher__LineCreatingMode__) */
