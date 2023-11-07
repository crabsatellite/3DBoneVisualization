//**********************************************************************
// Header includes
//**********************************************************************
#include <QPoint>
#include <math.h>
#include <QDebug>
#include "eventhandler.h"
#include "render_service/camera.h"

//**********************************************************************
// Function definitions
//**********************************************************************
EventHandleService::EventHandler::EventHandler(QObject *parent) : QObject(parent)
{

}

void EventHandleService::EventHandler::onStartRotationEvent(float curFocusPosX, float curFocusPosY)
{
    lastFocusPosX = curFocusPosX;
    lastFocusPosY = curFocusPosY;
    startRotationEvent = true;
}

void EventHandleService::EventHandler::onStopRotationEvent(float curFocusPosX, float curFocusPosY)
{
    lastFocusPosX = 0;
    lastFocusPosY = 0;
    startRotationEvent = false;
}

void EventHandleService::EventHandler::onProcessZoomEvent(int delta)
{
    int fov = camera->getFOV() - delta;
    fov = std::max(std::min(fov, 99), 0);
    camera->setFOV(fov);
    qDebug() << "FOV is: " << fov;
}

void EventHandleService::EventHandler::onStartPanEvent(float curFocusPosX, float curFocusPosY)
{
    lastFocusPosX = curFocusPosX;
    lastFocusPosY = curFocusPosY;
    startPanEvent = true;
}

void EventHandleService::EventHandler::onStopPanEvent(float curFocusPosX, float curFocusPosY)
{
    lastFocusPosX = 0;
    lastFocusPosY = 0;
    startPanEvent = false;
}

void EventHandleService::EventHandler::onProcessPanEvent(float curFocusPosX, float curFocusPosY, float sensitivity)
{
    if ( !camera ) {
        return;
    }

    int horizontalStep = curFocusPosX == INT_MAX ? 0 : lastFocusPosX - curFocusPosX > 0 ? -1 : 1;
    int verticalStep = curFocusPosY == INT_MAX ? 0 : lastFocusPosY - curFocusPosY > 0 ? -1 : 1;
    lastFocusPosX = curFocusPosX;
    lastFocusPosY = curFocusPosY;

    QVector3D rightDirection = camera->getRightDirection();
    QVector3D upDirection = camera->getUpDirection();
    QVector3D viewDirection = camera->getViewDirection();
    rightDirection.normalize();
    upDirection.normalize();
    viewDirection.normalize();

    QVector3D cameraPos = camera->getCameraPosition();
    cameraPos -= rightDirection * horizontalStep * sensitivity;
    cameraPos += upDirection * verticalStep * sensitivity;

    camera->setViewCenter(cameraPos + viewDirection * camera->getRadius());
    camera->setCameraPosition(cameraPos);
}

void EventHandleService::EventHandler::setCamera(RenderService::Camera *camera)
{
    this->camera = camera;
}

void EventHandleService::EventHandler::rotateByEulerAngle()
{
    // Reference: https://learnopengl.com/Getting-started/Camera
    if ( !camera ) {
        return;
    }

    QVector3D cameraPos;
    const QVector3D viewCenter = camera->getViewCenter();
    const float radius = camera->getRadius();

    cameraPos.setX(viewCenter.x() + radius * cosf(pitchAngle) * sinf(yawAngle));
    cameraPos.setY(viewCenter.y() + radius * sinf(pitchAngle));
    cameraPos.setZ(viewCenter.z() + radius * cosf(pitchAngle) * cosf(yawAngle));

    camera->setCameraPosition(cameraPos);
}

void EventHandleService::EventHandler::onProcessRotationEvent(float curFocusPosX, float curFocusPosY, float sensitivity)
{
    // Reference: https://learnopengl.com/Getting-started/Camera
    if ( startRotationEvent ) {
        yawAngle -= qDegreesToRadians((curFocusPosX - lastFocusPosX) * sensitivity);
        pitchAngle += qDegreesToRadians((curFocusPosY - lastFocusPosY) * sensitivity);
        if ( pitchAngle < -(float)M_PI / 2.0f + 0.1f ) {
            pitchAngle = -(float)M_PI / 2.0f + 0.1f;
        } else if ( pitchAngle > (float)M_PI / 2.0f - 0.1f) {
            pitchAngle = (float)M_PI / 2.0f - 0.1f;
        }
        rotateByEulerAngle();
        lastFocusPosX = curFocusPosX;
        lastFocusPosY = curFocusPosY;
    }
}
