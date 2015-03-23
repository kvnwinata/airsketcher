//
//  AirObjectManager.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
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
    
    void addObject(AirObject * object);

    void updateHighlight(ofPoint location);
    AirObject* getHighlightedObject();
    
    void drawObjects();
    
    std::string getStatusMessage();
    
    
private:
    
    AirObject* highlightedObject;
    
    std::vector<AirObject*> objects;
    
};



#endif /* defined(__airsketcher__AirObjectManager__) */
