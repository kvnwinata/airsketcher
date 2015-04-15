//
//  AirCommand.h
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#ifndef __airsketcher__AirCommand__
#define __airsketcher__AirCommand__

#include "AirObject.h"

class AirCommand
{
public:
	AirCommand();
    ~AirCommand();

    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class AirCommandColoring : public AirCommand
{
public:
	AirCommandColoring(AirObject* object, std::string prevColor, std::string newColor);
    ~AirCommandColoring();

    void execute() override;
    void unexecute() override;

private:
	const AirObject* _object; // should be a valid pointer
	const std::string _prevColor;
	const std::string _newColor;
};

class AirCommandResizing : public AirCommand
{
public:
	AirCommandResizing(AirObject* object, float prevScale, float newScale);
    ~AirCommandResizing();

    void execute() override;
    void unexecute() override;

private:
	const AirObject* _object; // should be a valid pointer
	const float _prevScale;
    const float _newScale;
};

class AirCommandCopying : public AirCommand
{
public:
	AirCommandCopying(AirObjectManager& objectManager, AirObject* copiedObject);
    ~AirCommandCopying();

    void execute() override;
    void unexecute() override;

    AirObject* getObjectCopy() { return _objectCopy; }

private:
	AirObjectManager& _objectManager;
	const AirObject* _copiedObject; // should be a valid pointer
	AirObject* _objectCopy;
};

class AirCommandErasing : public AirCommand
{
public:
	AirCommandErasing(AirObjectManager& objectManager, AirObject* object);
    ~AirCommandErasing();

    void execute() override;
    void unexecute() override;

private:
	AirObjectManager& _objectManager;
	AirObject* _object; // should be a valid pointer
};

class AirCommandMoving : public AirCommand
{
public:
	AirCommandMoving(AirObject* object, ofPoint prevPosition, ofPoint newPosition);
    ~AirCommandMoving();

    void execute() override;
    void unexecute() override;

private:
	const AirObject* _object; // should be a valid pointer
	const ofPoint _prevPosition;
	const ofPoint _newPosition;
};

class AirCommandSphere : public AirCommand
{
public:
	AirCommandSphere(AirObjectManager& objectManager, ofPoint centroid, float radius);
    ~AirCommandSphere();

    void execute() override;
    void unexecute() override;

    AirObject* getSphere() { return _sphere; }

private:
	AirObjectManager& _objectManager;
	const ofPoint _centroid;
	const float _radius;
	AirObject* _sphere;
};

class AirCommandCylinder : public AirCommand
{
public:
	AirCommandCylinder(AirObjectManager& objectManager, ofPoint centroid, float radius, float height);
    ~AirCommandCylinder();

    void execute() override;
    void unexecute() override;

    AirObject* getCylinder() { return _cylinder; }

private:
	AirObjectManager& _objectManager;
	const ofPoint _centroid;
	const float _radius;
	const float _height;
	AirObject* _cylinder;
};

class AirCommandLine : public AirCommand
{
public:
	AirCommandLine(AirObjectManager& objectManager, ofPoint startPoint, ofPoint endPoint);
    ~AirCommandLine();

    void execute() override;
    void unexecute() override;

    AirObject* getLine() { return _line; }

private:
	AirObjectManager& _objectManager;
	const ofPoint _startPoint;
	const ofPoint _endPoint;
	AirObject* _line;
};

#endif /* defined(__airsketcher__AirCommand__) */