//
//  CylinderCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "CylinderCreatingMode.h"

#include "AirCommandCylinder.h"
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
    circleTraces.resize(2, ofPoint());
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
}

bool CylinderCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "draw cylinder")
    {
        hasCompleted = false;
        return true;
    }
    return false;
}

void CylinderCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
                        circleTraces[1] = hand->getTipLocation();
                        break;
                    case DRAW_HEIGHT:
                    {
                        float height = hand->getTipLocation()[2] - cylinderBaseLoc[2];
                        if ((height >= 0) && (height < DEFAULT_HEIGHT)) {
                            height = DEFAULT_HEIGHT;
                        }
                        if ((height < 0) && (-height < DEFAULT_HEIGHT)) {
                            height = -DEFAULT_HEIGHT;
                        }

                        ofPoint centroid = computeCylinderCentroid(height);
                        newCylinder->setPosition(centroid);
                        newCylinder->setHeight(abs(height));
                        break;
                    }
                    case NONE_CIRCLE:
                        circleTraces[0] = hand->getTipLocation(); // Start point
                        circleTraces[1] = hand->getTipLocation(); // End point
                        drawCylinderMode = DRAW_CIRCLE;
                        break;
                    case NONE_HEIGHT:
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
                        if (!createCylinder(controller, objectManager))
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
            controller->popCommand();
        }
        newCylinder = NULL;
        drawCylinderMode = NONE_CIRCLE;
        circleTraces.clear();
    }
}

bool CylinderCreatingMode::createCylinder(AirController* controller, AirObjectManager &objectManager)
{
    cylinderBaseLoc = computeBaseCircleTraceCentroid();
    float radius = computeBaseCircleTraceRadius(cylinderBaseLoc);
    if (radius > 0)
    {
        float height =  DEFAULT_HEIGHT;
        ofPoint centroid = computeCylinderCentroid(height);
        
        AirCommandCylinder* cmd = new AirCommandCylinder(objectManager, centroid, radius, height);
        if (!controller->pushCommand(cmd))
        {
            return false;
        }
        newCylinder = dynamic_cast<AirCylinder*>(cmd->getObject());

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
    switch (drawCylinderMode) {
        case NONE_CIRCLE:
            msg = "Pinch your fingers and draw line (radius + centroid). \n";
            break;
        case DRAW_CIRCLE:
            msg = "When finished, release your pinch\n OR to cancel midway, say 'computer cancel'\n";
            break;
        case NONE_HEIGHT:
            msg = "Pinch your fingers and move around to adjust the height. \n";
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
