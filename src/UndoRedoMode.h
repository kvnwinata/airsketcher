//
//  UndoRedoMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__UndoRedoMode__
#define __airsketcher__UndoRedoMode__

#include <functional>

#include "AirControlMode.h"

class UndoRedoMode : public AirControlMode
{
public:
    
    UndoRedoMode();
    ~UndoRedoMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:
	int getLevelsFromString(std::string stringLevels);

	void undo(int levels);
	void redo(int levels);
};

#endif /* defined(__airsketcher__UndoRedoMode__) */