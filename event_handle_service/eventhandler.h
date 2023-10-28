#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

//**********************************************************************
// Header includes
//**********************************************************************
#include <QtMath>
#include <QObject>
#include <QMouseEvent>

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
    void onStartMouseClickEvent(QMouseEvent* event);
    void onProcessMouseClickEvent(QMouseEvent* event);
    void onStopMouseClickEvent(QMouseEvent* event);
    bool isStartMouseClickEvent() const { return startMouseClickEvent; }

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
    bool startMouseClickEvent = false;
    float lastMouseClickPosX;
    float lastMouseClickPosY;
    float yawAngle = -M_PI / 2;
    float pitchAngle = 0.0;
    float yawAngleDelta = 0.0;
    float pitchAngleDelta = 0.0;

    RenderService::Camera* camera;
};
}

#endif // EVENTHANDLER_H
