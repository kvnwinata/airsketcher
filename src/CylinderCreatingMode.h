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

#include "AirController.h"
#include "AirCylinder.h"

class CylinderCreatingMode : public AirControlMode
{
public:
    
    CylinderCreatingMode();
    ~CylinderCreatingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

private:
    
    std::vector<ofPoint> circleTraces;
    ofPoint cylinderBaseLoc;
    AirCylinder* newCylinder;
    
    bool createCylinder(AirController* controller, AirObjectManager &objectManager);
    
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
            ofPoint delta = point-centroid;
            float distance = sqrt(delta[0]*delta[0] + delta[1]*delta[1]);
            radius += distance;
        }
        radius /= circleTraces.size();
        return radius;
    }
    
    /* If height is negative, the cylinder's centroid should be shifted downwards */
    inline ofPoint computeCylinderCentroid(float height)
    {
        ofPoint centroid(cylinderBaseLoc);
        centroid[2] += height/2.0;
        return centroid;
    }
};

#endif /* defined(__airsketcher__CylinderCreatingMode__) */
