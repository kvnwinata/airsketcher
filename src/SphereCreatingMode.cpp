//
//  SphereCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "SphereCreatingMode.h"

#include "AirSphere.h"
#include "Logger.h"

#define DISTANCE_SQUARED_THRESHOLD  15


std::vector<std::string> SphereCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw sphere");
    return commands;
}

SphereCreatingMode::SphereCreatingMode()
    : AirControlMode()
    , drawCircleCompleted(false)
{
    
}

SphereCreatingMode::~SphereCreatingMode()
{
    
}

void SphereCreatingMode::drawMode()
{
    //TODO: draw the traces
    for (auto it = traces.begin(); it != traces.end(); )
    {
        const ofPoint& p1 = *it;
        it++;
        if (it != traces.end())
        {
            const ofPoint& p2 = *it;
            ofLine(p1, p2);
        }
    }
}

bool SphereCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw sphere")
    {
        hasCompleted = false;
        return true;
    }
    return false;
}

void SphereCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    LeapHand* hand = handProcessor.getHandAtIndex(0);
        
    if (hand->getIsActive())
    {
        if (!drawCircleCompleted)
        {
            traces.push_back(hand->getTipLocation());
            /*float distanceSq = (traces.front()-traces.back()).lengthSquared();
            if (distanceSq < DISTANCE_SQUARED_THRESHOLD)
            {
                // The last trace is near to the starting point of the circle
                drawCircleCompleted = true;
                hasCompleted = true;
            }*/
        }
    }
    else
    {
        // hand is lost
        drawCircleCompleted = true;
        hasCompleted = true;
    }
    if (drawCircleCompleted) {
        if (!createSphere(objectManager))
        {
            Logger::getInstance()->temporaryLog("FAILED to create new SPHERE; trace size " + traces.size() + "");
        }
        drawCircleCompleted = false;
        traces.clear();
    }
}

bool SphereCreatingMode::createSphere(AirObjectManager &objectManager)
{
    ofPoint centroid = computeTraceCentroid();
    float radius = computeTraceRadius(centroid);
    if (radius > 0.0) {
        AirSphere* sphere = new AirSphere();
        sphere->setup(centroid, radius, ofColor::gray); // Default color: gray
        objectManager.addObject(sphere);
        return true;
    }
    return false;
}

std::string SphereCreatingMode::getStatusMessage()
{
    return "DRAWING SPHERE";
}