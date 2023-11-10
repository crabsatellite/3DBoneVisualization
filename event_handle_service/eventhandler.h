#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QtMath>
#include <QObject>

//**********************************************************************
// Forward declarations
//**********************************************************************
namespace RenderService {
class Camera;
}

namespace EventHandleService {

//**********************************************************************
// Class declaration
//**********************************************************************
class EventHandler : public QObject
{
    Q_OBJECT
public:
//**********************************************************************
// Constructors & destructors
//**********************************************************************
    explicit EventHandler(QObject *parent = nullptr);
    ~EventHandler() = default;

public:
//**********************************************************************
// Public methods
//**********************************************************************

    // Rotation
    bool isStartRotationEvent() const { return startRotationEvent; }
    void onStartRotationEvent(float curFocusPosX, float curFocusPosY);
    void onProcessRotationEvent(float curFocusPosX, float curFocusPosY, float sensitivity = 1.0);
    void onStopRotationEvent(float curFocusPosX, float curFocusPosY);

    // Zoom
    void onProcessZoomEvent(int delta);

    // Move
    bool isStartPanEvent() const { return startPanEvent; }
    void onStartPanEvent(float curFocusPosX, float curFocusPosY);
    void onProcessPanEvent(float curFocusPosX, float curFocusPosY, float sensitivity = 1.0);
    void onStopPanEvent(float curFocusPosX, float curFocusPosY);

    void setCamera(RenderService::Camera* camera);

private:
//**********************************************************************
// Public methods
//**********************************************************************
    void rotateByEulerAngle();

private:
//**********************************************************************
// Private attributes
//**********************************************************************
    bool startRotationEvent = false;
    bool startPanEvent = false;
    float lastFocusPosX;
    float lastFocusPosY;
    float yawAngle = -M_PI / 2;
    float pitchAngle = 0.0;
    float yawAngleDelta = 0.0;
    float pitchAngleDelta = 0.0;

    RenderService::Camera* camera;
};
}

#endif // EVENTHANDLER_H
