//
//  SphereCreatingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__SphereCreatingMode__
#define __airsketcher__SphereCreatingMode__

#include <math.h>

#include "AirController.h"

class SphereCreatingMode : public AirControlMode
{
public:
    
    SphereCreatingMode();
    ~SphereCreatingMode();
    
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
    
    std::vector<ofPoint> traces;
    
    DRAWING_MODE drawCircleMode;
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
            float distance = sqrt((traces.front()-traces.back()).lengthSquared());
            radius += distance;
        }
        radius /= traces.size();
        return radius;
    }
};

#endif /* defined(__airsketcher__SphereCreatingMode__) */
