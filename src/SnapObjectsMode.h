#ifndef __airsketcher__SnapObjectsMode__
#define __airsketcher__SnapObjectsMode__

#include <stdio.h>

#include "AirController.h"

class SnapObjectsMode : public AirControlMode
{
public:
    SnapObjectsMode();
    ~SnapObjectsMode();
    
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
    std::string drawCommand = "snap";
    
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
    
};


#endif /* defined(__airsketcher__SnapObjectsMode__) */
