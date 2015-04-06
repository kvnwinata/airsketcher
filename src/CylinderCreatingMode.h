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
    
private:
    
    bool drawBaseCircleCompleted;
    bool drawCylinderCompleted;
    bool createCylinder(AirObjectManager &objectManager);
    
    std::vector<ofPoint> circleTraces;
    std::vector<ofPoint> heightTraces;
    
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
        float height = sqrt((heightTraces.front()-heightTraces.back()).lengthSquared());
        return height;
    }
};

#endif /* defined(__airsketcher__CylinderCreatingMode__) */
