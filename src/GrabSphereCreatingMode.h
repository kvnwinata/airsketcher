//
//  GrabSphereCreatingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 5/1/15.
//
//

#ifndef __airsketcher__GrabSphereCreatingMode__
#define __airsketcher__GrabSphereCreatingMode__

#include <math.h>

#include "AirController.h"

class GrabSphereCreatingMode : public AirControlMode
{
public:
    
    GrabSphereCreatingMode();
    ~GrabSphereCreatingMode();
    
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
    
    DRAWING_MODE drawCircleMode;
    AirSphere* sphere;
    std::vector<ofPoint> traces;
    
    bool createSphere(AirController* controller, AirObjectManager &objectManager);
    
    inline ofPoint computeTraceCentroid()
    {
        ofPoint centroid(0.0, 0.0, 0.0);
        for (const ofPoint& point : traces) {
            centroid += point;
        }
        centroid /= traces.size();
        return centroid;
    }
    
    inline float computeTraceRadius(const ofPoint& centroid)
    {
        float radius = 0.0;
        for (const ofPoint& point : traces) {
            float distance = sqrt((point-centroid).lengthSquared());
            radius += distance;
        }
        radius /= traces.size();
        return radius;
    }

    std::string completeTag    = "grab-sphere";
    std::string lostTag        = "grab-sphere-lost";
    std::string cancelTag      = "grab-sphere-cancel";
};

#endif /* defined(__airsketcher__GrabGrabSphereCreatingMode__) */
