//
//  BoxCreatingMode.h
//  airsketcher
//
//  Created by Pramod Kandel on 5/4/15.
//
//

#ifndef __airsketcher__BoxCreatingMode__
#define __airsketcher__BoxCreatingMode__

#include <stdio.h>
#include "AirController.h"

class BoxCreatingMode : public AirControlMode
{
public:
    
    BoxCreatingMode();
    ~BoxCreatingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:

    
    AirBox* box;
    std::string drawCommand = "draw box";
    std::vector<ofPoint> traces;
    
    bool createBox(AirController* controller, AirObjectManager &objectManager);
    
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
    
    inline ofVec3f getSize()
    {
        ofVec3f size_xyz;
        ofPoint startPoint = getStartPoint();
        ofPoint endPoint = getEndPoint();
        float width = abs(startPoint.x - endPoint.x);
        float height = abs(startPoint.y - endPoint.y);
        float depth = abs(startPoint.z - endPoint.z);
        size_xyz.set(width, height, depth);
        return size_xyz;
    }
    
    inline ofPoint getCenterPosition()
    {
        return (getEndPoint()+getStartPoint())*0.5;
    }
    
    std::string completeTag    = "voice-box";
    std::string lostTag        = "voice-box-lost";
    std::string cancelTag      = "voice-box-cancel";
    
};


#endif /* defined(__airsketcher__BoxCreatingMode__) */
