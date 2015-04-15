//
//  BoxCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "BoxCreatingMode.h"

#include "AirCommand.h"
#include "logger.h"

std::vector<std::string> BoxCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer "+drawCommand);
    return commands;
}

BoxCreatingMode::BoxCreatingMode() : AirControlMode()
{
    
}

BoxCreatingMode::~BoxCreatingMode()
{
    
}

void BoxCreatingMode::drawMode()
{
    if (drawBoxMode == DRAW)
    {
        ofLine(getStartPoint(), getEndPoint());
        
        //TODO: also draw the pseudo box while they're drawing
    }
    
}

bool BoxCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        hasCompleted = false;
        return true;
    }
    return false;
}

void BoxCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
                switch (drawBoxMode) {
                    case DRAW:
                        traces.push_back(hand->getTipLocation());
                        break;
                    case NONE:
                        drawBoxMode = DRAW;
                        break;
                    default:
                        break;
                }
            }
            else if (drawBoxMode == DRAW)
            {
                drawBoxMode = DONE;
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
        
        if (drawBoxMode == DONE) {
            if (!createBox(objectManager))
            {
                std::stringstream msg;
                msg << "FAILED to create new box; trace size ";
                msg << traces.size();
                Logger::getInstance()->temporaryLog(msg.str());
            }
            hasCompleted = true;
        }
    }
    
    if (hasCompleted)
    {
        drawBoxMode = NONE;
        traces.clear();
    }
}


bool BoxCreatingMode::createBox(AirObjectManager &objectManager)
{

    ofVec3f size_xyz = getSize();
    ofPoint center = getCenterPosition();
    float dist = size_xyz.length();
    
    if (dist != 0.0)
    {
        AirBox* box = new AirBox();
        if (NULL == box){
            return false;
        }
        box->setup(center, size_xyz, ofColor::gray);
        objectManager.addObject(box);
        return true;
    }
    
    return false;
}


std::string BoxCreatingMode::getStatusMessage()
{
    return "DRAW A BOX";
}


std::string BoxCreatingMode::getHelpMessage()
{
    std::string msg ="";
    switch (drawBoxMode){
        case DRAW:
            msg ="When finished, slowly release your pinch \n";
            break;
        case NONE:
            msg = "Pinch your all fingers together to start then pull your diagonal. \n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    
    return msg;
}
