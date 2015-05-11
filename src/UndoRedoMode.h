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

#include "AirController.h"

class UndoRedoMode : public AirControlMode
{
public:
    
    UndoRedoMode();
    ~UndoRedoMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;

    int getUndoCount const { return undoCount; };
    int getRedoCount const { return redoCount; };
    
private:
	int getLevelsFromString(std::string stringLevels);

	void undo(AirController* controller, int levels);
	void redo(AirController* controller, int levels);

    int undoCount;
    int redoCount;
};

#endif /* defined(__airsketcher__UndoRedoMode__) */