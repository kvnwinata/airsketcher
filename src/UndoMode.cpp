//
//  AirCommand.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "AirCommand.h"
#include "Logger.h"

/***************************************************************************************/
/** AirCommandColoring
/***************************************************************************************/

AirCommandColoring::AirCommandColoring(AirObject* object, std::string prevColor, std::string newColor)
	: AirCommand()
	, _object(object)
	, _prevColor(prevColor)
	, _newColor(newColor)
{
}

void AirCommandColoring::execute()
{
	_object->setColor(_newColor);
}

void AirCommandColoring::unexecute()
{
	_object->setColor(_prevColor);
}

/***************************************************************************************/
/** AirCommandResizing
/***************************************************************************************/

AirCommandResizing::AirCommandResizing(AirObject* object, float prevScale, float newScale)
	: AirCommand()
	, _object(object)
	, _prevScale(prevScale)
	, _newScale(newScale)
{
}

void AirCommandResizing::execute()
{
	_object->setScale(_newScale);
}

void AirCommandResizing::unexecute()
{
	_object->setScale(_prevScale);
}

/***************************************************************************************/
/** AirCommandCopying
/***************************************************************************************/

AirCommandCopying::AirCommandCopying(AirObjectManager& objectManager, AirObject* copiedObject)
	: AirCommand()
	, _objectManager(objectManager)
	, _copiedObject(copiedObject)
	, _objectCopy(NULL)
{
}

void AirCommandCopying::execute()
{
	_objectCopy = _copiedObject->getCopy();
	if (NULL == _objectCopy) 
	{
		return;
	}
	_objectManager.addObject(_objectCopy);
    _objectManager.switchHighlightedObject(_objectCopy, _objectCopy->getPosition());
}

void AirCommandCopying::unexecute()
{
	_objectManager.deleteObject(_objectCopy);
	_objectCopy = NULL;
}

/***************************************************************************************/
/** AirCommandErasing
/***************************************************************************************/

AirCommandErasing::AirCommandErasing(AirObjectManager& objectManager, AirObject* object)
	: AirCommand()
	, _objectManager(objectManager)
	, _object(object)
{
}

void AirCommandErasing::execute()
{
	AirObject* copy = _object->getCopy();
	if (NULL == copy) 
	{
		Logger::getInstance()->temporaryLog("ERASING object " + _object->getDescription() + "failed; cannot allocate new copy");
        return;
	}
	_objectManager.deleteObject(_object);
	_object = copy;
}

void AirCommandErasing::unexecute()
{
	_objectManager.addObject(_object);	
}

/***************************************************************************************/
/** AirCommandMoving
/***************************************************************************************/

AirCommandMoving::AirCommandMoving(AirObject* object, ofPoint prevPosition, ofPoint newPosition)
	: AirCommand()
	, _object(object)
	, _prevPosition(prevPosition)
	, _newPosition(newPosition)
{
}

void AirCommandMoving::execute()
{
	_object->setColor(_newColor);
}

void AirCommandMoving::unexecute()
{
	_object->setColor(_prevColor);
}

/***************************************************************************************/
/** AirCommandSphere
/***************************************************************************************/

AirCommandSphere::AirCommandSphere(AirObjectManager& objectManager, ofPoint centroid, float radius)
	: AirCommand()
	, _objectManager(objectManager)
	, _centroid(centroid)
	, _radius(radius)
	, _sphere(NULL)
{
}

void AirCommandSphere::execute()
{
	_sphere = new AirSphere();
    if (NULL == sphere)
    {
        return;
    }
    _sphere->setup(_centroid, _radius, ofColor::gray); // Default color: gray
    _objectManager.addObject(_sphere);
}

void AirCommandSphere::unexecute()
{
	_objectManager.deleteObject(_sphere);
	_sphere = NULL;
}

/***************************************************************************************/
/** AirCommandCylinder
/***************************************************************************************/

AirCommandCylinder::AirCommandCylinder(AirObjectManager& objectManager, ofPoint centroid, float radius, float height)
	: AirCommand()
	, _objectManager(objectManager)
	, _centroid(centroid)
	, _radius(radius)
	, _height(height)
	, _cylinder(NULL)
{
}

void AirCommandCylinder::execute()
{
	_cylinder = new AirCylinder();
    if (NULL == _cylinder)
    {
        return;
    }
    _cylinder->setup(_centroid, _radius, _height, ofColor::gray); // Default color: gray
    _objectManager.addObject(_cylinder);
}

void AirCommandCylinder::unexecute()
{
	_objectManager.deleteObject(_cylinder);
	_cylinder = NULL;
}

/***************************************************************************************/
/** AirCommandLine
/***************************************************************************************/

AirCommandLine::AirCommandLine(AirObjectManager& objectManager, ofPoint startPoint, ofPoint endPoint)
	: AirCommand()
	, _objectManager(objectManager)
	, _startPoint(startPoint)
	, _endPoint(endPoint)
{
}

void AirCommandLine::execute()
{
	_line = new AirLine();
    if (NULL == _line)
    {
        return;
    }
    _line->setup(_startPoint, _endPoint, ofColor::gray); // Default color: gray
    _objectManager.addObject(_line);
}

void AirCommandLine::unexecute()
{
	_objectManager.deleteObject(_line);
	_line = NULL;
}
