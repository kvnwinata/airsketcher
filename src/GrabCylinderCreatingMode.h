//
//  GrabCylinderCreatingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 5/1/15.
//
//

#ifndef __airsketcher__GrabCylinderCreatingMode__
#define __airsketcher__GrabCylinderCreatingMode__

#include <math.h>

#include "AirController.h"
#include "AirCylinder.h"

class GrabCylinderCreatingMode : public AirControlMode
{
public:
    
    GrabCylinderCreatingMode();
    ~GrabCylinderCreatingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:
    
    enum DRAWING_MODE {
        NONE = 0,
        DRAW,
        DONE
    };
    
    DRAWING_MODE drawCylinderMode;
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

    std::string completeTag    = "grab-cylinder";
    std::string lostTag        = "grab-cylinder-lost";
    std::string cancelTag      = "grab-cylinder-cancel";
};

#endif /* defined(__airsketcher__GrabCylinderCreatingMode__) */
