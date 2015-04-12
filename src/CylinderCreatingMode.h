//
//  CylinderCreatingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__CylinderCreatingMode__
#define __airsketcher__CylinderCreatingMode__

#include <math.h>

#include "AirControlMode.h"
#include "AirCylinder.h"

class CylinderCreatingMode : public AirControlMode
{
public:
    
    CylinderCreatingMode();
    ~CylinderCreatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

private:
    
    enum DRAWING_MODE {
        NONE_CIRCLE = 0,
        DRAW_CIRCLE,
        NONE_HEIGHT,
        DRAW_HEIGHT,
        DONE
    };
    
    DRAWING_MODE drawCylinderMode;
    bool createCylinder(AirObjectManager &objectManager);
    
    std::vector<ofPoint> circleTraces;
    ofPoint startHeight;
    ofPoint endHeight;
    AirCylinder* newCylinder;
    
    inline ofPoint computeBaseCircleTraceCentroid()
    {
        ofPoint centroid(0.0, 0.0, 0.0);
        for (const ofPoint& point : circleTraces) {
            centroid += point;
        }
        centroid /= circleTraces.size();
        return centroid;
    }
    
    inline float computeBaseCircleTraceRadius(const ofPoint& centroid)
    {
        float radius = 0.0;
        for (const ofPoint& point : circleTraces) {
            float distance = sqrt((circleTraces.front()-circleTraces.back()).lengthSquared());
            radius += distance;
        }
        radius /= circleTraces.size();
        return radius;
    }
    
    inline float computeCylinderHeight()
    {
        float height = sqrt((endHeight-startHeight).lengthSquared());
        return height;
    }
};

#endif /* defined(__airsketcher__CylinderCreatingMode__) */
