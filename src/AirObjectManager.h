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
#include "AirBox.h"
#include "AirCylinder.h"

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
    
    // Force switching the highlight to passed object.
    // Will only switch if object is inside hand (return TRUE)
    // otherwise, do nothing and return FALSE
    bool switchHighlightedObject(AirObject* objectToHighlight, ofPoint location);
    
    void drawObjects();
    
    std::string getStatusMessage();
    
    // use this to iterate over all object
    void getObjectsIterator(std::vector<AirObject*>::iterator &begin, std::vector<AirObject*>::iterator &end);
    
private:
    
    AirObject* highlightedObject;
    
    std::vector<AirObject*> objects;
    
};



#endif /* defined(__airsketcher__AirObjectManager__) */