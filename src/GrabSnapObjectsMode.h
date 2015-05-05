#ifndef __airsketcher__GrabSnapObjectsMode__
#define __airsketcher__GrabSnapObjectsMode__

#include <stdio.h>

#include "AirController.h"

class GrabSnapObjectsMode : public AirControlMode
{
public:
    GrabSnapObjectsMode();
    ~GrabSnapObjectsMode();
    
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
    std::string drawCommand = "snap line";
    
    std::vector<ofPoint> traces;
    
    DRAWING_MODE drawLineMode;
    
    bool createLine(AirController* controller, AirObjectManager &objectManager);
    
    ofPoint startPoint;
    ofPoint endPoint;
    
    std::string snappedFirstObj;
    std::string lineObjDescr;
    bool snapped;
    
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
    std::string completeTag    = "grab-snapline-box";
    std::string lostTag        = "grab-snapline-lost";
    std::string cancelTag      = "grab-snapline-cancel";
    
};


#endif /* defined(__airsketcher__GrabSnapObjectsMode__) */
