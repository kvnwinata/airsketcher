//
//  AirObjectManager.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//  Last update by Patricia Suriana on 3/31/15.
//
//

#include <assert.h>

#include "AirObjectManager.h"

AirObjectManager::AirObjectManager()
: highlightedObject(0)
{
}

AirObjectManager::~AirObjectManager()
{
    for (AirObject* object : objects)
    {
        delete object;
    }
    objects.clear();
}

void AirObjectManager::addObject(AirObject* object)
{
    objects.push_back(object);
}

void AirObjectManager::deleteObject(AirObject* object)
{
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        if((*it) == object)
        {
            if (highlightedObject == object)
            {
                highlightedObject = NULL;
            }
            delete *it;
            objects.erase(it);
            return;
        }
    }
}

void AirObjectManager::getObjectOwnership(AirObject* object)
{
    for (auto it = objects.begin(); it != objects.end(); ++it)
    {
        if((*it) == object)
        {
            if (highlightedObject == object)
            {
                highlightedObject = NULL;
            }
            objects.erase(it);
            return;
        }
    }
}

std::vector<AirObject*> AirObjectManager::getOwnershipAll()
{
    highlightedObject = NULL;
    std::vector<AirObject*> out;
    out.swap(objects);
    return out;
}

void AirObjectManager::drawObjects()
{
    for (AirObject* object : objects)
    {
        if (highlightedObject != object)
        {
            object->draw();
            object->drawShadow(false);
        }
    }
    
    if (highlightedObject)
    {
        highlightedObject->drawHighlight();
        highlightedObject->drawShadow(true);
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

void AirObjectManager::updateHighlight(ofPoint location, AirObject* forbiddenObject)
{
    highlightedObject = 0;
    
    for (AirObject* object : objects)
    {
        if (object != forbiddenObject && object->isInside(location))
        {
            highlightedObject = object;
            break;
        }
    }
}


bool AirObjectManager::switchHighlightedObject(AirObject* objectToHighlight, ofPoint location)
{
    if (objectToHighlight == NULL) return false;
    
    if (objectToHighlight->isInside(location))
    {
        highlightedObject = objectToHighlight;
        return true;
    }
    else
    {
        return false;
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

void AirObjectManager::getObjectsIterator(std::vector<AirObject*>::iterator &begin, std::vector<AirObject*>::iterator &end)
{
    begin = objects.begin();
    end = objects.end();
}
