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

#define DEFAULT_HEIGHT  5


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
    , newCylinder(NULL)
{
    
}

CylinderCreatingMode::~CylinderCreatingMode()
{
    
}

void CylinderCreatingMode::drawMode()
{
    if (drawCylinderMode == DRAW_CIRCLE) {
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
    bool isCancelled = false;
    
    if (command == "cancel")
    {
        isCancelled = true;
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
                    {
                        endHeight = hand->getTipLocation();
                        float height =  DEFAULT_HEIGHT + computeCylinderHeight();
                        newCylinder->setHeight(height);
                        break;
                    }
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
            else
            {
                switch (drawCylinderMode) {
                    case DRAW_CIRCLE:
                        if (!createCylinder(objectManager))
                        {
                            Logger::getInstance()->temporaryLog("FAILED to create new CYLINDER");
                            hasCompleted = true;
                        }
                        drawCylinderMode = NONE_HEIGHT;
                        break;
                    case DRAW_HEIGHT:
                        drawCylinderMode = DONE;
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
            std::stringstream msg;
            msg << "Create CYLINDER (FINAL) with RADIUS ";
            msg << newCylinder->getRadius();
            msg << " and HEIGHT ";
            msg << newCylinder->getHeight();
            Logger::getInstance()->temporaryLog(msg.str());
            hasCompleted = true;
        }
    }

    if (hasCompleted)
    {
        if (isCancelled && (NULL != newCylinder)) {
            objectManager.deleteObject(newCylinder);
        }
        newCylinder = NULL;
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
    float height =  DEFAULT_HEIGHT;
    if (radius > 0)
    {
        newCylinder = new AirCylinder();
        if (NULL == newCylinder)
        {
            return false;
        }
        newCylinder->setup(centroid, radius, height, ofColor::gray); // Default color: gray
        objectManager.addObject(newCylinder);
        std::stringstream msg;
        msg << "Create CYLINDER (INITIAL) with RADIUS ";
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
    switch (drawCylinderMode) {
        case DRAW_CIRCLE:
        {
            std::stringstream msg;
            msg << "DRAWING CYLINDER: current trace size ";
            msg << circleTraces.size();
            return msg.str();
        }
        case NONE_HEIGHT:
            return "DRAWING CYLINDER: done drawing base circle";
        case DRAW_HEIGHT:
            return "DRAWING CYLINDER: drawing height";
        case DONE:
            return "DRAWING CYLINDER: DONE";
        default:
            return "DRAWING CYLINDER: do nothing";
    }
}

std::string CylinderCreatingMode::getHelpMessage()
{
    std::string msg;
    switch (drawLineMode){
        case NONE_CIRCLE:
            msg = "Pinch your fingers and draw a circle. \n";
            break;
        case DRAW_CIRCLE:
            msg = "When finished, release your pinch\n OR to cancel midway, say 'computer cancel'\n";
            break;
        case NONE_HEIGHT:
            msg = "Pinch your fingers and move around to adjust the height. \n"
            break;    
        case DRAW_HEIGHT:
            msg = "When finished, release your pinch\n OR to cancel midway, say 'computer cancel'\n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    return msg;
}
