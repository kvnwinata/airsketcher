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
    commands.push_back("computer cancel");
    return commands;
}

CylinderCreatingMode::CylinderCreatingMode()
    : AirControlMode()
    , drawCylinderMode(NONE_CIRCLE)
{
    
}

CylinderCreatingMode::~CylinderCreatingMode()
{
    
}

void CylinderCreatingMode::drawMode()
{
    if ((drawCylinderMode != NONE_CIRCLE) && (drawCylinderMode != DONE)) {
        for (auto it = circleTraces.begin(); it != circleTraces.end(); )
        {
            const ofPoint& p1 = *it;
            it++;
            if (it != circleTraces.end())
            {
                const ofPoint& p2 = *it;
                ofLine(p1, p2);
            }
        }
    }
    if (drawCylinderMode == DRAW_HEIGHT) {
        ofLine(startHeight, endHeight);
    }
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
    std::string command = speechProcessor.getLastCommand();
    if (command == "cancel")
    {
        hasCompleted = true;
    } 
    else 
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            if (hand->getIsPinching())
            {
                switch (drawCylinderMode) {
                    case DRAW_CIRCLE:
                        circleTraces.push_back(hand->getTipLocation());
                        break;
                    case DRAW_HEIGHT:
                        endHeight = hand->getTipLocation();
                        break;
                    case NONE_CIRCLE:
                        drawCylinderMode = DRAW_CIRCLE;
                        break;
                    case NONE_HEIGHT:
                        startHeight = hand->getTipLocation();
                        drawCylinderMode = DRAW_HEIGHT;
                        break;
                    default:
                        break;
                }
            }
            else if (drawCylinderMode == DRAW_CIRCLE)
            {
                switch (drawCylinderMode) {
                    case DRAW_CIRCLE:
                        drawCylinderMode = NONE_HEIGHT;
                        break;
                    case DRAW_HEIGHT:
                        drawCylinderMode = DONE;
                        hasCompleted = true;
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
        
        if (drawCylinderMode == DONE) {
            if (!createCylinder(objectManager))
            {
                Logger::getInstance()->temporaryLog("FAILED to create new CYLINDER");
            }
        }
    }

    if (hasCompleted)
    {
        drawCylinderMode = NONE_CIRCLE;
        circleTraces.clear();
        startHeight = ofPoint();
        endHeight = ofPoint();
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
        //cylinder->setup(centroid, height, ofColor::gray); // Default color: gray
        //objectManager.addObject(cylinder);
        std::stringstream msg;
        msg << "Create CYLINDER with RADIUS ";
        msg << radius;
        msg << " and HEIGHT ";
        msg << height;
        Logger::getInstance()->temporaryLog(msg.str());
        return true;
    }
    return false;
}

std::string CylinderCreatingMode::getStatusMessage()
{
    return "DRAWING CYLINDER";
}