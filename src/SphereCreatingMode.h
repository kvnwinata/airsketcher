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

#include "AirControlMode.h"

class SphereCreatingMode : public AirControlMode
{
public:
    
    SphereCreatingMode();
    ~SphereCreatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    
private:
    
    std::vector<ofPoint> traces;
    
    bool drawCircleCompleted;
    bool createSphere(AirObjectManager &objectManager);
    
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
