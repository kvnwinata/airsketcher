//
//  AirControlMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#ifndef __airsketcher__AirControlMode__
#define __airsketcher__AirControlMode__

#include "HandProcessor.h"
#include "SpeechProcessor.h"
#include "AirObjectManager.h"


class AirControlMode
{
    
public:
    
    AirControlMode();
    virtual ~AirControlMode();
    
    virtual bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) = 0;
    virtual void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) = 0;
    virtual void drawMode() = 0;
    virtual std::vector<std::string> getCommands() = 0;
    
    bool getHasCompleted() const;
    
    virtual std::string getStatusMessage() = 0;
    virtual std::string getHelpMessage();
    
protected:
    bool hasCompleted;

    // For undo-redo
    std::stack<AirCommand> undoCommands;
    std::stack<AirCommand> redoCommands;

    inline void pushCommand(AirCommand cmd) { 
        undoCommands.push(cmd);
        redoCommands = std::stack<AirCommand>();
    };

    /* Pop the command on the top of the undoCommands stack */
    inline AirCommand deleteCommand(AirCommand cmd) { 
        AirCommand cmd = undoCommands.top();
        undoCommands.pop();
        return cmd;
    };
};

#endif /* defined(__airsketcher__AirControlMode__) */
