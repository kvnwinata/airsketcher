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
    std::string getHelpMessage() override;
    
private:
    enum DRAWING_MODE {
        DRAW = 0,
        DONE,
        NONE
    };
    
    std::string drawCommand = "draw box";
    
    std::vector<ofPoint> traces;
    
    DRAWING_MODE drawBoxMode;
    
    bool createBox(AirObjectManager &objectManager);
    
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
    
};


#endif /* defined(__airsketcher__BoxCreatingMode__) */
