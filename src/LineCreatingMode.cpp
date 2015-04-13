//
//  LineCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//
//

#include "LineCreatingMode.h"
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


bool LineCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        hasCompleted = false;
        return true;
    }
    return false;

}

void LineCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
            if (!createLine(objectManager))
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


bool LineCreatingMode::createLine(AirObjectManager &objectManager)
{
    ofPoint startPoint = getStartPoint();
    ofPoint endPoint = getEndPoint();
    
    float dist = (endPoint - startPoint).length();
    
    if (dist != 0.0)
    {
        AirLine* line = new AirLine();
        if (NULL == line){
            return false;
        }
        line->setup(startPoint, endPoint, ofColor::gray);
        objectManager.addObject(line);
        return true;
    }

    return false;
}


std::string LineCreatingMode::getStatusMessage()
{
    return "Creating a line";
}


std::string LineCreatingMode::getHelpMessage()
{

    std::string msg = "1. Pinch your all fingers together to start drawing. \n"
    "2. When finished, slowly spread your fingers out.";
    return msg;
}
