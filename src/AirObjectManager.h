//
//  AirObjectManager.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//  Last update by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__AirObjectManager__
#define __airsketcher__AirObjectManager__

#include "ofMain.h"

#include "AirObject.h"

#include "AirSphere.h"

class AirObjectManager
{
public:
    
    AirObjectManager();
    ~AirObjectManager();
    
    // Transfer ownership to AirObjectManager. AirObjectManager will take care
    // of deleting the allocated pointer during its destruction
    void addObject(AirObject* object);
    
    // Delete object from the container; handle memory deallocation as well.
    void deleteObject(AirObject* object);
    
    void updateHighlight(ofPoint location);
    AirObject* getHighlightedObject();
    
    void drawObjects();
    
    std::string getStatusMessage();
    
    
private:
    
    AirObject* highlightedObject;
    
    std::vector<AirObject*> objects;
    
};



#endif /* defined(__airsketcher__AirObjectManager__) */