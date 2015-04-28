//
//  LineCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "LineCreatingMode.h"

#include "AirCommandLine.h"
#include "logger.h"

std::vector<std::string> LineCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer " + drawCommand);
    return commands;
}

LineCreatingMode::LineCreatingMode() : AirControlMode(), drawLineMode(NONE)
{
    
}

LineCreatingMode::~LineCreatingMode()
{

}

void LineCreatingMode::drawMode()
{
    if (drawLineMode == DRAW)
    {
        ofLine(getStartPoint(), getEndPoint());
    }
}


bool LineCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        hasCompleted = false;
        return true;
    }
    return false;

}

void LineCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
            // need to update higlighted object for snapping
            ofPoint tipLocation = hand->getTipLocation();
            objectManager.updateHighlight(tipLocation);

            if (hand->getIsPinching())
            {
                switch (drawLineMode) {
                    case DRAW:
                        traces.push_back(hand->getTipLocation());
                        break;
                    case NONE:
                        drawLineMode = DRAW;
                        break;
                    default:
                        break;
                }
            }
            else if (drawLineMode == DRAW)
            {
                drawLineMode = DONE;
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
        
        if (drawLineMode == DONE) {
            if (!createLine(controller, objectManager))
            {
                std::stringstream msg;
                msg << "FAILED to create new Line; trace size ";
                msg << traces.size();
                Logger::getInstance()->temporaryLog(msg.str());
            }
            hasCompleted = true;
        }
    }
    
    if (hasCompleted)
    {
        drawLineMode = NONE;
        traces.clear();
    }
    
}


bool LineCreatingMode::createLine(AirController* controller, AirObjectManager &objectManager)
{
    ofPoint startPoint = getStartPoint();
    ofPoint endPoint = getEndPoint();
    
    float dist = (endPoint - startPoint).length();
    
    if (dist != 0.0)
    {
        AirCommandLine* cmd = new AirCommandLine(objectManager, startPoint, endPoint);
        if (!controller->pushCommand(cmd))
        {
            return false;
        }
        return true;
    }

    return false;
}


std::string LineCreatingMode::getStatusMessage()
{
    return "DRAW A LINE";
}


std::string LineCreatingMode::getHelpMessage()
{
    std::string msg ="";
    switch (drawLineMode){
        case DRAW:
            msg ="When finished, slowly release your pinch \n";
            break;
        case NONE:
            msg = "Pinch your all fingers together to start then pull your line. \n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }

    return msg;
}
