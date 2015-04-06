//
//  CylinderCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "CylinderCreatingMode.h"

#include "AirCylinder.h"
#include "Logger.h"

#define DISTANCE_SQUARED_THRESHOLD  5


std::vector<std::string> CylinderCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw cylinder");
    return commands;
}

CylinderCreatingMode::CylinderCreatingMode()
    : AirControlMode()
    , drawBaseCircleCompleted(false)
    , drawCylinderCompleted(false)
{
    
}

CylinderCreatingMode::~CylinderCreatingMode()
{
    
}

void CylinderCreatingMode::drawMode()
{
    
}

bool CylinderCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw cylinder")
    {
        hasCompleted = false;
        return true;
    }
    return false;
}

void CylinderCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    LeapHand* hand = handProcessor.getHandAtIndex(0);
    
    if (hand->getIsActive())
    {
        if (!drawBaseCircleCompleted)
        {
            circleTraces.push_back(hand->getTipLocation());
            float distanceSq = (circleTraces.front()-circleTraces.back()).lengthSquared();
            if (distanceSq < DISTANCE_SQUARED_THRESHOLD)
            {
                // The last trace is near to the starting point of the circle
                drawBaseCircleCompleted = true;
            }
        }
        else // Draw the cyclider height
        {
            if (!drawCylinderCompleted)
            {
                //TODO
                hasCompleted = true;
            }
        }
    }
    else
    {
        // hand is lost
        hasCompleted = true;
    }
    if (drawCylinderCompleted) {
        if (!createCylinder(objectManager))
        {
            Logger::getInstance()->temporaryLog("FAILED to create new CYLINDER");
        }
        drawBaseCircleCompleted = false;
        drawCylinderCompleted = false;
        circleTraces.clear();
        heightTraces.clear();
    }
}

bool CylinderCreatingMode::createCylinder(AirObjectManager &objectManager)
{
    ofPoint centroid = computeBaseCircleTraceCentroid();
    float radius = computeBaseCircleTraceRadius(centroid);
    float height = computeCylinderHeight();
    if ((radius > 0) && (height > 0))
    {
        //TODO: create cylinder
        //AirCylinder* cylinder = new AirCylinder();
        //cylinder->setup(centroid, radius, ofColor::gray); // Default color: gray
        //objectManager.addObject(cylinder);
        return true;
    }
    return false;
}

std::string CylinderCreatingMode::getStatusMessage()
{
    return "DRAWING CYLINDER";
}