//
//  AirObjectManager.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#include "AirObjectManager.h"

AirObjectManager::AirObjectManager()
: highlightedObject(0)
{
}

AirObjectManager::~AirObjectManager()
{
    
}

void AirObjectManager::addObject(AirObject * object)
{
    objects.push_back(object);
}

void AirObjectManager::drawObjects()
{
    for (AirObject* object : objects)
    {
        if (highlightedObject != object) object->draw();
    }
    
    if (highlightedObject)
    {
        highlightedObject->drawHighlight();
    }
}

void AirObjectManager::updateHighlight(ofPoint location)
{
    highlightedObject = 0;
    
    for (AirObject* object : objects)
    {
        if (object->isInside(location))
        {
            highlightedObject = object;
            break;
        }
    }
}

AirObject * AirObjectManager::getHighlightedObject()
{
    return highlightedObject;
}

std::string AirObjectManager::getStatusMessage()
{
    std::stringstream msg;
    msg << "[OBJECTS]: ";
    msg << "status message\n";
    
    return msg.str();
}